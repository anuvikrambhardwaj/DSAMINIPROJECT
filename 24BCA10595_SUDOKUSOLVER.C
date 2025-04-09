#include <stdio.h> 

#define N 9

// Predefined Sudoku Board (0 = empty)
int board[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Function to print the Sudoku board
void printBoard(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }
}

// Check if placing a number is valid
int isSafe(int board[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num)
            return 0;
    }

    // Check column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num)
            return 0;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return 0;
        }
    }

    return 1;
}

// Backtracking function to solve the puzzle
int solveSudoku(int board[N][N]) {
    int row, col;
    int emptyFound = 0;

    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                emptyFound = 1;
                goto found;
            }
        }
    }

found:
    if (!emptyFound)
        return 1; // Puzzle is solved

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board))
                return 1;

            board[row][col] = 0; // backtrack
        }
    }

    return 0; // Trigger backtracking
}

// Main function
int main() {
    printf("Initial Sudoku Puzzle:\n");
    printBoard(board);

    if (solveSudoku(board)) {
        printf("\nSolved Sudoku Puzzle:\n");
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}