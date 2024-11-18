#include <iostream>
#include <vector>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

// Magic square mapping
int magicSquare[3][3] = {
    {2, 7, 6},
    {9, 5, 1},
    {4, 3, 8}
};

// To store the board state
vector<vector<char>> board(3, vector<char>(3, ' '));

// To store the moves chosen by the player and the computer
vector<int> player_moves, computer_moves;

void printBoard() {
    cout << "Current Board:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "--+---+--" << endl;
    }
}

bool isValidMove(int row, int col) {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

bool checkWin(const vector<int>& moves) {
    // Check if any combination of 3 moves sums to 15
    int size = moves.size();
    if (size < 3) return false;

    for (int i = 0; i < size - 2; i++) {
        for (int j = i + 1; j < size - 1; j++) {
            for (int k = j + 1; k < size; k++) {
                if (moves[i] + moves[j] + moves[k] == 15) {
                    return true;
                }
            }
        }
    }
    return false;
}

void computerMove() {
    int row, col;
    do {
        // Randomly select a position
        row = rand() % 3;
        col = rand() % 3;
    } while (!isValidMove(row, col));

    board[row][col] = 'O';
    int moveValue = magicSquare[row][col];
    computer_moves.push_back(moveValue);

    cout << "Computer chose: (" << row << ", " << col << ")" << endl;
}

void playGame() {
    int row, col;
    char currentPlayer = 'X';

    for (int turn = 0; turn < 9; ++turn) {
        printBoard();
        if (currentPlayer == 'X') {
            // Player's turn
            cout << "Player's turn (enter row and column): ";
            cin >> row >> col;

            if (!isValidMove(row, col)) {
                cout << "Invalid move! Try again." << endl;
                --turn;
                continue;
            }

            board[row][col] = 'X';
            int moveValue = magicSquare[row][col];
            player_moves.push_back(moveValue);

            if (checkWin(player_moves)) {
                printBoard();
                cout << "Player wins!" << endl;
                return;
            }
        } else {
            // Computer's turn
            computerMove();
            if (checkWin(computer_moves)) {
                printBoard();
                cout << "Computer wins!" << endl;
                return;
            }
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printBoard();
    cout << "It's a draw!" << endl;
}

int main() {
    srand(time(0));  // Seed for random number generation
    playGame();
    return 0;
}
