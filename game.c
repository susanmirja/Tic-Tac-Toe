#include <stdio.h>
#include <limits.h>
e
#define PLAYER 'X' // Human
#define AI 'O'     // Computer

char board[3][3];

// Function declarations
void resetBoard();
void printBoard();
int isMovesLeft();
int evaluate();
int minimax(int depth, int isMax);
void bestMove();
void playerMove();

int main() {
    resetBoard();
    int turn;

  printf("Do you want to play first? (1 = Yes, 0 = No): ");
    scanf("%d", &turn);

  while (1) {
        printBoard();

  if (evaluate() == 10) {
            printf("😔 AI wins!\n");
            break;
        } else if (evaluate() == -10) {
            printf("🎉 You win!\n");
            break;
        } else if (!isMovesLeft()) {
            printf("🤝 It's a draw!\n");
            break;
        }

  if (turn) {
            playerMove();
            turn = 0;
        } else {
            bestMove();
            turn = 1;
        }
    }

  printBoard();
    return 0;
}

// Reset the board with spaces
void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Print the board
void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i != 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Check if moves are left
int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

// Evaluate board state
int evaluate() {
    // Rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == AI) return 10;
            else if (board[i][0] == PLAYER) return -10;
        }

  // Columns
    for (int i = 0; i < 3; i++)
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            if (board[0][i] == AI) return 10;
            else if (board[0][i] == PLAYER) return -10;
        }

  // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return 10;
        else if (board[0][0] == PLAYER) return -10;
    }

  if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return 10;
        else if (board[0][2] == PLAYER) return -10;
    }

  return 0;
}

// Minimax algorithm
int minimax(int depth, int isMax) {
    int score = evaluate();

  if (score == 10) return score - depth;     // AI wins
    if (score == -10) return score + depth;    // Player wins
    if (!isMovesLeft()) return 0;              // Draw

  if (isMax) {
        int best = INT_MIN;

  for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);
                    board[i][j] = ' ';
                }
        return best;
    } else {
        int best = INT_MAX;

  for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);
                    board[i][j] = ' ';
                }
        return best;
    }
}

// Find the best move for AI
void bestMove() {
    int bestVal = INT_MIN;
    int bestRow = -1, bestCol = -1;

  for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';

  if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }

  board[bestRow][bestCol] = AI;
    printf("AI played at (%d, %d)\n", bestRow + 1, bestCol + 1);
}

// Get player's move
void playerMove() {
    int row, col;
    while (1) {
        printf("Enter your move (row and column: 1-3 1-3): ");
        scanf("%d %d", &row, &col);
        row--; col--;

  if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = PLAYER;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}
