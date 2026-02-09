#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <math.h>
#include "raylib.h"
using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define RECT_WIDTH 30
#define RECT_HEIGHT 30
#define FONT_SIZE 30

bool isPointExists = false;
Rectangle point;
float vx = 5;
float vy = 5;
char key;

Vector4 pos = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RECT_WIDTH, RECT_HEIGHT};

deque<Rectangle> rects = {
    {pos.x, pos.y, pos.z, pos.w},
    {pos.x - pos.z, pos.y, pos.z, pos.w},
    {pos.x - 2 * pos.z, pos.y, pos.z, pos.w},
    {pos.x - 3 * pos.z, pos.y, pos.z, pos.w},
    {pos.x - 4 * pos.z, pos.y, pos.z, pos.w},
    {pos.x - 5 * pos.z, pos.y, pos.z, pos.w},
    {pos.x - 6 * pos.z, pos.y, pos.z, pos.w},
    {pos.x - 7 * pos.z, pos.y, pos.z, pos.w},
};

// Definition
void renderSnake();
bool hitsBoundary();
void randomPoints();
void showScore();
void move();
bool hitSelf(
    const Rectangle &newHead, bool willGrow);

Vector2 dir = {1,
               0};
Vector2 nextDir = {1, 0};

float moveTimer = 0.0f;
float moveInterval = 0.10f;
unsigned int score = 0;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Don't be a Snake");
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
        BeginDrawing();
        ClearBackground(BLACK);
        showScore();
        renderSnake();
        DrawRectangleRec(point, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void renderSnake()
{
    DrawRectangleRec(rects[0], WHITE);
    for (int i = 1; i < rects.size(); i++)
    {
        DrawRectangleRec(rects[i], BROWN);
    }
}
bool hitsBoundary()
{

    if (rects[0].y < 1 || rects[0].x < 0 ||
        rects[0].x >= SCREEN_WIDTH - RECT_WIDTH ||
        rects[0].y >= SCREEN_HEIGHT - RECT_HEIGHT)
    {
        return true;
    }

    return false;
}

void randomPoints()
{
    float rect_x = GetRandomValue(0, SCREEN_WIDTH - RECT_WIDTH);
    float rect_y = GetRandomValue(0, SCREEN_HEIGHT - RECT_HEIGHT);
    point = {rect_x, rect_y, RECT_WIDTH, RECT_HEIGHT};
}

void move()
{
    Rectangle newHead = rects.front();
    newHead.x += dir.x * RECT_WIDTH;
    newHead.y += dir.y * RECT_HEIGHT;

    bool willGrow = CheckCollisionRecs(newHead, point);

    if (hitSelf(newHead, willGrow))
    {
        return;
    }

    rects.push_front(newHead);

    if (!willGrow)
        rects.pop_back();
    else
    {
        score += 10;
        randomPoints();
    }
}

void showScore()
{
    std::string scoreText = "Score: " + std::to_string(score);
    int textW = MeasureText(scoreText.c_str(), FONT_SIZE);
    DrawText(scoreText.c_str(), SCREEN_WIDTH - textW - 10, 10, FONT_SIZE, WHITE);
}

bool hitSelf(const Rectangle &newHead, bool willGrow)
{
    int limit = rects.size();
    if (limit > 0 && !willGrow)
        limit -= 1;
    for (int i = 0; i < limit; i++)
    {
        if (CheckCollisionRecs(newHead, rects[i]))
            return true;
    }
    return false;
}

/*
TODO:
    1. Snake & Points Overlaps
    2.Snake & Points Overlaps with Score
    3.Pause/End/Start Screen.

*/