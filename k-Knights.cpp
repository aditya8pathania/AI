#include <bits/stdc++.h>
using namespace std;

int m,n;

void print_board(int **board) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool canPlace(int **board, int i, int j) {
    int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };

    for (int k = 0; k < 8; k++) {
        int new_i = i + knightMoves[k][0];
        int new_j = j + knightMoves[k][1];

        if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n && board[new_i][new_j] == 1) {
            return false;
        }
    }
    return true;
}

void Place(int **board, int i, int j) {
    board[i][j] = 1;
}

int PlaceKnights(int **board, int k, int sti, int stj, int count) {
    if (k == 0) {
        count++;
        cout << "Board " << count << ":" << endl;
        print_board(board);
        return count;
    }
    for (int i = sti; i < m; i++) {
        for (int j = (i == sti ? stj : 0); j < n; j++) {
            if (canPlace(board, i, j)) {
                Place(board, i, j);
                count = PlaceKnights(board, k - 1, i, j + 1, count);
                board[i][j] = 0;
            }
        }
    }
    return count;
}

int main() {
    
    cout << "Enter size of board (rows and columns): ";
    cin >> m >> n;

    int **board = new int*[m];
    for (int i = 0; i < m; i++) {
        board[i] = new int[n];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }

    cout << "Number of knights to be placed: ";
    int K;
    cin >> K;

    auto start = chrono::high_resolution_clock::now();
    int totalSolutions = PlaceKnights(board, K, 0, 0, 0);
    //cout << "Total solutions found: " << totalSolutions << n << endl;

    for (int i = 0; i < m; i++) {
        delete[] board[i];
    }
    delete[] board;
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start)/1000000;
    cout<<"Time taken: "<< duration.count()<<" Seconds"<<endl;
    return 0;
}

