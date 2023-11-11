/*
	2023FA-ENGR-2304-81001-P07-TUCKER-IAN
	AUTHOR: IAN TUCKER
	DATE: NOVEMBER 3, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
int currentPlayer;
int totalMoves;

// Function to initialize the game board
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the game board
void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

// Function to check if a player has won
int checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1;
    }
    return 0;
}

// Function to make a move
void makeMove(char player, int row, int col) {
    board[row][col] = player;
    totalMoves++;
    printBoard();
    if (checkWin(player)) {
        printf("%c wins!\n", player);
        exit(0);
    } else if (totalMoves == 9) {
        printf("It's a draw!\n");
        exit(0);
    }
}

// Function to get the user's move
void getUserMove() {
    int row, col;
    printf("Enter your move (row and column, e.g., 1 2): ");
    scanf("%d %d", &row, &col);
    if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
        printf("Invalid move. Try again.\n");
        getUserMove();
    } else {
        makeMove(currentPlayer, row, col);
    }
}

// Function to get the computer's move
void getComputerMove() {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
    makeMove(currentPlayer, row, col);
}

int main() {
    int players;
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Enter the number of players (1 or 2): ");
    scanf("%d", &players);

    if (players != 1 && players != 2) {
        printf("Invalid number of players. Exiting.\n");
        return 1;
    }

    initializeBoard();
    printBoard();

    // Randomly determine who goes first
    srand(time(NULL));
    currentPlayer = rand() % 2 == 0 ? 'X' : 'O';

    while (1) {
        if (currentPlayer == 'X') {
            if (players == 1) {
                getUserMove();
            } else {
                printf("Player X, enter your move (row and column, e.g., 1 2): ");
                getUserMove();
            }
        } else {
            if (players == 1) {
                printf("Computer's move:\n");
                getComputerMove();
            } else {
                printf("Player O, enter your move (row and column, e.g., 1 2): ");
                getUserMove();
            }
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
