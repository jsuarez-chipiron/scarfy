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

    InitAudioDevice();

    Music music = LoadMusicStream("country.mp3");

    PlayMusicStream(music);

    Texture2D background = LoadTexture("forest.png");
    Texture2D scarfy = LoadTexture("scarfy.png");

    int frameWidth = scarfy.width/6;
    int frameHeight = scarfy.height;

    SetTargetFPS(60);

    float timer = 0.0f;
    int frame = 0;

    float scarfy_x = 0.f;
    float scarfy_y = (float)frameHeight;
    float scarfy_vx = 3.2f;
    float scarfy_vy = 0.0f;
    float scarfy_flip = 1.0f;

    float back_x = -30.0f;
    float back_vx = -0.1f;

    float frame_rate = 0.12f;

    float g = 9.8f;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_UP)) 
        {
            scarfy_vy = -10.0f;
        }
    
        UpdateMusicStream(music);

        scarfy_x += scarfy_vx;
        scarfy_y += scarfy_vy;

        if ( scarfy_y > (float)frameHeight ) scarfy_y = (float)frameHeight;

        back_x += back_vx;

        timer += GetFrameTime();

        scarfy_vy = scarfy_vy + g * timer;

        if ( timer > frame_rate )
        {
            timer = 0.0f;
            frame++;
            frame %= 6;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        Rectangle src_back = { 150.f, 560.0f, (float)screenWidth+200.0f, (float)screenHeight };
        DrawTextureRec(background, src_back, Vector2{back_x, 0}, WHITE);

        Rectangle sourceRec = { (float)frameWidth*frame, 0.0f, (float)frameWidth, (float)frameHeight };

        sourceRec.width *= scarfy_flip;

        DrawTextureRec(scarfy, sourceRec, Vector2{scarfy_x, scarfy_y}, WHITE);

        DrawFPS(10, 400);

        if ( scarfy_x > screenWidth || scarfy_x < 0-frameWidth ) 
        { 
            scarfy_vx   *= -1.f; 
            scarfy_flip *= -1.f; 
            back_vx     *= -1.f; 
        }

        EndDrawing();
    }

    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice(); 

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
