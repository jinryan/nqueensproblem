#include <iostream>


using namespace std;

void printQueenList(int *grid, int n);
bool queensInTheGrid(int n, int row, int column, int *existingQueens);
bool canPutQueenAt(int n, int row, int column, int *existingQueens);
bool queen(int n, int *existingQueens);

int main() {
    int n;
    cout << "Please enter the grid width (n): ";
    cin >> n;
    int *queensGrid = new int[n]; // There will be n queens
    for (int i = 0; i < n; i++) {
        queensGrid[i] = -1;
    }
    if (queen(n, queensGrid)) {
        printQueenList(queensGrid, n);
    } else {
        cout << "No Solution" << endl;
    }

    // Delete grid
    delete[] queensGrid;
    return 0;

}

bool queen(int n, int *existingQueens) {
    for (int i = 0; i < n; i++) {
        if (queensInTheGrid(n, 0, i, existingQueens)) {
            return true;
        }
    }
    return false;
}

bool queensInTheGrid(int n, int row, int column, int *existingQueens) {
    existingQueens[row] = -1; // Reset the row so previous attempts on this row has been cleared
    if (row == n - 1 && canPutQueenAt(n, row, column, existingQueens)) {
        // If we are looking at the last row and we got one, then return true
        existingQueens[row] = column;
        return true;
    } else if (column == n - 1 && !canPutQueenAt(n, row, column, existingQueens)) {
        // If we are looking at the last item of any row, return false if that queen would conflict
        return false;
    } else if (!canPutQueenAt(n, row, column, existingQueens)) {
        return queensInTheGrid(n, row, column+1, existingQueens);
    }
    existingQueens[row] = column;
    if(!queensInTheGrid(n, row + 1, 0, existingQueens)) {
        for (int i = existingQueens[row] + 1; i < n; i++) {
            if (queensInTheGrid(n, row, i, existingQueens)) {
                return true;
            }
        }
    } else {
        return true;
    }
}


void printQueenList(int *grid, int n) {
    cout << "Queen Coordinates: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "Queen #" << i + 1 << ": x is " << i << " and y is " << grid[i] << endl;
    }
}

bool canPutQueenAt(int n, int row, int column, int *existingQueens) {

    for (int i = 0; i < n; i++) {
        int erow = i;
        int ecol = existingQueens[i];
        if (ecol == -1) {
            break;
        }
        if (row == erow || column == ecol || abs(erow - row) == abs(ecol - column)) {
            return false;
        }
    }
    return true;
}