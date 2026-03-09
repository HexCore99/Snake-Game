#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <math.h>
#include <vector>
#include "raylib.h"
using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 780
#define RECT_WIDTH 30
#define RECT_HEIGHT 30
#define FONT_SIZE 30
const int GRID_COLS = SCREEN_WIDTH / RECT_WIDTH;
const int GRID_ROWS = SCREEN_HEIGHT / RECT_HEIGHT;

enum class State
{
    START,
    PAUSE,
    RESUME,
    NEWGAME,
    EXIT,
    GAMEOVER,
};

// global vars
State state = State::START;
bool isPointExists = false;
Rectangle point;
Color food = {232, 116, 81, 255};

float vx = 5;
float vy = 5;
char key;

Sound hoverSound;
Sound clickSound;
Sound gameOver;
Sound eat;
std::string lastHovered = "";

Vector2 dir = {1, 0};
Vector2 nextDir = {1, 0};
float moveTimer = 0.0f;
float moveInterval = 0.10f;
unsigned int score = 0;
Vector4 pos = {(float)(GRID_COLS / 2) * RECT_WIDTH,
               (float)(GRID_ROWS / 2) * RECT_HEIGHT,
               (float)RECT_WIDTH,
               (float)RECT_HEIGHT};

deque<Rectangle> snakeRects = {
    {pos.x, pos.y, pos.z, pos.w},

};
deque<Rectangle> initialSnakeRects = snakeRects;

struct Button
{
    Rectangle bounds;
    std::string label;
    State targetState;
    int fontSize = FONT_SIZE;
    Color fillColor = WHITE;
    Color hoverCOlor = LIGHTGRAY;
    Color textColor = BLACK;

    bool isHovered() const
    {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    bool isClicked() const
    {
        return isHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    void render() const
    {
        Color currentColor = isHovered() ? hoverCOlor : fillColor;
        DrawRectangleRec(bounds, currentColor);

        int textWidth = MeasureText(label.c_str(), fontSize);
        float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
        float textY = bounds.y + (bounds.height - fontSize) / 2.0f;
        DrawText(label.c_str(), (int)textX, (int)textY, fontSize, textColor);
    }
};

// Declarations
void renderSnake();
bool hitsBoundary();
void randomPoints();
void showScore();
void move();
bool hitSelf(const Rectangle &newHead, bool willGrow);
void drawBoardBackground();
void drawMenu();
void reset();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Don't be a Snake");
    InitAudioDevice();
    hoverSound = LoadSound("assets/hover2.mp3");
    clickSound = LoadSound("assets/hover4.mp3");
    gameOver = LoadSound("assets/gameOverKid.mp3");
    eat = LoadSound("assets/eating.wav");

    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    randomPoints();
    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_W) && dir.y != 1)
            nextDir = {0, -1};
        if (IsKeyPressed(KEY_S) && dir.y != -1)
            nextDir = {0, 1};
        if (IsKeyPressed(KEY_A) && dir.x != 1)
            nextDir = {-1, 0};
        if (IsKeyPressed(KEY_D) && dir.x != -1)
            nextDir = {1, 0};
        if (IsKeyPressed(KEY_ESCAPE))
        {
            if (state == State::RESUME)
            {
                state = State::PAUSE;
            }

            else if (state == State::PAUSE)
            {
                state = State::RESUME;
            }
        }

        if (state == State::RESUME)
        {
            moveTimer += GetFrameTime();
            if (moveTimer >= moveInterval)
            {
                moveTimer = 0.0f;
                if (!hitsBoundary())
                {
                    dir = nextDir;
                    move();
                }
            }
        }

        BeginDrawing();

        if (state == State::PAUSE || state == State::GAMEOVER || state == State::START)
        {
            drawMenu();
        }
        else
        {
            drawBoardBackground();
            showScore();
            renderSnake();
            DrawRectangleRec(point, food);
        }

        EndDrawing();
        if (state == State::EXIT && !IsSoundPlaying(clickSound))
            break;
    }

    UnloadSound(hoverSound);
    UnloadSound(clickSound);
    CloseWindow();
    return 0;
}
// Definitions
void renderSnake()
{
    Color snakeHead = {170, 196, 200, 255};
    Color snakeBodyA = {126, 156, 162, 255};
    Color snakeBodyB = {108, 138, 146, 255};
    Color snakeOutline = {44, 60, 66, 255};

    DrawRectangleRec(snakeRects[0], snakeHead);
    DrawRectangleLinesEx(snakeRects[0], 2, snakeOutline);
    for (int i = 1; i < snakeRects.size(); i++)
    {
        Color bodyColor = (i % 2) == 0 ? snakeBodyA : snakeBodyB;
        DrawRectangleRec(snakeRects[i], bodyColor);
        DrawRectangleLinesEx(snakeRects[i], 1.5f, snakeOutline);
    }
}
bool hitsBoundary()
{

    if (snakeRects[0].y < 0 || snakeRects[0].x < 0 ||
        snakeRects[0].x > SCREEN_WIDTH - RECT_WIDTH ||
        snakeRects[0].y > SCREEN_HEIGHT - RECT_HEIGHT)
    {
        state = State::GAMEOVER;
        PlaySound(gameOver);
        return true;
    }

    return false;
}

void randomPoints()
{
    bool pointCollidedWithSnake = true;

    while (pointCollidedWithSnake)
    {
        int col = GetRandomValue(0, GRID_COLS - 1);
        int row = GetRandomValue(0, GRID_ROWS - 1);
        point = {(float)(col * RECT_WIDTH), (float)(row * RECT_HEIGHT), (float)RECT_WIDTH, (float)RECT_HEIGHT};
        pointCollidedWithSnake = false;

        for (const Rectangle &rect : snakeRects)
        {
            if (CheckCollisionRecs(point, rect))
            {
                pointCollidedWithSnake = true;
                break;
            }
        }
    }
}

void move()
{
    Rectangle newHead = snakeRects.front();
    newHead.x += dir.x * RECT_WIDTH;
    newHead.y += dir.y * RECT_HEIGHT;

    bool willGrow = CheckCollisionRecs(newHead, point);

    if (hitSelf(newHead, willGrow))
    {
        state = State::GAMEOVER;
        PlaySound(gameOver);
        return;
    }

    snakeRects.push_front(newHead);

    if (!willGrow)
        snakeRects.pop_back();
    else
    {
        PlaySound(eat);
        score += 10;
        randomPoints();
    }
}

void showScore()
{
    std::string scoreText = "Score: " + std::to_string(score);
    int textW = MeasureText(scoreText.c_str(), FONT_SIZE);
    //~
    DrawText(scoreText.c_str(), SCREEN_WIDTH - textW - 10, 10, FONT_SIZE, WHITE);
}

bool hitSelf(const Rectangle &newHead, bool willGrow)
{
    int limit = snakeRects.size();
    if (limit > 0 && !willGrow)
        limit -= 1;
    for (int i = 0; i < limit; i++)
    {
        if (CheckCollisionRecs(newHead, snakeRects[i]))
            return true;
    }
    return false;
}

void drawBoardBackground()
{
    Color darkGrass = {18, 34, 38, 255};
    Color lightGrass = {28, 52, 58, 255};
    Color gridLine = {62, 96, 102, 110};
    ClearBackground({16, 30, 32, 255});

    for (int y = 0; y < SCREEN_HEIGHT; y += RECT_HEIGHT)
    {
        for (int x = 0; x < SCREEN_WIDTH; x += RECT_WIDTH)
        {
            bool alternate = ((x / RECT_WIDTH) + (y / RECT_HEIGHT)) % 2 == 0;
            DrawRectangle(x, y, RECT_WIDTH, RECT_HEIGHT, alternate ? darkGrass : lightGrass);
            DrawRectangleLines(x, y, RECT_WIDTH, RECT_HEIGHT, gridLine);
        }
    }
}

void drawMenu()
{
    const float widthRatio = 0.35;
    const float heightRatio = 0.60;
    // Draw Menu Container
    float menuWidth = SCREEN_WIDTH * widthRatio;
    float menuHeight = SCREEN_HEIGHT * heightRatio;
    float menuX = (SCREEN_WIDTH - menuWidth) / 2.0f;
    float menuY = (SCREEN_HEIGHT - menuHeight) / 2.0f;

    Rectangle menuContainer = {
        menuX,
        menuY,
        menuWidth,
        menuHeight,
    };

    ClearBackground({12, 28, 18, 255});
    // Color menuPanelColor = {58, 74, 46, 255};
    // DrawRectangleRec(menuContainer, menuPanelColor);

    // Init Buttons
    const float buttondWidth = menuWidth - 120.0f;
    const float buttondHeight = 60.0f;
    const float buttonGap = 18.0f;
    const float buttonX = menuX + (menuWidth - buttondWidth) / 2.0f;
    const float firstButtonY = menuY + 90.0f;

    std::vector<Button> buttons = {
        {{buttonX, firstButtonY + 0 * (buttondHeight + buttonGap), buttondWidth, buttondHeight}, "RESUME", State::RESUME},
        {{buttonX, firstButtonY + 0 * (buttondHeight + buttonGap), buttondWidth, buttondHeight}, "START", State::START},

        {{buttonX, firstButtonY + 1 * (buttondHeight + buttonGap), buttondWidth, buttondHeight}, "NEWGAME", State::NEWGAME},

        {{buttonX, firstButtonY + 2 * (buttondHeight + buttonGap), buttondWidth, buttondHeight}, "EXIT", State::EXIT},
    };

    std::string hoveredNow = "";
    // render buttons
    for (const Button &button : buttons)
    {
        if ((state == State::GAMEOVER && button.label == "RESUME") || (state == State::START && button.label == "RESUME") || (state != State::START && button.label == "START"))

        {
            continue;
        }
        button.render();
        if (button.isHovered())
        {
            hoveredNow = button.label;
        }
    }

    if (!hoveredNow.empty() && hoveredNow != lastHovered)
    {
        PlaySound(hoverSound);
    }
    lastHovered = hoveredNow;

    // configure Actions
    for (const Button &button : buttons)
    {
        if (!button.isClicked())
        {
            continue;
        }
        lastHovered = "";
        PlaySound(clickSound);
        switch (button.targetState)
        {
        case State::START:
            state = State::RESUME;
            break;
        case State::RESUME:
            state = State::RESUME;
            break;
        case State::NEWGAME:
            reset();
            break;
        case State::EXIT:
            state = State::EXIT;
            break;

        default:
            break;
        }
    }
}
void reset()
{
    snakeRects = initialSnakeRects;
    score = 0;
    dir = {1, 0};
    nextDir = {1, 0};

    moveTimer = 0.0f;
    moveInterval = 0.10f;
    score = 0;
    state = State::RESUME;
}

/*
TODO:
    1. When snake cover whole Window what happens to the randomPoints()??
*/

/*
Completed:
    1. Snake & Points Overlaps
    2.Pause/End/Start Screen.
    3.Add Sound
    4.Grid based movement
*/
