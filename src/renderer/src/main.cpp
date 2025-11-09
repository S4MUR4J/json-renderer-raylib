#include "raylib.h"

int main() {
    InitWindow(1024, 768, "SceneKeeper Renderer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("SceneKeeper Renderer", 220, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}