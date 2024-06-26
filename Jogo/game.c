#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "raylib.h"
#include "function.c"
#include "ranking.c"
#include "dica.c"

#define WIDTH 510
#define HEIGHT 446
#define MAX_INPUT_CHARS 6
#define NUM 6

typedef enum { 
    MENU,
    RANKING_PAGE,
    GET_NAME,
    GAME,
    DICA,
    GUESS,
    GAME_OVER,
    WIN
} ScreenState;

typedef enum {
    START, 
    RANKING
} MenuOpcoes;

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

typedef enum {
    SIM,
    NAO
} SimouNao;

void TextInput(char *inputText, int *charCount);
Alternativas animacaoLuigi(Texture2D bg, Font font, Questions *head);
bool isMusicOver(Music musica);
void loopMusic(Music musica);
void DrawText32Chars(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color color);

int main(void)
{
    // Configurações de tela
    InitWindow(WIDTH, HEIGHT, "Mario Is Missing");
    SetTargetFPS(60);
    SetWindowState(FLAG_VSYNC_HINT);
    SetExitKey(KEY_NULL);
    DisableCursor();
    HideCursor();
    InitAudioDevice();
    SetMasterVolume(0.7);
    
    // Load Menu
    Texture2D menu = LoadTexture("src/Telas/menu.png");
    Texture2D start = LoadTexture("src/Telas/start.png");
    Texture2D ranking = LoadTexture("src/Telas/ranking.png");

    // Load Ranking
    Texture2D ranking_page = LoadTexture("src/Telas/ranking_page.png");

    // Load Font
    Font customFont = LoadFont("src/MarioFont.ttf");

    // Inicializar string do nome e do local
    char get_name[MAX_INPUT_CHARS + 1] = {0};
    int charCountName = 0;
    char get_guess[10] = {0};
    int charCountGuess = 0;

    // Load typing page
    Texture2D type_page = LoadTexture("src/Telas/type_page.png");
    Texture dica = LoadTexture("src/Telas/dica.png");
    Texture2D sim = LoadTexture("src/Telas/escolha_c.png");
    Texture2D nao = LoadTexture("src/Telas/escolha_d.png");

    // Load Backgrounds
    Texture2D texturasCenarios[NUM];
    texturasCenarios[MEX] = LoadTexture("src/Background/Mexico/Mexico.png");
    texturasCenarios[ARG] = LoadTexture("src/Background/BuenosAires/BuenosAires.png");
    texturasCenarios[BRA] = LoadTexture("src/Background/Rio/Rio.png");
    texturasCenarios[FRA] = LoadTexture("src/Background/Paris/Paris.png"); 
    texturasCenarios[ITA] = LoadTexture("src/Background/Roma/Roma.png");
    texturasCenarios[CHI] = LoadTexture("src/Background/China/China.png");

    // Load end
    Texture2D win = LoadTexture("src/Telas/end.png");
    Texture2D over = LoadTexture("src/Telas/GameOver.png");

    // Load music and play music
    Music temaMenu = LoadMusicStream("src/Ost/Menu.mp3");
    Music temaWin = LoadMusicStream("src/Ost/FinalBom.mp3");
    Music temaOver = LoadMusicStream("src/Ost/FinalRuim.mp3");
    Sound acertou = LoadSound("src/Ost/LuigiYAHOO.wav");
    Sound itsmeMario = LoadSound("src/Ost/itsmeMario.wav");
    PlayMusicStream(temaMenu);
    PlayMusicStream(temaWin);
    PlayMusicStream(temaOver);

    // Inicializar tela no menu e variáveis zeradas
    ScreenState currentScreen = MENU;
    int cenarios = 0;
    int pontos = 120;

    // Inicializar head das perguntas e lista encadeada
    Questions *head = NULL;
    int respostas[6];
    sortearArquivo(&head, respostas);
    aleatorizarPerguntas(&head);

    // Inicializar head das dicas e lista encadeada
    Dicas *headDicas = NULL;
    lerDicas(&headDicas);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        UpdateMusicStream(temaMenu);
        loopMusic(temaMenu);
        // Percorre as telas através da variável currentScreen
        switch (currentScreen) {
            case MENU:
                static MenuOpcoes opcao;
                DrawTexture(menu, 0, 0, WHITE); 
   
                if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
                    opcao = RANKING;
                } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
                    opcao = START;
                }  
    
                switch (opcao) {
                    case START: 
                        DrawTexture(start, 165, 260, WHITE); 
                        if (IsKeyDown(KEY_ENTER)) {  
                            currentScreen = GET_NAME; // Pede o nome do usuário
                            break;
                        }
                        break;
                    case RANKING: 
                        DrawTexture(ranking, 165, 260, WHITE); 
                        if (IsKeyDown(KEY_ENTER)) { 
                            currentScreen = RANKING_PAGE; // Mostra o ranking
                            break;
                        }
                        break;
                }
                break;
            case RANKING_PAGE:
                DrawTexture(ranking_page, 0, 0, WHITE);
                ListaRanking *headRank = NULL;
                ordernar_ranking(); // Ordena a lista encadeada 
                ListaRanking *ranking = printranking(); // Chama a lista encadeada

                // Percorre a lista encadeada do ranking e mostrando as 10 pontuações mais altas
                ListaRanking *i;
                int cont = 0;
                for (i = ranking; i != NULL && cont < 10; i = i->next) { 
                    char *str_pontos = strpontos(i->pontos);
                    DrawTextEx(customFont, i->nome, (Vector2){120, (100 + (30 * cont))}, 20, 2, BLACK);
                    DrawTextEx(customFont, str_pontos, (Vector2){330, (100 + (30 * cont))}, 20, 2, BLACK);
                    cont++;
                }                 

                if (IsKeyDown(KEY_ESCAPE)) {
                    currentScreen = MENU; // Volta pro menu
                }
                break;
            case GET_NAME:
                DrawTexture(type_page, 0, 0, WHITE); 
                TextInput(get_name, &charCountName); // Guarda nome na variável get_name
                DrawTextEx(customFont, "Digite seu nome:", (Vector2){60, 90}, 20, 2, WHITE);
                DrawTextEx(customFont, get_name, (Vector2){60, 140}, 20, 2, WHITE); // Mostra o nome da tela
       
                if (IsKeyPressed(KEY_ENTER) && get_name[0] != '\0'){ 
                    currentScreen = GAME; // Inicializa jogo
                    PauseMusicStream(temaMenu);
                    break;
                }
                break;
            case GAME:
                Alternativas resposta_usuario;

                while (cenarios < NUM) { // Percorre os cenários
                    if (cenarios > 0) {
                        pontos -= 20; // A cada cenário percorrido perde 20 pontos
                    }
                    // Recebe a resposta do usuário com a função animação Luigi
                    resposta_usuario = animacaoLuigi(texturasCenarios[cenarios], customFont, head);
                    cenarios++;
                    break;
                }

                if ((resposta_usuario == head->resposta) && cenarios < NUM) {  // Se resposta tiver correta
                    currentScreen = DICA; // Recebe a dica
                    PlaySound(acertou);
                }
                else if (cenarios == NUM) {
                    currentScreen = GUESS; // Se perguntas tiverem acabado, usuário advinha local
                }
                else {
                    currentScreen = GAME_OVER; // Caso responda errado, perde o jogo.
                }
                
                remover(&head); // Remove a head de perguntas
                break;
            case DICA:
                static SimouNao chutar;
                SetWindowMonitor(FLAG_VSYNC_HINT);
                SetTargetFPS(60);
                ResumeMusicStream(temaMenu);
                DrawTexture(dica, 0, 0, WHITE); 

                if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_DOWN)) {
                    chutar = NAO;
                } else if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_UP)) {
                    chutar = SIM;
                }    
                
                switch (chutar) {
                    case SIM: // Caso queira advinhar, vai para página para digitar
                        DrawTexture(sim, 50, 20, WHITE); 
                        if (IsKeyDown(KEY_ENTER)) {
                            currentScreen = GUESS;
                            removerDicas(&headDicas); // Remove head de dicas
                            break;
                        }
                        break;
                    case NAO: // Caso não queira, volta pro jogo
                        DrawTexture(nao, 50, 20, WHITE); 
                        if (IsKeyDown(KEY_ENTER)) {
                            currentScreen = GAME;
                            removerDicas(&headDicas); // Remove head de dicas
                            break;
                        }
                        break;
                }
                DrawTextEx(customFont, "DICA:", (Vector2){55, 25}, 14, 2, BLACK);
                DrawText32Chars(customFont, headDicas->dica, (Vector2){55, 45}, 12, 2, BLACK);
                DrawTextEx(customFont, "deseja advinhar onde o Mario esta?", (Vector2){55, 135}, 11, 2, BLACK); // Acessando a dica
                DrawTextEx(customFont, "  sim\n  nao", (Vector2){55, 155}, 14, 2, BLACK);
             
                break;
            case GUESS:
                char local[7] = "PEQUIM"; // Local definido

                DrawTexture(type_page, 0, 0, WHITE); 
                
                TextInput(get_guess, &charCountGuess); // Input do local advinhado
                DrawTextEx(customFont, "em que cidade o Mario\nesta:", (Vector2){60, 90}, 16, 2, WHITE);
                DrawTextEx(customFont, get_guess, (Vector2){60, 140}, 20, 2, WHITE);
                
                if (IsKeyPressed(KEY_ENTER) && get_guess[0] != '\0'){ 
                    if (strcmp(get_guess, local) == 0) { // Caso local definido == input do usuário
                        salvar_ranking(get_name, pontos); // Salva a pontuação
                        currentScreen = WIN; // Ganha o jogo
                    }
                    else if (strcmp(get_guess, local) != 0 && cenarios == (NUM - 1)) { // Caso local definido != input
                        currentScreen = GAME_OVER; // Perde o jogo
                    }
                    else {
                        currentScreen = GAME; 
                    }
                    memset(get_guess, '\0', sizeof(get_guess)); // Limpar o input
                    break;
                }
                break;
            case GAME_OVER: // Tela game over
                SetWindowState(FLAG_VSYNC_HINT);
                SetTargetFPS(60);
                StopMusicStream(temaMenu);
                DrawTexture(over, 0, 0, WHITE); 
                UpdateMusicStream(temaOver);
                loopMusic(temaOver);
                DrawTextEx(customFont, "aperte esc para sair", (Vector2){120, 380}, 14, 2, WHITE);
                if (IsKeyDown(KEY_ESCAPE)) {
                    CloseWindow(); 
                }
                break;
            case WIN: // Tela de vitória
                SetWindowState(FLAG_VSYNC_HINT);
                SetTargetFPS(60);
                StopMusicStream(temaMenu);
                DrawTexture(win, 0, 0, WHITE); 
                DrawTextEx(customFont, strpontos(pontos), (Vector2){260, 330}, 14, 2, BLACK);
                UpdateMusicStream(temaWin);
                loopMusic(temaWin);
                DrawTextEx(customFont, "aperte esc para sair", (Vector2){120, 380}, 14, 2, BLACK);
                if (IsKeyDown(KEY_ESCAPE)) {
                    CloseWindow();
                }

                break;
                
        }
        EndDrawing();

    }
    UnloadTexture(over);

    CloseWindow();
    CloseAudioDevice();
    return 0;
}


void TextInput(char *inputText, int *charCount) { // Recebe uma string do usuário
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
        }
    }
}

Alternativas animacaoLuigi(Texture2D bg, Font font, Questions *head) {
    // Load sprites
    Texture2D luigiLeft1 = LoadTexture("src/Sprites/Luigi/L.png");
    Texture2D luigiLeft2 = LoadTexture("src/Sprites/Luigi/W_L.png");
    Texture2D luigiRight1 = LoadTexture("src/Sprites/Luigi/R.png");
    Texture2D luigiRight2 = LoadTexture("src/Sprites/Luigi/W_R.png");

    Texture2D alt_a = LoadTexture("src/Telas/escolha_a.png");
    Texture2D alt_b = LoadTexture("src/Telas/escolha_b.png");
    Texture2D alt_c = LoadTexture("src/Telas/escolha_c.png");
    Texture2D alt_d = LoadTexture("src/Telas/escolha_d.png");
    Texture2D aperte = LoadTexture("src/Telas/aperteE.png");

    Vector2 position = { WIDTH - luigiLeft1.width - 470, HEIGHT - luigiLeft1.height - 40};
    SetTargetFPS(15); 
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
                DrawTexture(aperte, 20, 30, WHITE);
                DrawTextEx(font, "Aperte E para falar com a Peach", (Vector2){22, 40}, 15, 2, BLACK);
            }
            
            if (IsKeyDown(KEY_E)) {
                pgtaAtiva = true;
            }
            
            if (pgtaAtiva) {
                if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_DOWN)) {
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

                switch (alt) { // Retorna a alternativa escolhida pelo usuário
                    case A:
                        DrawTexture(alt_a, 50, 20, WHITE);
                        if (IsKeyDown(KEY_ENTER)) {
                            return alt;
                            break;
                        } 
                        break;
                    case B:
                        DrawTexture(alt_b, 50, 20, WHITE);
                        if (IsKeyDown(KEY_ENTER)) {
                            return alt;
                            break;
                        } 
                        break;
                    case C:
                        DrawTexture(alt_c, 50, 20, WHITE);
                        if (IsKeyDown(KEY_ENTER)) {
                            return alt;
                            break;
                        }                         
                        break;
                    case D:
                        DrawTexture(alt_d, 50, 20, WHITE);
                        if (IsKeyDown(KEY_ENTER)) {
                            return alt;
                            break;
                        }                         
                        break;
                }
        
                // Printa pergunta e alternativas
                DrawText32Chars(font, head->pergunta, (Vector2){55, 35}, 12, 2, BLACK);
                DrawTextEx(font, head->a, (Vector2){80, 122}, 12, 2, BLACK);
                DrawTextEx(font, head->b, (Vector2){80, 138}, 12, 2, BLACK);
                DrawTextEx(font, head->c, (Vector2){80, 154}, 12, 2, BLACK);
                DrawTextEx(font, head->d, (Vector2){80, 170}, 12, 2, BLACK);
            }
        }
        
        if (!pgtaAtiva) {
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
                position.x -= speed; // Animação do Luigi andando para esquerda e direita
                
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
            } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
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

bool isMusicOver(Music musica) { // Verifica se música acabou
    if((GetMusicTimePlayed(musica)/GetMusicTimeLength(musica)) >= 1) return true;
    if((GetMusicTimePlayed(musica)/GetMusicTimeLength(musica)) <= 0) return true;
    else return false;
}

void loopMusic(Music musica) { // Se música acabar, bota ela em um loop
    if(isMusicOver(musica)) UpdateMusicStream(musica);
}

// Printar até 32 caracteres para caber na tela
void DrawText32Chars(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color color) {
    int y = 0;
    int index = 0;
    while (text[index] != '\0') {
        char substring[33];
        int i;
        for (i = 0; i < 32 && text[index] != '\0'; i++, index++) {
            substring[i] = text[index];
        }
        substring[i] = '\0';

        DrawTextEx(font, substring, (Vector2){position.x, position.y + y * (fontSize + spacing)}, fontSize, spacing, color);
        y++; 
    }
}