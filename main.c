#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int width = 20, height = 20;
int gameover;
int x, y, fruitx, fruity, score, bscore;
int tailx[100], taily[100];
int counttail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

void setup()
{
    gameover = 0;
    dir = STOP;
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
        printf("# ");
    printf("\n");

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (j == 0)
                printf("# ");
            if (i == y && j == x)
                printf("O ");
            else if (i == fruity && j == fruitx)
                printf("* ");
            else
            {
                int print = 0;
                for (k = 0; k < counttail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        printf("o ");
                        print = 1;
                    }
                }
                if (print == 0)
                    printf("  ");
            }

            if (j == width - 1)
                printf("# ");
        }
        printf("\n");
    }

    for (i = 0; i < width + 2; i++)
        printf("# ");
    printf("\n");
    printf("Score: %d \n", score);
    printf("Best score: %d \n", bscore);
    printf("Use WASD to move, X to exit \n");
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
    //if (x > width || x < 0 || y > height || y < 0)
    //    gameover = 1;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    for (i = 0; i < counttail; i++)
        if (tailx[i] == x && taily[i] == y)
            gameover = 1;
    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        counttail++;
    }
}

int main()
{
    int m, n;
    char c;
    FILE *fp;
    fp = fopen(".\\score\\bestscore.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        _getch();
        exit(1);
    }
    fscanf(fp, "%d", &bscore);
    fclose(fp);
    srand(time(NULL));
    printf("Welcome to Snake Game \n");
    printf("Choose difficulty level: \n");
    printf(" 1. Easy \n 2. Medium \n 3. Hard \n 4. Exit \n Enter your choice: ");
    scanf("%d", &n);
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
        printf("Invalid choice");
        _getch();
        exit(0);
    }
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep(m);
    }
    system("cls");
    printf("Game Over \n Score: %d", score);
    printf(" \nBest score: %d", bscore);
    if (score > bscore)
    {
        bscore = score;
        fp = fopen(".\\score\\bestscore.txt", "w");
        if (fp == NULL)
        {
            printf("Error opening file");
            _getch();
            exit(1);
        }
        fprintf(fp, "%d", bscore);
        fclose(fp);
    }
    printf(" \n Press any key to exit");
    _getch();
    return 0;
}
