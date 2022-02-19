#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


// check if the input is number
bool checkDigit(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}


// check if the input is valid
bool validCheck(char **arg)
{
    if (!checkDigit(arg[1]))
    {
        return false;
    }
    else if (!checkDigit(arg[2]))
    {
        return false;
    }
    else if (!checkDigit(arg[3]))
    {
        return false;
    }
    else if (!checkDigit(arg[4]))
    {
        return false;
    }
    else if (atoi(*(arg + 3)) >= atoi(*(arg + 1)))
    {
        return false;
    }
    else if (atoi(*(arg + 4)) >= atoi(*(arg + 2)))
    {
        return false;
    }
    else
    {
        return true;
    }
}


// find possible moves of given knight position
int *possibleMoves(int **ptr, int currentRow, int currentColumn, int *rowMove, int *columnMove, int row, int column, int currentStep)
{
    static int moves[8] = {9, 9, 9, 9, 9, 9, 9, 9};
    int count = 0;
    for (int k = 0; k < 8; k++)
    {
        if (currentRow + rowMove[k] < row && currentRow + rowMove[k] >= 0 && currentColumn + columnMove[k] < column && currentColumn + columnMove[k] >= 0)
        {
            if (ptr[currentRow + rowMove[k]][currentColumn + columnMove[k]] == 0)
            {
                moves[count] = k;
                count += 1;
                printf("location: %d %d\n", currentRow + rowMove[k], currentColumn + columnMove[k]);
            }
        }
    }
    return moves;
}

// recurision of creating fork and find possible next move, incomplete, bug still exists
void process(int **ptr, int currentRow, int currentColumn, int *rowMove, int *columnMove, int row, int column, int currentStep)
{

    int possibleMoveCount = 0;
    int *possibleMove = possibleMoves(ptr, currentRow, currentColumn, rowMove, columnMove, row, column, currentStep);
    for (int i = 0; i < 8; i++)
    {
        if (possibleMove[i] == 9)
        {
            possibleMoveCount = i;
            break;
        }
    }
    printf("Count: %d\n", possibleMoveCount);
    if (possibleMoveCount == 0)
    {
        return;
    }
    else if (possibleMoveCount == 1)
    {
        printf("%d %d\n", currentRow + rowMove[possibleMove[0]], currentColumn + columnMove[possibleMove[0]]);
        ptr[currentRow][currentColumn] = currentStep;
        printf("%d\n", currentStep);
        process(ptr, currentRow + rowMove[possibleMove[0]], currentColumn + columnMove[possibleMove[0]], rowMove, columnMove, row, column, currentStep + 1);
    }
    else
    {
        return;
    }
}

int main(int argc, char **argv)
{
    if (!validCheck(argv))
    {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }
    int row = atoi(*(argv + 1));
    int column = atoi(*(argv + 2));
    int startingRow = atoi(*(argv + 3));
    int startingColumn = atoi(*(argv + 4));
    int currentStep = 1;
    int **ptr = calloc(row, sizeof(int *));
    for (int i = 0; i < row; i++)
    {
        ptr[i] = calloc(column, sizeof(int));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            ptr[i][j] = 0;
        }
    }

    // using both array with same index to find possible move of knight in 8 directions
    int rowMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int columnMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    ptr[startingRow][startingColumn] = 1;

    process(ptr, startingRow, startingColumn, rowMove, columnMove, row, column, currentStep);
    // int * possibleMove = possibleMoves(ptr, startingRow, startingColumn, rowMove, columnMove, row, column, currentStep);
    // for(int i = 0; i < 8; i ++){
    //     printf("%d\n", possibleMove[i]);
    // }

    // pid_t p;
    // p = fork();
    // if ( p == -1 ) { perror( "fork() failed" ); return EXIT_FAILURE; }

    return EXIT_SUCCESS;
}