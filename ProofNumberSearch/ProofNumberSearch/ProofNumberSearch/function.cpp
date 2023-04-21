#include "function.h"
#include <iostream>
constexpr int INF = 9999;
extern char rootplayer = '1';
extern int wysokosc = 0;
extern int szerokosc = 0;
NODE::NODE(char** board, int freeTitles, char activePlayer, int seria, Type type)
{
    this->board = board;
    this->freeTitles = freeTitles;
    this->activePlayer = activePlayer;
    this->seria = seria;
    this->type = type;
}
void NODE::deleteSubtree()
{
    NODE* temp = this->children;
    if (this->children != nullptr)
        killAllChildren(temp);
}
void killAllChildren(NODE* child)
{
    if (child->children != nullptr)
    {
        killAllChildren(child->children);
    }
    NODE* temp2 = child;
    while (temp2 != nullptr && temp2->sibling != nullptr)
    {
        child = temp2;
        temp2 = child->sibling;
        temp2 = nullptr;
        delete temp2;

    }
    child = nullptr;
    delete child;

}
void evaluate(NODE* root)
{
    char win = won_now(*root);
    if (win == rootplayer)
    {
        root->value = TRUE;
    }
    else if (win == opositeplayer(rootplayer) || root->freeTitles == 0)
    {
        root->value = FALSE;
    }
    else
        root->value = UNKNOWN;
}
void editroot(char player)
{
    rootplayer = player;
}
void setWidthHeight(int xszerokosc, int xwysokosc)
{
    szerokosc = xszerokosc;
    wysokosc = xwysokosc;
}
bool PN(NODE* root)
{

    evaluate(root); // sprawdzam czy win
    setProofAndDisproofNumbers(root);
    NODE* currentNode = root;
    while (root->proof != 0 && root->disproof != 0)
    {
        //Second Part of the algorithm
        NODE* mostProvingNode = SelectMostProvingNode(currentNode);
        expandNode(mostProvingNode);

        currentNode = updateAncestors(mostProvingNode, root);
    }
    if (root->proof == 0)
    {
        return true;
    }
    else if (root->disproof == 0)
    {
        return false;
    }

    return 0;
}
//Calculating proof and disproof numbers
void setProofAndDisproofNumbers(NODE* node)
{
    if (node->expanded)
    {
        //jesli jest rozwiety to znaczy ze ma dzieci
        if (node->type == AND)
        {
            node->proof = 0;
            node->disproof = INF;
            NODE* child = node->children;
            while (child != nullptr)
            {
                node->proof = node->proof + child->proof;
                if (child->disproof < node->disproof)
                    node->disproof = child->disproof;
                child = child->sibling;
            }
        }
        else
        {
            node->proof = INF;
            node->disproof = 0;
            NODE* child = node->children;
            while (child != nullptr)
            {
                node->disproof = node->disproof + child->disproof;
                if (child->proof < node->proof)
                    node->proof = child->proof;
                child = child->sibling;
            }
        }
    }
    else
    {
        switch (node->value)
        {
        default:
            break;
        case FALSE:
            node->proof = INF;
            node->disproof = 0;
            break;
        case TRUE:
            node->proof = 0;
            node->disproof = INF;
            break;
        case UNKNOWN:
            node->proof = 1;
            node->disproof = 1;
            break;
        }
    }
}
//Select the most-proving node
NODE* SelectMostProvingNode(NODE* node)
{
    while (node->expanded) {
        NODE* child = node->children;
        if (node->type == OR) //OR Node
            while (child->proof != node->proof)
            {
                if (child->sibling == nullptr)
                    break;
                child = child->sibling;
            }
        else //AND Node
            while (child->disproof != node->disproof)
            {
                if (child->sibling == nullptr)
                    break;
                child = child->sibling;
            }
        node = child;
    }
    return node;
}
//Expand node
void expandNode(NODE* node)
{
    generateAllChildren(node);
    NODE* child = node->children;
    while (child != nullptr)
    {
        evaluate(child);
        setProofAndDisproofNumbers(child);
        if ((node->type == OR && child->proof == 0) ||
            (node->type == AND && child->disproof == 0))
            break;
        child = child->sibling;
    }
    node->expanded = true;
}
//Update ancestors
NODE* updateAncestors(NODE* mostProvingNode, NODE* root)
{
    do {
        int oldProof = mostProvingNode->proof;
        int oldDisProof = mostProvingNode->disproof;
        setProofAndDisproofNumbers(mostProvingNode);

        if (mostProvingNode->proof == oldProof && mostProvingNode->disproof == oldDisProof)
            return mostProvingNode;

        if (mostProvingNode->proof == 0 || mostProvingNode->disproof == 0)
            mostProvingNode->deleteSubtree();

        if (mostProvingNode == root)
            return mostProvingNode;
        //if (mostProvingNode->parent == nullptr)
        //    return mostProvingNode;
        mostProvingNode = mostProvingNode->parent;
    } while (true);
}
char** copyBoard(NODE* node)
{
    char** tmp = new char* [wysokosc];
    for (int i = 0; i < wysokosc; i++)
    {
        tmp[i] = new char[szerokosc];
    }
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            tmp[i][j] = node->board[i][j];
        }
    }
    return tmp;
}
Type opositetype(Type type)
{
    if (type == OR)
    {
        return AND;
    }
    else
    {
        return OR;
    }
}
void generateAllChildren(NODE* node)
{
    NODE* temp = node->children;
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            if (node->board[i][j] != '0')
                continue;
            else
            {
                node->board[i][j] = node->activePlayer;
                char** childtab = copyBoard(node);
                NODE* kopiec = new NODE(childtab, node->freeTitles - 1, opositeplayer(node->activePlayer), node->seria, opositetype(node->type));
                kopiec->parent = node;
                node->board[i][j] = '0';
                if (node->children == nullptr)
                {
                    node->children = kopiec;
                    temp = node->children;
                }
                else
                {
                    temp->sibling = kopiec;
                    temp = temp->sibling;
                }
            }
        }
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
char opositeplayer(char p)
{
    if (p == '1')
        return '2';
    if (p == '2')
        return '1';
    return '0';
}
char won_now(NODE& root)
{
    int szer = wysokosc;
    int wys = szerokosc;
    char** gametab = root.board;
    int seria = root.seria;
    for (int j = 0; j < wys; j++)
    {
        for (int i = 0; i < szer; i++)
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
            for (int g = 1; g < seria; g++)
            {
                rightDiagonal(gametab, rightDiagonal_one, rightDiagonal_two, i, j, g, wys, szer, next);
                leftDiagonal(gametab, leftDiagonal_one, leftDiagonal_two, i, j, g, wys, szer, next);
                y_check(gametab, y_one, y_two, i, j, g, wys, next);
                x_check(gametab, x_one, x_two, i, j, g, szer, next);

                if (!x_one && !y_one && !leftDiagonal_one && !rightDiagonal_one && !x_two && !y_two && !leftDiagonal_two && !rightDiagonal_two)
                    break;
            }
            if (x_one || y_one || leftDiagonal_one || rightDiagonal_one)
            {
                if (root.activePlayer == '1')
                    root.value = TRUE;
                else
                    root.value = FALSE;
                return '1';
            }

            if (x_two || y_two || leftDiagonal_two || rightDiagonal_two)
            {
                if (root.activePlayer == '2')
                    root.value = TRUE;
                else
                    root.value = FALSE;
                return '2';
            }
        }

    }
    root.value = UNKNOWN;
    return '0';

}