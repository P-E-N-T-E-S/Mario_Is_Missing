#include <stdio.h>
#include "raylib.h"

#define WIDTH 510
#define HEIGHT 480
#define MAX_INPUT_CHARS 10

typedef enum { 
    START, 
    RANKING,
    RANKING_PAGE,
    GET_NAME,
    GAME,
    GUESS,
    GAME_OVER,
    END
} ScreenState;

void TextInput(char *inputText, int *charCount);

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Mario Is Missing");
    SetTargetFPS(60); 

    // Load Menu
    Texture2D menu = LoadTexture("src/Telas/menu.png");
    Texture2D start = LoadTexture("src/Telas/start.png");
    Texture2D ranking = LoadTexture("src/Telas/ranking.png");

    // Load Ranking
    Texture2D ranking_page = LoadTexture("src/Telas/ranking_page.png");

    // Load Font
    Font customFont = LoadFont("src/MarioFont.ttf");
    char get_name[MAX_INPUT_CHARS + 1] = {0};
    int charCount = 0;

    // Load type
    Texture2D type_page = LoadTexture("src/Telas/type_page.png");

    // Load end
    Texture2D end = LoadTexture("src/Telas/end.png");

    ScreenState currentScreen = START;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        switch (currentScreen) {
            case START:
                if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
                 currentScreen = RANKING;
                        break;
                }
               
                if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
                    currentScreen = RANKING;
                    break;
                }

                DrawTexture(menu, 0, 0, WHITE); 
                DrawTexture(start, 165, 260, WHITE); 
                if (IsKeyPressed(KEY_ENTER)) { 
                    currentScreen = GET_NAME;
                    UnloadTexture(menu);
                    UnloadTexture(start);
                    break;
                }
                break;
            case RANKING:
                if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
                 currentScreen = START;
                        break;
                }
               
                if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
                    currentScreen = START;
                    break;
                }

                DrawTexture(menu, 0, 0, WHITE); 
                DrawTexture(ranking, 165, 260, WHITE); 
                if (IsKeyPressed(KEY_ENTER)) { 
                    currentScreen = RANKING_PAGE;
                    UnloadTexture(menu);
                    UnloadTexture(start);
                    break;
                }
                break;
            case RANKING_PAGE:
                DrawTexture(ranking_page, 0, 0, WHITE);
                break;
            case GET_NAME:
                DrawTexture(type_page, 0, 0, WHITE); 
                TextInput(get_name, &charCount);
                DrawTextEx(customFont, "Digite seu nome:", (Vector2){60, 90}, 20, 2, WHITE);
                DrawTextEx(customFont, get_name, (Vector2){60, 140}, 20, 2, WHITE);
                if (IsKeyPressed(KEY_ENTER)) { 
                    currentScreen = GAME;
                    UnloadTexture(type_page);
                }
            case GAME:

            case GUESS:

            case GAME_OVER:

            case END:
                DrawTexture(end, 0, 0, WHITE); 
                
        }
        EndDrawing();

    }

    CloseWindow();

    return 0;
}


void TextInput(char *inputText, int *charCount) {
    int key = GetKeyPressed();
    if (key != 0)
    {
        if ((key >= 32) && (key <= 125) && (*charCount < MAX_INPUT_CHARS))
        {
            inputText[*charCount] = (char)key;
            (*charCount)++;
        }
        else if ((key == KEY_BACKSPACE) && (*charCount > 0))
        {
            (*charCount)--;
            inputText[*charCount] = '\0';
        }
        else if (key == KEY_ENTER)
        {
            inputText[*charCount] = '\0';
            *charCount = 0;
            printf("Texto digitado: %s\n", inputText);
        }
    }
}