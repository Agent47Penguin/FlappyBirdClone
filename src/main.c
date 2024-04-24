#include "raylib.h"

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
enum Level currentLevel = GAME;

Rectangle ground;
Rectangle baseObstacle;
Rectangle player;

void loadAssets();
void updateGame(float);
void drawGame();

int main(void) {

    // Raylib Setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Clone");
    SetTargetFPS(60);

    // Game Setup
    ground = (Rectangle){0, 400, 800, 100};
    player = (Rectangle){100, 150, 40, 40};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        updateGame(dt);
        drawGame();
    }

    CloseWindow();

    return 0;
}

void updateGame(float dt) {
    switch (currentLevel) {
    case MENU:
        break;
    case GAME:
        // Player Input
        if (IsKeyPressed(KEY_SPACE)) {
            player.y -= 75;
        }
        // Player Gravity
        if (!CheckCollisionRecs(player, ground)) {
            player.y += 150 * dt;
        } else {
            currentLevel = END;
        }
        break;
    case END:
        break;
    }
}

void drawGame() {
    BeginDrawing();
    ClearBackground(PURK);

    switch (currentLevel) {
    case MENU:
        DrawText("This is the main menu", 0, 200, 12, YELH);
        break;
    case GAME:
        // Draw Player
        DrawRectangleRec(player, YELH);

        // Draw Ground
        DrawRectangleRec(ground, YELH);
        break;
    case END:
        DrawText("This is the end screen", 0, 200, 24, YELH);
        break;
    default:
        DrawText("There is an issue with level management", 0, 200, 24, YELH);
        break;
    }

    EndDrawing();
}