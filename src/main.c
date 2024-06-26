#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

#define PURK \
    (Color) { 146, 2, 68, 255 }
#define YELH \
    (Color) { 254, 194, 140, 255 }

enum Level {
    MENU,
    GAME,
    END
};
// Starting Level
enum Level currentLevel = MENU;

Vector2 cursorPosition = {340, 200};
bool exitPressed = false;

int frameCount = 0;
int score = 0;
int highScore = 0;
Rectangle ground;
Rectangle preGround;
Rectangle player;
Rectangle prePlayer;

#define MAX_OBSTACLE 4
#define OBSTACLE_PIECES 2
Rectangle obstacles[MAX_OBSTACLE][OBSTACLE_PIECES];
Rectangle preObstacles[MAX_OBSTACLE][OBSTACLE_PIECES];
int xIncrement = 240;

void updateGame(float);
void drawGame();

int main(void) {

    // Raylib Setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Clone");
    SetTargetFPS(60);

    // Game Setup
    ground = (Rectangle){0, 400, 800, 100};
    preGround = ground;
    player = (Rectangle){100, 150, 40, 40};
    prePlayer = player;

    srand(time(NULL));
    int minHeight = 50;
    int maxHeight = 200;
    int startX = 600;

    for (int i = 0; i < MAX_OBSTACLE; i++) {
        int topHeight = (rand() % (maxHeight - minHeight + 1)) + minHeight;
        obstacles[i][0] = (Rectangle){startX, 0, 60, topHeight};
        preObstacles[i][0] = obstacles[i][0];
        obstacles[i][1] = (Rectangle){startX, topHeight + player.height * 3 + 20, 60, 450};
        preObstacles[i][1] = obstacles[i][1];
        startX += xIncrement;
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        updateGame(dt);
        drawGame();

        if (exitPressed) {
            break;
        }
    }

    CloseWindow();

    return 0;
}

void updateGame(float dt) {
    switch (currentLevel) {
    case MENU:
        int x = 340;
        int y = 200;

        // Handle Navigation
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) {
            if (cursorPosition.y == y) {
                cursorPosition.x = 350;
                cursorPosition.y = 250;
            } else {
                cursorPosition.x = x;
                cursorPosition.y = y;
            }
        }

        // Handle Interaction
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
            if (cursorPosition.y == y) {
                currentLevel = GAME;
            } else {
                exitPressed = true;
            }
        }
        break;
    case GAME:
        // Player Input
        int jumpHeight = 50;
        if (IsKeyPressed(KEY_SPACE)) {
            if (player.y > jumpHeight + 1) {
                player.y -= jumpHeight;
            } else {
                player.y = 0;
            }
        }
        // Player Gravity
        if (!CheckCollisionRecs(player, ground)) {
            player.y += 125 * dt;
        } else {
            currentLevel = END;
            if (score > highScore)
                highScore = score;
        }

        // Move Obstacles
        int obstacleSpeed = 150;

        for (int i = 0; i < MAX_OBSTACLE; i++) {
            for (int j = 0; j < OBSTACLE_PIECES; j++) {
                obstacles[i][j].x -= obstacleSpeed * dt;
                if (obstacles[i][j].x < 0 - obstacles[i][j].width) {
                    obstacles[i][j].x = SCREEN_WIDTH + xIncrement / 2;
                }
            }
        }

        // Obstacle Collision
        for (int i = 0; i < MAX_OBSTACLE; i++) {
            for (int j = 0; j < OBSTACLE_PIECES; j++) {
                if (CheckCollisionRecs(player, obstacles[i][j])) {
                    currentLevel = END;
                    if (score > highScore)
                        highScore = score;
                }
            }
        }

        // Update Timer
        frameCount++;
        if (frameCount >= 60) {
            score++;
            frameCount = 0;
        }
        break;
    case END:
        if (IsKeyPressed(KEY_ENTER)) {
            currentLevel = GAME;
            frameCount = 0;
            score = 0;
            ground = preGround;
            player = prePlayer;
            for (int i = 0; i < MAX_OBSTACLE; i++) {
                obstacles[i][0] = preObstacles[i][0];
                obstacles[i][1] = preObstacles[i][1];
            }
        }
        break;
    }
}

void drawGame() {
    BeginDrawing();
    ClearBackground(PURK);

    int midScreen = SCREEN_WIDTH / 2;
    int fontSize = 24;

    switch (currentLevel) {
    case MENU:
        int center = MeasureText("flappy bird clone", fontSize) / 2;
        DrawText("flappy bird clone", midScreen - center, 100, fontSize, YELH);

        center = MeasureText("START", fontSize) / 2;
        DrawText("START", midScreen - center, 200, fontSize, YELH);

        center = MeasureText("EXIT", fontSize) / 2;
        DrawText("EXIT", midScreen - center, 250, fontSize, YELH);

        // Draw Cursor
        DrawText(">", cursorPosition.x, cursorPosition.y, fontSize, YELH);
        break;
    case GAME:
        // Draw Obstacles
        for (int i = 0; i < MAX_OBSTACLE; i++) {
            for (int j = 0; j < OBSTACLE_PIECES; j++) {
                DrawRectangleRec(obstacles[i][j], YELH);
            }
        }

        // Draw Player
        DrawRectangleRec(player, YELH);

        // Draw Ground
        DrawRectangleRec(ground, YELH);

        // Draw Score
        DrawRectangle(300, 0, 200, 50, YELH);

        char formattedScore[20];
        sprintf(formattedScore, "SCORE: "
                                "%d",
                score);
        center = MeasureText(formattedScore, fontSize) / 2;
        DrawText(formattedScore, 400 - center, 10, 24, PURK);
        break;
    case END:
        // Draw Options
        midScreen = SCREEN_WIDTH / 2;
        fontSize = 24;

        center = MeasureText("flappy bird clone", fontSize) / 2;
        DrawText("flappy bird clone", midScreen - center, 25, fontSize, YELH);

        sprintf(formattedScore, "HIGHSCORE: "
                                "%d",
                highScore);
        center = MeasureText(formattedScore, fontSize * 2) / 2;
        DrawText(formattedScore, midScreen - center, 75, fontSize * 2, YELH);

        sprintf(formattedScore, "SCORE: "
                                "%d",
                score);
        center = MeasureText(formattedScore, fontSize * 2) / 2;
        DrawText(formattedScore, midScreen - center, 125, fontSize * 2, YELH);

        center = MeasureText("PRESS SPACE TO REPLAY", fontSize) / 2;
        DrawText("PRESS ENTER TO REPLAY", midScreen - center, 350, fontSize, YELH);

        break;
    default:
        DrawText("There is an issue with level management", 0, 200, 24, YELH);
        break;
    }

    EndDrawing();
}