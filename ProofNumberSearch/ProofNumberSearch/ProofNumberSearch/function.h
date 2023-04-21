#pragma once
#pragma once

enum Type
{
    AND,
    OR
};
enum Value
{
    TRUE,
    FALSE,
    UNKNOWN
};
struct NODE
{
    char** board = nullptr;
    char activePlayer;
    int freeTitles;
    int proof = 1;
    int disproof = 1;
    int seria = 0;
    Value value = UNKNOWN;
    Type type = OR;
    bool expanded = false;
    NODE* parent = nullptr;
    NODE* sibling = nullptr;
    NODE* children = nullptr;
    NODE(char** board, int freeTitles, char activePlayer, int seria, Type type);
    void deleteSubtree();
};
void evaluate(NODE* root);
bool PN(NODE* root);
void setProofAndDisproofNumbers(NODE* node);
NODE* SelectMostProvingNode(NODE* node);
void expandNode(NODE* node);
NODE* updateAncestors(NODE* node, NODE* root);
void generateAllChildren(NODE* node);
void rightDiagonal(char** gametab, bool& rightDiagonal_one, bool& rightDiagonal_two, int i, int j, int g, int wysokosc, int szerokosc, bool& next);
void leftDiagonal(char** gametab, bool& leftDiagonal_one, bool& leftDiagonal_two, int i, int j, int g, int wysokosc, int szerokosc, bool& next);
void x_check(char** gametab, bool& x_one, bool& x_two, int i, int j, int g, int szerokosc, bool& next);
void y_check(char** gametab, bool& y_one, bool& y_two, int i, int j, int g, int wysokosc, bool& next);
char opositeplayer(char p);
char won_now(NODE& root);
void killAllChildren(NODE* child);
void editroot(char player);
void setWidthHeight(int xszerokosc, int xwysokosc);