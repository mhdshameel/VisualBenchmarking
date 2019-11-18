#include "../benchmark.h"
#include <iostream>
#include <cmath>

using namespace std;

int calls = 0;

void inMat(int matrix[][25], int r, int c);
void outMat(int matrix[][25], int r, int c);
bool canPlace(int board[][25], const int& n, const int& r, const int& c, const int& number);
bool sodukoSolver(int board[][25], const int& n, const int& r, const int& c);

int main() {
	int board[25][25], n;
	cin >> n;
	inMat(board, n, n);

    START_SESSION("nQueen Problem");
	if (sodukoSolver(board, n, 0, 0))
		outMat(board, n, n);
	else
		cout << "I can't solve this Soduko!! So do you.";
    END_SESSION();

    std::cout << calls << std::endl;
}

void inMat(int matrix[][25], int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> matrix[i][j];
		}
	}
}

void outMat(int matrix[][25], int r, int c) {
    PROFILE_FUNCTION();
	cout << "\n----MAT Begins----\n";
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << matrix[i][j] << " ";
		}

		cout << "\n";
	}
	cout << "-----MAT Ends-----\n";
}

bool canPlace(int board[][25], const int& n, const int& r, const int& c, const int& number) {
    calls++;
    PROFILE_FUNCTION();
	for(int x = 0; x < n; ++x){
        if (board[r][x] == number or board[x][c] == number){
            return false;
        }
    }

    int rootN = sqrt(n);
    int subBoxStartRow = r - (r % rootN);
    int subBoxStartCol = c - (c % rootN);
    for(int i = subBoxStartRow; i < subBoxStartRow + rootN; i++) {
        for(int c = subBoxStartCol; c < subBoxStartCol + rootN; c++) {
            if (board[i][c] == number) {
                return false;
            }
        }
    }

    return true;
}

bool sodukoSolver(int board[][25], const int& n, const int& r, const int& c) {
    PROFILE_FUNCTION();

    // calls++;

	if (r == n)
		return true;
	else if (c == n)
		return sodukoSolver(board, n, r+1, 0);

	if (board[r][c] != 0)
		return sodukoSolver(board, n, r, c+1);

	for (int num = 1; num <= n; num++) {
		if (canPlace(board, n, r, c, num)) {
			board[r][c] = num;
			if (sodukoSolver(board, n, r, c+1))
				return true;
			else
				board[r][c] = 0;
		}
	}

	return false;
}