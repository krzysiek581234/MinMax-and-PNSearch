#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <string.h>
#include <iostream>
#include "function.h"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    char komenda[50];
    // szerokosc -> n
    // wysokosc  -> m
    int szerokosc, wysokosc;
    int k;
    char p;
    char** gametab;
    int freePos = 0;
    while (scanf("%s", komenda) == 1)
    {
        scanf("%d %d %d %c\n", &wysokosc, &szerokosc, &k, &p);
        freePos = 0;
        gametab = new char* [szerokosc];
        for (int i = 0; i < szerokosc; i++)
        {
            gametab[i] = new char[wysokosc];
        }
        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j < szerokosc; j++)
            {
                do
                {
                    scanf("%c", &gametab[j][i]);
                } while (gametab[j][i] != '0' && gametab[j][i] != '1' && gametab[j][i] != '2');
                if (gametab[j][i] == '0')
                    freePos++;
            }
        }
        if (strcmp(komenda, "GEN_ALL_POS_MOV") == 0)
        {
            if (won_now(gametab, szerokosc, wysokosc, k) != 0)
                printf("0\n");
            else
            {
                printf("%d \n", freePos);
                GEN_ALL_POS_MOV(gametab, szerokosc, wysokosc, k, p);
            }
        }
        else if (strcmp(komenda, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
        {
            if (overidezero(gametab, szerokosc, wysokosc, k, p, true) == 0)
            {
                printf("%d \n", freePos);
                GEN_ALL_POS_MOV(gametab, szerokosc, wysokosc, k, p);
            }
        }
        else if (strcmp(komenda, "SOLVE_GAME_STATE") == 0)
        {
            int solve = jeszczeraz(gametab, szerokosc, wysokosc, k, p, freePos);
            if (solve == 0)
                printf("BOTH_PLAYERS_TIE\n");
            else if (solve == 1)
                printf("FIRST_PLAYER_WINS\n");
            else if (solve == 2)
                printf("SECOND_PLAYER_WINS\n");
        }
    }
}