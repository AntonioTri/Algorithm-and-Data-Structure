#include <iostream>
#include <vector>

using namespace std;

#define N 8  // Dimensione della scacchiera

// Funzione per verificare se possiamo piazzare una regina in (row, col)
bool isSafe(vector<vector<int>> &board, int row, int col) {
    // Controlla la colonna sopra
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Controlla la diagonale in alto a sinistra
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Controlla la diagonale in alto a destra
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true; // Nessun conflitto, posizione sicura
}

// Funzione ricorsiva per risolvere il problema delle 8 regine
bool solveNQueens(vector<vector<int>> &board, int row) {
    // Se abbiamo posizionato tutte le 8 regine, ritorna true
    if (row >= N)
        return true;

    // Prova a piazzare una regina in ogni colonna della riga corrente
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // Posiziona la regina

            // Ricorsivamente prova a piazzare le altre regine
            if (solveNQueens(board, row + 1))
                return true;

            board[row][col] = 0;  // Backtracking: rimuove la regina se non va bene
        }
    }
    return false; // Nessuna soluzione trovata per questa riga
}

// Funzione per stampare la scacchiera
void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

// Funzione principale
int main() {
    vector<vector<int>> board(N, vector<int>(N, 0)); // Inizializza scacchiera vuota

    if (solveNQueens(board, 0)) {
        cout << "Soluzione trovata:\n";
        printBoard(board);
    } else {
        cout << "Nessuna soluzione trovata.\n";
    }

    return 0;
}
