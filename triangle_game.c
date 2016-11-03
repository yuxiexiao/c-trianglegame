#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "triangle_routines.h"
#define NMOVES 36

/*
 * triangle_game:
 *   This program asks the user for an initial board for the triangle game and
 *   determines if that board is solvable (so that only one peg is remaining).
 *   The program prints out steps taken to solve the board in reverse order
 *   if it can be solved.
 */

int moves[NMOVES][3] =
{
    {0, 1, 3},
    {3, 1, 0},
    {1, 3, 6},
    {6, 3, 1},
    {3, 6, 10},
    {10, 6, 3},
    {0, 2, 5},
    {5, 2, 0},
    {2, 5, 9},
    {9, 5, 2},
    {5, 9, 14},
    {14, 9, 5},
    {2, 4, 7},
    {7, 4, 2},
    {4, 7, 11},
    {11, 7, 4},
    {5, 8, 12},
    {12, 8, 5},
    {1, 4, 8},
    {8, 4, 1},
    {4, 8, 13},
    {13, 8, 4},
    {3, 7, 12},
    {12, 7, 3},
    {3, 4, 5},
    {5, 4, 3},
    {6, 7, 8},
    {8, 7, 6},
    {7, 8, 9},
    {9, 8, 7},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12}
};

/* function prototypes */
int npegs(int board[]);
int valid_move(int board[], int move[]);
void make_move(int board[], int move[]);
void unmake_move(int board[], int move[]);
int solve(int board[]);


/* Return the number of pegs on the board. */
int npegs(int board[])
{
    int i;
    int totalPegs = 0;

    for (i = 0; i < 15; i++)
    {
        if (board[i] == 1)
        {
            totalPegs++;
        }
    }
    return totalPegs;

}


/* Return 1 if the move is valid on the board, otherwise, return 0. */
int valid_move(int board[], int move[])
{
    int i;

    if (board[move[0]] == 0 || board[move[1]] == 0 || board[move[2]] == 1)
    {
        return 0;
    }

    for (i = 0; i < NMOVES; i++)
    {
        if (moves[i] == move)
        {
            return 1;
        }
    }
    return 0;

}


/* Make this move on this board. */
void make_move(int board[], int move[])
{
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;

}


/* Unmake this move on this board. */
void unmake_move(int board[], int move[])
{
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}


/*
 * Solve the game staring from this baord. Return 1 if the game can be solved
 * otherwise return 0. Do not permanently alter the board passed in. Once a
 * solution is found, print the boards making up the solution in reverse
 * order.
 */
int solve(int board[])
{
    int i;
    int temp;

    if (npegs(board) == 1)
    {
        triangle_print(board);
        return 1;
    }
    else
    {
        for (i = 0; i < NMOVES; i++)
        {
            if (valid_move(board, moves[i]))
            {
                make_move(board, moves[i]);
                temp = solve(board);
                unmake_move(board, moves[i]);
                if (temp)
                {
                    triangle_print(board);
                    return 1;
                }

            }
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{

    int board[15];
    triangle_input(board);

    if (solve(board) == 1)
        {
            printf("Board can be solved\n");
        }
    else
        {
            printf("Board cannot be solved\n");
        }
    return 0;
}
