#pragma once
char opositeplayer(char p);
void ClearBoard(char** gametab, int szerokosc);
void print(char** gametab, int szerokosc, int wysokosc);
void rightDiagonal(char** gametab, bool& rightDiagonal_one, bool& rightDiagonal_two, int i, int j, int g, int wysokosc, int szerokosc, bool& next);
void leftDiagonal(char** gametab, bool& leftDiagonal_one, bool& leftDiagonal_two, int i, int j, int g, int wysokosc, int szerokosc, bool& next);
void x_check(char** gametab, bool& x_one, bool& x_two, int i, int j, int g, int szerokosc, bool& next);
void y_check(char** gametab, bool& y_one, bool& y_two, int i, int j, int g, int wysokosc, bool& next);
int won_now(char** gametab, int szerokosc, int wysokosc, int k);
void GEN_ALL_POS_MOV(char** gametab, int szerokosc, int wysokosc, int k, char p);
int overidezero(char** gametab, int szerokosc, int wysokosc, int k, char p, bool toprint);
int jeszczeraz(char** gametab, int szerokosc, int wysokosc, int k, char p, int freePos);