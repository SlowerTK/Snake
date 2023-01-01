#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
using namespace std;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum eDirection dir;

int width = 20, height = 20;
int gameover, wall = 1, tailbehavior = 1;
int x, y, fruitx, fruity, score, bscore;
int tailx[100], taily[100];
int counttail = 0;

void setup()
{
    gameover = 0;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void draw()
{
    system("cls");
    int i, j, k;
    for (i = 0; i < width + 2; i++)
    {
        cout << "# ";
    }
    cout << endl;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "# ";
            }
            if (i == y && j == x)
            {
                cout << "O ";
            }
            else if (i == fruity && j == fruitx)
            {
                cout << "* ";
            }
            else
            {
                int print = 0;
                for (k = 0; k < counttail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o ";
                        print = 1;
                    }
                }
                if (print == 0)
                {
                    cout << "  ";
                }
            }
            if (j == width - 1)
            {
                cout << "# ";
            }
        }
        cout << endl;
    }
    for (i = 0; i < width + 2; i++)
    {
        cout << "# ";
    }
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "Best Score: " << bscore << endl;
    cout << "Use WASD to move, X to exit" << endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic()
{
    int i;
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (i = 1; i < counttail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (wall == 1)
    {
        if (x >= width || x < 0 || y >= height || y < 0)
            gameover = 1;
    }
    else
    {
        if (x >= width)
            x = 0;
        else if (x < 0)
            x = width - 1;
        if (y >= height)
            y = 0;
        else if (y < 0)
            y = height - 1;
    }
    if (tailbehavior == 1)
    {
        for (i = 0; i < counttail; i++)
            if (tailx[i] == x && taily[i] == y)
                gameover = 1;
    }
    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        counttail++;
    }
}

void fruitcheck()
{
    int i;
    for (i = 0; i < counttail; i++)
    {
        if (fruitx == tailx[i] && fruity == taily[i])
        {
            fruitx = rand() % width;
            fruity = rand() % height;
            i = 0;
        }
    }
}

int main()
{
    int m, n;
    char c;
    FILE *fp;
    fp = fopen(".\\bestscore.txt", "r");
    if (fp == NULL)
    {
        fp = fopen(".\\bestscore.txt", "w");
        fprintf(fp, "%d", 0);
        fclose(fp);
        fp = fopen(".\\bestscore.txt", "r");
    }
    fscanf(fp, "%d", &bscore);
    fclose(fp);
    srand(time(0));
    cout << "Welcome to Snake Game" << endl;
    cout << "Choose wall behavior" << endl;
    cout << "1. Wall" << endl;
    cout << "2. No wall" << endl;
    cout << "Enter your choice: ";
    cin >> wall;
    system("cls");
    if (wall == 1)
    {
        cout << "Wall is on" << endl;
    }
    else if (wall == 2)
    {
        system("cls");
    }
    else
    {
        cout << "Invalid choice" << endl;
        cout << "Wall is on" << endl;
    }
    if (wall == 1)
    {
        cout << "Choose tail behavior" << endl;
        cout << "1. Tail" << endl;
        cout << "2. No tail" << endl;
        cout << "Enter your choice: ";
        cin >> tailbehavior;
        system("cls");
        if (tailbehavior == 1)
        {
            if (wall == 1)
            {
                cout << "Wall is on" << endl;
                cout << "Tail is on" << endl;
                cout << endl;
            }
            else
            {
                cout << "Wall is off" << endl;
                cout << "Tail is on" << endl;
                cout << endl;
            }
        }
        else if (tailbehavior == 2)
        {
            if (wall == 1)
            {
                cout << "Wall is on" << endl;
                cout << "Tail is off" << endl;
                cout << endl;
            }
            else
            {
                cout << "Wall is off" << endl;
                cout << "Tail is off" << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "Invalid choice" << endl;
            cout << endl;
            if (wall == 1)
            {
                cout << "Wall is on" << endl;
                cout << "Tail is on" << endl;
                cout << endl;
            }
            else
            {
                cout << "Wall is off" << endl;
                cout << "Tail is on" << endl;
                cout << endl;
            }
        }
    }
    else
    {
        cout << "Wall is off" << endl;
        cout << "Tail is on" << endl;
        cout << endl;
    }
    cout << "Choose difficulty level" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> n;
    switch (n)
    {
    case 1:
        m = 100;
        break;
    case 2:
        m = 50;
        break;
    case 3:
        m = 20;
        break;
    case 4:
        exit(0);
    default:
        system("cls");
        cout << "Invalid choice" << endl;
        _getch();
        exit(0);
    }
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        fruitcheck();
        Sleep(m);
    }
    system("cls");
    cout << "Game Over" << endl;
    cout << "Your score is: " << score << endl;
    if (score > bscore)
    {
        bscore = score;
        cout << "New high score" << endl;
        fp = fopen(".\\bestscore.txt", "w");
        fprintf(fp, "%d", bscore);
        fclose(fp);
    }
    cout << "Press any key to exit" << endl;
    _getch();
    return 0;
}