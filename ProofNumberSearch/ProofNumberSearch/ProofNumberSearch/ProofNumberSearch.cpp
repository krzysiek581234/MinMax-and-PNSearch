#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <string.h>
#include <iostream>
#include "function.h"
using namespace std;

void freememory(char** gametab, int wysokosc, int szerokosc)
{
    for (int i = 0; i < wysokosc; i++)
    {
        delete[] gametab[i];
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    char komenda[50];
    // szerokosc -> n
    // wysokosc  -> m
    int szerokosc, wysokosc;
    int k;
    char player;
    char** gametab;
    int freePos = 0;
    while (scanf("%s", komenda) == 1)
    {
        scanf("%d %d %d %c\n", &wysokosc, &szerokosc, &k, &player);
        freePos = 0;
        gametab = new char* [wysokosc];
        for (int i = 0; i < wysokosc; i++)
        {
            gametab[i] = new char[szerokosc];
        }
        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j < szerokosc; j++)
            {
                do
                {
                    scanf("%c", &gametab[i][j]);
                } while (gametab[i][j] != '0' && gametab[i][j] != '1' && gametab[i][j] != '2');
                if (gametab[i][j] == '0')
                    freePos++;
            }
        }
        if (strcmp(komenda, "SOLVE_GAME_STATE") == 0)
        {
            setWidthHeight(szerokosc, wysokosc);
            NODE* kopiec = new NODE(gametab, freePos, player, k, OR);
            NODE* kopiec2 = new NODE(gametab, freePos, player, k, AND);
            editroot(player);
            bool solve = PN(kopiec);



            //remis

            if (solve == true)
            {
                if (player == '1')
                    printf("FIRST_PLAYER_WINS\n");
                else if (player == '2')
                    printf("SECOND_PLAYER_WINS\n");
            }
            else
            {

                editroot(opositeplayer(player));
                bool solve2 = PN(kopiec2);
                if (solve2 == true)
                {
                    if (player == '2')
                        printf("FIRST_PLAYER_WINS\n");
                    else if (player == '1')
                        printf("SECOND_PLAYER_WINS\n");
                }
                else if (solve == false && solve2 == false)
                    printf("BOTH_PLAYERS_TIE\n");
            }
            kopiec->deleteSubtree();
            kopiec2->deleteSubtree();
            freememory(gametab, wysokosc, szerokosc);
        }
    }
}