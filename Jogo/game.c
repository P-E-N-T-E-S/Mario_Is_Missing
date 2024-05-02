#include "raylib.h"

#define width 510
#define height 480

int main(void)
{
    InitWindow(width, height, "Mario Is Missing");
    Image icon = LoadImage("src/Telas/menu.png");
    SetWindowIcon(icon);
    SetTargetFPS(60); 

    Texture2D background = LoadTexture("src/Telas/menu.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(background, 0, 0, WHITE); 
        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow();

    return 0;
}
