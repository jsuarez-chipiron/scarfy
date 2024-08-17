#include "raylib.h"

#include <string>
#include <vector>

constexpr int screen_width = 1200;
constexpr int screen_height = 450;
constexpr float floor_y = 250.f;
constexpr float g = 9.8f;

struct Erizo
{
    Erizo(float x, float y, float r): erizo_x{x}, erizo_y{y}, erizo_r{r}
    {
        erizo_vx = 9.0f;
    }

    float erizo_x;
    float erizo_y;

    float erizo_vx;
    float erizo_vy;

    float erizo_r = 20.f;

    void update(float timer) 
    {
        erizo_x += erizo_vx;
        erizo_y += erizo_vy;

        erizo_vy = erizo_vy + g * timer;

        if ( erizo_y > floor_y + 105.f )
        { 
            erizo_y = floor_y + 105.f;
        }
    }

    void draw() const
    {
        DrawCircle(erizo_x, erizo_y, erizo_r, BROWN);
    }
};

int main(void)
{
    InitWindow(screen_width, screen_height, "raylib [shapes] example - collision area");

    InitAudioDevice();

    Music music = LoadMusicStream("resources/country.mp3");

    PlayMusicStream(music);

    Texture2D background = LoadTexture("resources/forest.png");
    Texture2D scarfy = LoadTexture("resources/scarfy.png");
    Texture2D heart = LoadTexture("resources/heart.png");

    int heart_width = heart.width/8;
    int heart_height = heart.height;

    int frame_width = scarfy.width/6;
    int frame_height = scarfy.height;

    std::vector<Erizo> erizos;

    SetTargetFPS(60);

    float global_timer = 0.0f;
    float timer = 0.0f;
    float timer_heart = 0.0f;
    float timer_lives = 0.0f;
    float timer_enemy = 0.0f;

    int frame = 0;
    int frame_heart = 0;

    bool can_hurt = true;

    float scarfy_x = 0.f;
    float scarfy_y = floor_y;
    float scarfy_vx = 3.2f;
    float scarfy_vy = 0.0f;
    float scarfy_flip = 1.0f;
    int scarfy_lives = 3;

    float back_x = -30.0f;
    float back_vx = -0.1f;

    float frame_rate = 0.12f;
    float heart_rate = 0.07f;

    bool is_in_the_air = false;

    int lower_limit = 2000;
    int upper_limit = 4000;

    float erizo_r = 20.f;

    int level = 1;

    float random = GetRandomValue(lower_limit, upper_limit)/1000.f;

    while (!WindowShouldClose())
    {
        if ( IsKeyPressed(KEY_SPACE) && !is_in_the_air ) 
        {
            scarfy_vy = -17.0f;
            is_in_the_air = true;
        }

        //if ( IsKeyPressed(KEY_N) ) 
        //{
        //  erizos.push_back(Erizo{0.f, floor_y - erizo_r});
        //}

        if ( IsKeyDown(KEY_J) && IsKeyDown(KEY_A) && IsKeyDown(KEY_V) && IsKeyDown(KEY_I) ) 
        {
            scarfy_lives = 10;
        }

        UpdateMusicStream(music);

        timer += GetFrameTime();
        timer_heart += GetFrameTime();
        timer_enemy += GetFrameTime();
        global_timer += GetFrameTime();

        if ( global_timer > 10.f )
        {
            global_timer = 0.0f;
            erizo_r += 3.0f;
            lower_limit -= 50.f;
            lower_limit -= 50.f;
            level++;
        }

        if ( timer_enemy > random )
        {
            timer_enemy = 0.0f;
            random = GetRandomValue(lower_limit, upper_limit)/1000.f;
            if ( scarfy_x < 200.f) { random = GetRandomValue(lower_limit, upper_limit)/1000.f; }
            else { erizos.push_back(Erizo{0.f, floor_y - 50.f, erizo_r}); }
        }

        if ( !can_hurt )
        {
            timer_lives += GetFrameTime();
            if ( timer_lives > 1.f )
            {
                timer_lives = 0.0f;
                can_hurt = true;
            }
        }

        scarfy_x += scarfy_vx;
        scarfy_y += scarfy_vy;

        // Floor check
        if ( scarfy_y > floor_y )
        { 
            scarfy_y = floor_y;
            is_in_the_air = false;
        }

        back_x += back_vx;

        scarfy_vy = scarfy_vy + g * timer;

        if ( timer > frame_rate )
        {
            timer = 0.0f;
            frame++;
            frame %= 6;
        }

        if ( timer_heart > heart_rate )
        {
            timer_heart = 0.0f;
            frame_heart++;
            frame_heart %= 8;
        }

        for (auto& erizo: erizos)
        { 
            erizo.update(timer);
            Vector2 erizo_center { erizo.erizo_x, erizo.erizo_y };
            if ( CheckCollisionCircleRec(erizo_center, erizo.erizo_r, Rectangle{scarfy_x, scarfy_y, (float)frame_width, (float)frame_height}) )
            {
                if ( can_hurt )
                {
                    can_hurt = false;
                    scarfy_lives--;
                }
            }
        }

        BeginDrawing();

        ClearBackground(WHITE);

        Rectangle src_back = { 150.f, 560.0f, (float)screen_width+200.0f, (float)screen_height };
        DrawTextureRec(background, src_back, Vector2{back_x, 0}, WHITE);

        if ( scarfy_lives > 0 )
        {

            Rectangle source_rec = { (float)frame_width*frame, 0.0f, (float)frame_width, (float)frame_height };

            source_rec.width *= scarfy_flip;

            DrawTextureRec(scarfy, source_rec, Vector2{scarfy_x, scarfy_y}, WHITE);

            float heart_x = 20.f;
            for (size_t i=0; i!=scarfy_lives; ++i) 
            {
                Rectangle heart_rec = { (float)heart_width*frame_heart, 0.0f, (float)heart_width, (float)heart_height };
                DrawTextureRec(heart, heart_rec, Vector2{heart_x, 20}, WHITE);
                heart_x += heart_width;
            }

            for (auto& erizo: erizos)
            { 
                erizo.draw();
            }

            DrawFPS(1100, 10);

            if ( scarfy_x > screen_width || scarfy_x < 0-frame_width ) 
            { 
                scarfy_vx   *= -1.f; 
                scarfy_flip *= -1.f; 
                back_vx     *= -1.f; 
            }
        }
        else
        {
             DrawText("GAME OVER", 360, 200, 80, LIGHTGRAY);
        }

        std::string level_str = "Level " + std::to_string(level);
        DrawText(level_str.c_str(), 1100, 400, 20, LIGHTGRAY);

        EndDrawing();
    }

    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice(); 

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
