#include "raylib.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

#define PURK \
    (Color) { 146, 2, 68, 255 }
#define YELH \
    (Color) { 254, 194, 140, 255 }

enum Level {
    menu,
    game,
    end
};
Level currentLevel = Level::game;

typedef struct {
    Rectangle rect;
    Texture2D texture;
    bool collisionEnabled;
    Color tint;
} Sprite;

Sprite ground;
Sprite baseObstacle;
Sprite player;

void loadAssets();
void updateGame(float);
void drawGame();
void unloadAssets();

int main(void) {

    // Raylib Setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Clone");
    SetTargetFPS(60);

    // Game Setup
    ground.rect = Rectangle{0, 450 - 100, 800, 200};
    ground.collisionEnabled = true;
    ground.tint = YELH;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        updateGame(dt);
        drawGame();
    }

    CloseWindow();

    return 0;
}

void updateGame(float _dt) {
    switch (currentLevel) {
    case menu:
        break;
    case game:
        break;
    case end:
        break;
    }
}

void drawGame() {
    BeginDrawing();
    ClearBackground(PURK);

    switch (currentLevel) {
    case menu:
        DrawText("This is the main menu", 0, 200, 12, YELH);
        break;
    case game:
        // Draw Ground
        DrawRectangleRec(ground.rect, ground.tint);
        break;
    case end:
        DrawText("This is the end screen", 0, 200, 12, YELH);
        break;
    default:
        DrawText("There is an issue with level management", 0, 200, 12, YELH);
        break;
    }

    EndDrawing();
}