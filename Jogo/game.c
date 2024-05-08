#include <stdio.h>
#include "raylib.h"
#include "function.c"

#define WIDTH 510
#define HEIGHT 446
#define MAX_INPUT_CHARS 6
#define NUM 6

typedef enum { 
    START, 
    RANKING,
    RANKING_PAGE,
    GET_NAME,
    GAME,
    GUESS,
    GAME_OVER,
    WIN
} ScreenState;

typedef enum {
    MEX,
    ARG,
    BRA,
    FRA,
    ITA,
    CHI,
} Cenarios;

typedef enum {
    A,
    B,
    C,
    D
} Alternativas;

void TextInput(char *inputText, int *charCount);
Alternativas animacaoLuigi(Texture2D bg, Font font);

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

    // Nome
    char get_name[MAX_INPUT_CHARS + 1] = {0};
    int charCountName = 0;
    char get_guess[10] = {0};
    int charCountGuess = 0;
    // Load typing page
    Texture2D type_page = LoadTexture("src/Telas/type_page.png");

    // Load Backgrounds
    Texture2D texturasCenarios[NUM];
    texturasCenarios[MEX] = LoadTexture("src/Background/Mexico/Mexico.png");
    texturasCenarios[ARG] = LoadTexture("src/Background/BuenosAires/BuenosAires.png");
    texturasCenarios[BRA] = LoadTexture("src/Background/Rio/Rio.png");
    texturasCenarios[FRA] = LoadTexture("src/Background/Paris/Paris.png"); 
    texturasCenarios[ITA] = LoadTexture("src/Background/Roma/Roma.png");
    texturasCenarios[CHI] = LoadTexture("src/Background/China/China.png");

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
                TextInput(get_name, &charCountName);
                DrawTextEx(customFont, "Digite seu nome:", (Vector2){60, 90}, 20, 2, WHITE);
                DrawTextEx(customFont, get_name, (Vector2){60, 140}, 20, 2, WHITE);
                printf("%d", charCountName);
                if (IsKeyPressed(KEY_ENTER) && get_name[0] != '\0'){ 
                    currentScreen = GAME;
                    break;
                }
                break;
            case GAME:
          
                Alternativas resposta = animacaoLuigi(texturasCenarios[0], customFont);
                currentScreen = GUESS;
                
                break;
            case GUESS:
                DrawTexture(type_page, 0, 0, WHITE); 
                TextInput(get_guess, &charCountGuess);
                DrawTextEx(customFont, "em que cidade o mario\nesta:", (Vector2){60, 90}, 16, 2, WHITE);
                DrawTextEx(customFont, get_guess, (Vector2){60, 140}, 20, 2, WHITE);
                printf("%d", charCountGuess);
                if (IsKeyPressed(KEY_ENTER) && get_guess[0] != '\0'){ 
                    // if (get_guess == lugar)
                        // currentScreen = END;
                    // else
                        // currentScreen = GAME_OVER;
                    break;
                }
                break;
            case GAME_OVER:

            case WIN:
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

Alternativas animacaoLuigi(Texture2D bg, Font font) {
    // Load sprites
    Texture2D luigiLeft1 = LoadTexture("src/Sprites/Luigi/L.png");
    Texture2D luigiLeft2 = LoadTexture("src/Sprites/Luigi/W_L.png");
    Texture2D luigiRight1 = LoadTexture("src/Sprites/Luigi/R.png");
    Texture2D luigiRight2 = LoadTexture("src/Sprites/Luigi/W_R.png");

    Texture2D alt_a = LoadTexture("src/Telas/escolha_a.png");
    Texture2D alt_b = LoadTexture("src/Telas/escolha_b.png");
    Texture2D alt_c = LoadTexture("src/Telas/escolha_c.png");
    Texture2D alt_d = LoadTexture("src/Telas/escolha_d.png");

    Vector2 position = { WIDTH - luigiLeft1.width - 470, HEIGHT - luigiLeft1.height - 40};
    
    int currentFrame = 0;
    float speed = 8.0f;
    int last;
    int part = 1;
    bool pgtaAtiva = false; 
    Alternativas alt = A;
    

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(bg, 0, 0, WHITE);
            
        if (position.x >= 310) {
            if (!pgtaAtiva) {
                DrawTextEx(font, "Aperte E para falar com a Peach", (Vector2){20, 90}, 15, 2, BLACK);
            }
            
            if (IsKeyDown(KEY_E)) {
                pgtaAtiva = true;
            }
            
            if (pgtaAtiva) {
                if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_UP)) {
                    if (alt < D) {
                        alt++;
                    } else {
                        alt = A;
                    }
                } else if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_UP)) {
                    if (alt > A) {
                        alt--;
                    } else {
                        alt = D;
                    }
                }

                switch (alt) {
                    case A:
                        DrawTexture(alt_a, 50, 20, WHITE);
                        if (IsKeyDown(KEY_ENTER)) {
                            return alt;
                            break;
                        } 
                        break;
                    case B:
                        DrawTexture(alt_b, 50, 20, WHITE);
                        break;
                    case C:
                        DrawTexture(alt_c, 50, 20, WHITE);
                        break;
                    case D:
                        DrawTexture(alt_d, 50, 20, WHITE);
                        break;
                }

                DrawTextEx(font, "Que nome é dado aos vestígios do\npassado que ajudam os\nhistoriadores a conhecer sobre \noutros tempos?", (Vector2){55, 35}, 12, 2, BLACK);
                DrawTextEx(font, "  a) nao sei\n  b) isso ai\n  c) acho q eh\n  d) vei seila", (Vector2){55, 120}, 14, 2, BLACK);
            }
        }
        
        if (!pgtaAtiva) {
            if (IsKeyDown(KEY_A)) {
                position.x -= speed;
                
                if (currentFrame == 0) {
                    DrawTexture(luigiLeft1, position.x, position.y, WHITE);
                }
                else if (currentFrame == 1) {
                    DrawTexture(luigiLeft2, position.x, position.y, WHITE);
                }
                
                currentFrame++;
                if (currentFrame > 1) {
                    currentFrame = 0;
                }

                last = 1;
            } else if (IsKeyDown(KEY_D)) {
                position.x += speed;
                
                if (currentFrame == 0) {
                    DrawTexture(luigiRight1, position.x, position.y, WHITE);
                }
                    
                else if (currentFrame == 1) {
                    DrawTexture(luigiRight2, position.x, position.y, WHITE);
                }
                    
                currentFrame++;
                if (currentFrame > 1) {
                    currentFrame = 0;
                }
                
                last = 0;
            } else {
                if (last == 1) {
                    DrawTexture(luigiLeft1, position.x, position.y, WHITE);
                }
                else {
                    DrawTexture(luigiRight1, position.x, position.y, WHITE);
                }
            } 
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
