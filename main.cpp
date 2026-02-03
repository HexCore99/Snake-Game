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
void handleKeyPressed(char key);
void renderSnake();
void moveUp();
void moveLeft();
void moveRight();
void moveBottom();
bool hasNeighbour(char pressedKey);
bool hitsBoundary(char pressedKey);
void randomPoints();
void increaseSize();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Don't be a Snake");
    SetTargetFPS(60);

    float speed = 200.0f;
    Vector2 dir = {1, 0};

    while (!WindowShouldClose())
    {
        int k = GetKeyPressed();

        if (IsKeyDown(KEY_W))
            dir = {0, -1};
        if (IsKeyDown(KEY_S))
            dir = {0, 1};

        if (IsKeyDown(KEY_A))
            dir = {-1, 0};
        if (IsKeyDown(KEY_D))
            dir = {1, 0};
        float dt = GetFrameTime();
        rects[0].x += dir.x * speed * dt;
        rects[0].y += dir.y * speed * dt;

        for (int i = 1; i < rects.size(); i++)
        {
            Vector2 prev = {rects[i - 1].x, rects[i - 1].y};
            Vector2 curr = {rects[i].x, rects[i].y};
            Vector2 delta = {prev.x - curr.x, prev.y - curr.y};
            float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);

            if (dist > RECT_WIDTH)
            {
                float t = (dist - RECT_WIDTH) / dist;
                rects[i].x += delta.x * t;
                rects[i].y += delta.y * t;
            }
        }

        handleKeyPressed(key);
        BeginDrawing();
        ClearBackground(BLACK);
        renderSnake();
        if (!isPointExists)
        {
            randomPoints();
            DrawRectangleRec(point, RED);
            isPointExists = true;
        }
        else
        {
            DrawRectangleRec(point, RED);
        }

        if (CheckCollisionRecs(rects[0], point))
        {
            increaseSize();
            isPointExists = false;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void handleKeyPressed(char key)
{
    switch (key)
    {
    case 'W':
        if (hitsBoundary(key) || hasNeighbour(key))
            return;
        moveUp();
        break;

    case 'A':
        if (hitsBoundary(key) || hasNeighbour(key))
            return;
        moveLeft();
        break;

    case 'S':
        if (hitsBoundary(key) || hasNeighbour(key))
            return;
        moveBottom();
        break;
    case 'D':
        if (hitsBoundary(key) || hasNeighbour(key))
            return;
        moveRight();
        break;

    default:
        break;
    }
    // if (IsKeyPressed(KEY_W))
    // {
    //     if (hitsBoundary('W') || hasNeighbour('W'))
    //         return;
    //     moveUp();
    // }
    // if (IsKeyPressed(KEY_A))
    // {
    //     if (hitsBoundary('A') || hasNeighbour('A'))
    //         return;
    //     moveLeft();
    // }
    // if (IsKeyPressed(KEY_S))
    // {
    //     if (hitsBoundary('S') || hasNeighbour('S'))
    //         return;
    //     moveBottom();
    // }
    // if (IsKeyPressed(KEY_D))
    // {
    //     if (hitsBoundary('D') || hasNeighbour('D'))
    //         return;
    //     moveRight();
    // }
}

void renderSnake()
{
    DrawRectangleRec(rects[0], WHITE);
    for (int i = 1; i < rects.size(); i++)
    {
        DrawRectangleRec(rects[i], BROWN);
    }
}
void moveUp()
{
    Rectangle tempRect = rects[0];
    rects[0].y -= vy;

    for (int i = 1; i < rects.size(); i++)
    {
        Rectangle temp2 = tempRect;
        tempRect = rects[i];
        rects[i] = temp2;
    }
}

void moveLeft()
{

    Rectangle tempRect = rects[0];
    rects[0].x -= vx;

    for (int i = 1; i < rects.size(); i++)
    {
        Rectangle temp2 = tempRect;
        tempRect = rects[i];
        rects[i] = temp2;
    }
}

void moveRight()
{
    Rectangle tempRect = rects[0];
    rects[0].x += vx;

    for (int i = 1; i < rects.size(); i++)
    {
        Rectangle temp2 = tempRect;
        tempRect = rects[i];
        rects[i] = temp2;
    }
}

void moveBottom()
{
    Rectangle tempRect = rects[0];
    rects[0].y += vy;

    for (int i = 1; i < rects.size(); i++)
    {
        Rectangle temp2 = tempRect;
        tempRect = rects[i];
        rects[i] = temp2;
    }
}

bool hitsBoundary(char pressedKey)
{

    switch (pressedKey)
    {
    case 'W':

        if (rects[0].y < 1)
            return true;
        // cout << "Top Boundary Hit\n";
        break;
    case 'A':

        if (rects[0].x < 0)
            return true;
        // cout << "Left Boundary Hit\n";
        break;
    case 'D':
        if (rects[0].x >= SCREEN_WIDTH - RECT_WIDTH)
            return true;
        // cout << "Right Boundary Hit\n";
        break;
    case 'S':
        if (rects[0].y >= SCREEN_HEIGHT - RECT_HEIGHT)
            return true;
        // cout << "Bottom Boundary Hit\n";
        break;

    default:
        break;
    }
    return false;
}

bool hasNeighbour(char pressedKey)
{
    switch (pressedKey)
    {
    case 'W':

        for (int i = 0; i < rects.size(); i++)
        {
            if (rects[i].x == rects[0].x && rects[i].y == rects[0].y - RECT_HEIGHT)
            {
                cout << "top rectangle exists\n";
                return true;
            }
        }
        break;
    case 'A':

        for (int i = 0; i < rects.size(); i++)
        {
            if (rects[i].x == rects[0].x - RECT_WIDTH && rects[i].y == rects[0].y)
            {
                cout << "Left rectangle exists\n";
                return true;
            }
        }
        break;
    case 'D':

        for (int i = 0; i < rects.size(); i++)
        {
            if (rects[i].x == rects[0].x + RECT_WIDTH && rects[i].y == rects[0].y)
            {
                cout << "Right rectangle exists\n";
                return true;
            }
        }

        break;
    case 'S':
        for (int i = 0; i < rects.size(); i++)
        {
            if (rects[i].x == rects[0].x && rects[i].y == rects[0].y + RECT_HEIGHT)
            {
                cout << "Bottom rectangle exists\n";
                return true;
            }
        }
        break;

    default:
        break;
    }
    return false;
}

void randomPoints()
{
    float rect_x = GetRandomValue(0, SCREEN_WIDTH - RECT_WIDTH);
    float rect_y = GetRandomValue(0, SCREEN_HEIGHT - RECT_HEIGHT);
    point = {rect_x, rect_y, RECT_WIDTH, RECT_HEIGHT};
}

void increaseSize()
{
    Rectangle tail = rects.back();
    Rectangle beforeTail = rects[rects.size() - 2];
    float dx = tail.x - beforeTail.x;
    float dy = tail.y - beforeTail.y;

    Rectangle newTail = {
        tail.x + dx,
        tail.y + dy,
        tail.width,
        tail.height};
    rects.push_back(newTail);
}