#pragma once
#include "function.h"
#include <stdio.h>
using namespace std;
char opositeplayer(char p)
{
    if (p == '1')
        return '2';
    if (p == '2')
        return '1';
    return '0';
}
void ClearBoard(char** gametab, int szerokosc)
{
    for (short i = 0; i < szerokosc; i++)
    {
        delete[] gametab[i];
    }
}
void print(char** gametab, int szerokosc, int wysokosc)
{

    for (int j = 0; j < wysokosc; j++)
    {
        for (int i = 0; i < szerokosc; i++)
        {
            printf("%c ", gametab[i][j]);
        }
        printf("\n");
    }
}

void rightDiagonal(char** gametab, bool& rightDiagonal_one, bool& rightDiagonal_two, int i, int j, int g, int wysokosc, int szerokosc, bool& next)
{
    if ((rightDiagonal_one || rightDiagonal_two))
    {
        if (!(i + g < szerokosc && j + g < wysokosc))
        {
            rightDiagonal_two = false;
            rightDiagonal_one = false;
        }
        else
        {
            switch (gametab[i + g][j + g])
            {
            default:
                break;
            case '0':
                if (next)
                {
                    next = false;
                    break;
                }
                rightDiagonal_two = false;
                rightDiagonal_one = false;
                break;
            case '1':
                rightDiagonal_two = false;
                break;
            case '2':
                rightDiagonal_one = false;
                break;
            }
        }
    }
}
void leftDiagonal(char** gametab, bool& leftDiagonal_one, bool& leftDiagonal_two, int i, int j, int g, int wysokosc, int szerokosc, bool& next)
{
    if ((leftDiagonal_one || leftDiagonal_two))
    {
        if (!(i - g >= 0 && j + g < wysokosc))
        {
            leftDiagonal_two = false;
            leftDiagonal_one = false;
        }
        else
        {
            switch (gametab[i - g][j + g])
            {
            default:
                break;
            case '0':
                if (next)
                {
                    next = false;
                    break;
                }
                leftDiagonal_two = false;
                leftDiagonal_one = false;
                break;
            case '1':
                leftDiagonal_two = false;
                break;
            case '2':
                leftDiagonal_one = false;
                break;
            }
        }
    }
}
void x_check(char** gametab, bool& x_one, bool& x_two, int i, int j, int g, int szerokosc, bool& next)
{
    if ((x_one || x_two))
    {
        if (!(i + g < szerokosc))
        {
            x_two = false;
            x_one = false;
        }
        else
        {
            switch (gametab[i + g][j])
            {
            default:
                break;
            case '0':
                if (next)
                {
                    next = false;
                    break;
                }
                x_two = false;
                x_one = false;
                break;
            case '1':
                x_two = false;
                break;
            case '2':
                x_one = false;
                break;
            }
        }
    }
}
void y_check(char** gametab, bool& y_one, bool& y_two, int i, int j, int g, int wysokosc, bool& next)
{
    if ((y_one || y_two))
    {
        if (!(j + g < wysokosc))
        {
            y_two = false;
            y_one = false;
        }
        else
        {
            switch (gametab[i][j + g])
            {
            default:
                break;
            case '0':
                if (next)
                {
                    next = false;
                    break;
                }
                y_two = false;
                y_one = false;
                break;
            case '1':
                y_two = false;
                break;
            case '2':
                y_one = false;
                break;
            }
        }
    }
}
int won_now(char** gametab, int szerokosc, int wysokosc, int k)
{
    for (int j = 0; j < wysokosc; j++)
    {
        for (int i = 0; i < szerokosc; i++)
        {
            bool x_one = true, y_one = true, leftDiagonal_one = true, rightDiagonal_one = true;
            bool x_two = true, y_two = true, leftDiagonal_two = true, rightDiagonal_two = true;
            bool contin = true;
            bool next = false;
            switch (gametab[i][j])
            {
            default:
                break;
            case '0':
                x_one = false, y_one = false, leftDiagonal_one = false, rightDiagonal_one = false;
                x_two = false, y_two = false, leftDiagonal_two = false, rightDiagonal_two = false;
                continue;
                break;
            case '1':
                x_two = false, y_two = false, leftDiagonal_two = false, rightDiagonal_two = false;
                break;
            case '2':
                x_one = false, y_one = false, leftDiagonal_one = false, rightDiagonal_one = false;
                break;
            }
            if (j > wysokosc - k)
            {
                y_two = false;
                y_one = false;
                rightDiagonal_two = false;
                rightDiagonal_one = false;
                leftDiagonal_two = false;
                leftDiagonal_one = false;
                if (x_one || x_two)
                {

                    for (int g = 1; g < k; g++)
                    {
                        bool next = false;
                        x_check(gametab, x_one, x_two, i, j, g, szerokosc, next);

                        if (!x_one && !y_one && !leftDiagonal_one && !rightDiagonal_one && !x_two && !y_two && !leftDiagonal_two && !rightDiagonal_two)
                            break;
                    }
                }
                contin = false;
            }
            if (contin && i > szerokosc - k)
            {
                x_two = false;
                x_one = false;
                rightDiagonal_two = false;
                rightDiagonal_one = false;
                if (y_one || y_two || leftDiagonal_one || leftDiagonal_two)
                {
                    for (int g = 1; g < k; g++)
                    {
                        bool next = false;
                        y_check(gametab, y_one, y_two, i, j, g, wysokosc, next);
                        leftDiagonal(gametab, leftDiagonal_one, leftDiagonal_two, i, j, g, wysokosc, szerokosc, next);

                        if (!x_one && !y_one && !leftDiagonal_one && !rightDiagonal_one && !x_two && !y_two && !leftDiagonal_two && !rightDiagonal_two)
                            break;
                    }
                }
                contin = false;
            }
            if (contin)
            {
                for (int g = 1; g < k; g++)
                {
                    rightDiagonal(gametab, rightDiagonal_one, rightDiagonal_two, i, j, g, wysokosc, szerokosc, next);
                    leftDiagonal(gametab, leftDiagonal_one, leftDiagonal_two, i, j, g, wysokosc, szerokosc, next);
                    y_check(gametab, y_one, y_two, i, j, g, wysokosc, next);
                    x_check(gametab, x_one, x_two, i, j, g, szerokosc, next);

                    if (!x_one && !y_one && !leftDiagonal_one && !rightDiagonal_one && !x_two && !y_two && !leftDiagonal_two && !rightDiagonal_two)
                        break;
                }
            }
            if (x_one || y_one || leftDiagonal_one || rightDiagonal_one)
                return 1;
            if (x_two || y_two || leftDiagonal_two || rightDiagonal_two)
                return 2;
        }
    }
    return 0;

}

void GEN_ALL_POS_MOV(char** gametab, int szerokosc, int wysokosc, int k, char p)
{
    for (int j = 0; j < wysokosc; j++)
    {
        for (int i = 0; i < szerokosc; i++)
        {
            if (gametab[i][j] == '0')
            {
                gametab[i][j] = p;
                print(gametab, szerokosc, wysokosc);
                gametab[i][j] = '0';
            }
        }
    }
}

int overidezero(char** gametab, int szerokosc, int wysokosc, int k, char p, bool toprint)
{
    int win = won_now(gametab, szerokosc, wysokosc, k);
    if (win != 0)
    {
        if (toprint)
            printf("0\n");
        return win;
    }
    for (int j = 0; j < wysokosc; j++)
    {
        for (int i = 0; i < szerokosc; i++)
        {
            if (gametab[i][j] == '0')
            {
                gametab[i][j] = p;
                win = won_now(gametab, szerokosc, wysokosc, k);
                if (win != 0)
                {
                    if (toprint)
                    {
                        printf("1\n");
                        print(gametab, szerokosc, wysokosc);
                    }
                    else
                        gametab[i][j] = '0';
                    return win;
                }
                else
                {
                    gametab[i][j] = '0';

                }
            }
        }
    }
    return 0;
}
int jeszczeraz(char** gametab, int szerokosc, int wysokosc, int k, char p, int freePos)
{

    bool zero = false;
    int solve = 0;
    int licznik_solve = 0;
    int win = overidezero(gametab, szerokosc, wysokosc, k, p, false);
    if (win != 0)
    {
        return win;
    }
    if (freePos == 1)
    {
        return 0;
    }
    for (int j = 0; j < wysokosc; j++)
    {
        for (int i = 0; i < szerokosc; i++)
        {
            if (gametab[i][j] != '0')
                continue;

            gametab[i][j] = p;
            freePos--;
            if (overidezero(gametab, szerokosc, wysokosc, k, opositeplayer(p), false) == p - 48)
            {
                gametab[i][j] = '0';
                return p - 48;
            }

            solve = jeszczeraz(gametab, szerokosc, wysokosc, k, opositeplayer(p), freePos);
            if (solve == 0)
                zero = true;

            if (solve == p - 48)
            {
                licznik_solve++;
                gametab[i][j] = '0';
                return solve;
            }

            else
            {
                gametab[i][j] = '0';
                freePos++;
            }
        }
    }
    if (zero)
        return 0;
    return solve;
}