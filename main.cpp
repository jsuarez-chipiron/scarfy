#include "raylib.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <variant>

constexpr int screen_width = 1200;
constexpr int screen_height = 450;
constexpr float floor_y = 250.f;

int main(void)
{
    InitWindow(screen_width, screen_height, "raylib [shapes] example - collision area");

    InitAudioDevice();

    Music music = LoadMusicStream("country.mp3");

    PlayMusicStream(music);

    Texture2D background = LoadTexture("forest.png");
    Texture2D scarfy = LoadTexture("scarfy.png");

    int frame_width = scarfy.width/6;
    int frame_height = scarfy.height;

    SetTargetFPS(60);

    float timer = 0.0f;
    int frame = 0;

    float scarfy_x = 0.f;
    float scarfy_y = floor_y;
    float scarfy_vx = 3.2f;
    float scarfy_vy = 0.0f;
    float scarfy_flip = 1.0f;

    float back_x = -30.0f;
    float back_vx = -0.1f;

    float frame_rate = 0.12f;

    float g = 9.8f;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) 
        {
            scarfy_vy = -17.0f;
        }
    
        UpdateMusicStream(music);

        timer += GetFrameTime();

        scarfy_x += scarfy_vx;
        scarfy_y += scarfy_vy;

        // Floor check
        if ( scarfy_y > floor_y ) scarfy_y = floor_y;

        back_x += back_vx;

        scarfy_vy = scarfy_vy + g * timer;

        if ( timer > frame_rate )
        {
            timer = 0.0f;
            frame++;
            frame %= 6;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        Rectangle src_back = { 150.f, 560.0f, (float)screen_width+200.0f, (float)screen_height };
        DrawTextureRec(background, src_back, Vector2{back_x, 0}, WHITE);

        Rectangle sourceRec = { (float)frame_width*frame, 0.0f, (float)frame_width, (float)frame_height };

        sourceRec.width *= scarfy_flip;

        DrawTextureRec(scarfy, sourceRec, Vector2{scarfy_x, scarfy_y}, WHITE);

        DrawFPS(10, 400);

        if ( scarfy_x > screen_width || scarfy_x < 0-frame_width ) 
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
