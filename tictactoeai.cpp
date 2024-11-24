#include <iostream>
#include <vector>
#include <limits>

using namespace std;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char player = 'X', ai = 'O';

void printBoard() {
    cout << "---------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " " << board[i + 1] << " " << board[i + 2] << " |" << endl;
    }
    cout << "---------" << endl;
}

bool isBoardFull() {
    for (char c : board) {
        if (c == ' ') {
            return false;
        }
    }
    return true;
}

bool hasWon(char currentPlayer) {
    return (board[0] == currentPlayer && board[1] == currentPlayer && board[2] == currentPlayer) ||
           (board[3] == currentPlayer && board[4] == currentPlayer && board[5] == currentPlayer) ||
           (board[6] == currentPlayer && board[7] == currentPlayer && board[8] == currentPlayer) ||
           (board[0] == currentPlayer && board[3] == currentPlayer && board[6] == currentPlayer) ||
           (board[1] == currentPlayer && board[4] == currentPlayer && board[7] == currentPlayer) ||
           (board[2] == currentPlayer && board[5] == currentPlayer && board[8] == currentPlayer) ||
           (board[0] == currentPlayer && board[4] == currentPlayer && board[8] == currentPlayer) ||
           (board[2] == currentPlayer && board[4] == currentPlayer && board[6] == currentPlayer);
}

bool isGameOver() {
    if (hasWon(player)) {
        cout << "Player wins!" << endl;
        return true;
    }
    if (hasWon(ai)) {
        cout << "AI wins!" << endl;
        return true;
    }
    if (isBoardFull()) {
        cout << "It's a tie!" << endl;
        return true;
    }
    return false;
}

int minimax(bool isMaximizing) {
    if (hasWon(ai)) return 1;
    if (hasWon(player)) return -1;
    if (isBoardFull()) return 0;

    int bestScore = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = isMaximizing ? ai : player;
            int score = minimax(!isMaximizing);
            board[i] = ' ';
            bestScore = isMaximizing ? max(score, bestScore) : min(score, bestScore);
        }
    }

    return bestScore;
}

void aiMove() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = ai;
            int score = minimax(false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }

    board[move] = ai;
    cout << "AI chose position " << (move + 1) << endl;
    printBoard();
}

void playerMove() {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        move -= 1;
        if (move >= 0 && move < 9 && board[move] == ' ') {
            board[move] = player;
            break;
        }
        cout << "Invalid move, try again." << endl;
    }
    printBoard();
}

int main() {
    printBoard();

    while (true) {
        playerMove();
        if (isGameOver()) {
            break;
        }
        aiMove();
        if (isGameOver()) {
            break;
        }
    }

    return 0;
}