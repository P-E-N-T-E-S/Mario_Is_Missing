#include <stdio.h>
#include "raylib.h"

#define WIDTH 510
#define HEIGHT 480
#define MAX_INPUT_CHARS 6

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
void animacaoLuigi(Texture2D bg);

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Mario Is Missing");
    SetTargetFPS(15); 

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

    // Load Backgrounds
    Texture2D arg = LoadTexture("src/Background/BuenosAires/LongBuenosAires2x.png");

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
                printf("%d", charCount);
                if (IsKeyPressed(KEY_ENTER) && get_name[0] != '\0'){ 
                    currentScreen = GAME;
                    break;
                }
                break;
            case GAME:
                ClearBackground(BLACK);
               
                animacaoLuigi(arg);
                
                break;
            case GUESS:

            case GAME_OVER:

            case END:
                //DrawTexture(end, 0, 0, WHITE); 
                
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

void animacaoLuigi(Texture2D bg) {
    Texture2D luigiLeft1 = LoadTexture("src/Sprites/Luigi/L.png");
    Texture2D luigiLeft2 = LoadTexture("src/Sprites/Luigi/W_L.png");
    Texture2D luigiRight1 = LoadTexture("src/Sprites/Luigi/R.png");
    Texture2D luigiRight2 = LoadTexture("src/Sprites/Luigi/W_R.png");
    
    Vector2 position = { WIDTH / 2 - luigiLeft1.width / 2, HEIGHT - luigiLeft1.height - 70};
    
    int currentFrame = 0;
    float speed = 5.0f;
    int last;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(bg, 0, 0, WHITE);
        if (IsKeyDown(KEY_A)) {
            position.x -= speed;
            
            if (currentFrame == 0)
                DrawTexture(luigiLeft1, position.x, position.y, WHITE);
            else if (currentFrame == 1)
                DrawTexture(luigiLeft2, position.x, position.y, WHITE);
            
            currentFrame++;
            if (currentFrame > 1)
                currentFrame = 0;

            last = 1;
        } else if (IsKeyDown(KEY_D)) {
            position.x += speed;
            
            if (currentFrame == 0)
                DrawTexture(luigiRight1, position.x, position.y, WHITE);
            else if (currentFrame == 1)
                DrawTexture(luigiRight2, position.x, position.y, WHITE);
            
            currentFrame++;
            if (currentFrame > 1)
                currentFrame = 0;
            
            last = 0;
        } else {
            if (last == 1) {
                DrawTexture(luigiLeft1, position.x, position.y, WHITE);
            }
            else {
                DrawTexture(luigiRight1, position.x, position.y, WHITE);
            }
            
        }
        
        EndDrawing();
    }
    
    UnloadTexture(luigiLeft1);
    UnloadTexture(luigiLeft2);
    UnloadTexture(luigiRight1);
    UnloadTexture(luigiRight2);
}

