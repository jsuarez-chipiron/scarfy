#include "raylib.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <variant>

constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - collision area");

    Texture2D scarfy = LoadTexture("scarfy.png");

    int frameWidth = scarfy.width/6;
    int frameHeight = scarfy.height;

    SetTargetFPS(60);

    float timer = 0.0f;
    int frame = 0;

    while (!WindowShouldClose())
    {
        timer += GetFrameTime();

        if ( timer > 0.15f )
        {
            timer = 0.0f;
            frame++;
            frame %= 6;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        Rectangle sourceRec = { (float)frameWidth*frame, 0.0f, (float)frameWidth, (float)frameHeight };

        DrawTextureRec(scarfy, sourceRec, Vector2{0, (float)frameHeight}, WHITE);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
