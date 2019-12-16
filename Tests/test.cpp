#include <iostream>
#include <cmath>

#include "../benchmark.h"

#define DEBUG_MODE 1

#if DEBUG_MODE
#include <chrono>

class Timing {
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;
	std::chrono::duration<float> duration;
public:
	Timing() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timing() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << "Sudoku solved in " << duration.count() << "s" << std::endl;
	}
};

int calls = 0;
#endif

void inMat(int matrix[][25], int r, int c);
void outMat(int matrix[][25], int r, int c);
bool canPlace(int board[][25], const int& n, const int& r, const int& c, const int& number);
bool sudokuSolver(int board[][25], const int& n, const int& r, const int& c);

int main() {
	int board[25][25], n;
	std::cin >> n;
	inMat(board, n, n);

	#if DEBUG_MODE
		START_SESSION("Sudoku Solver");
		Timing T;
	#endif

	if (sudokuSolver(board, n, 0, 0))
		outMat(board, n, n);
	else
		std::cout << "I can't solve this Soduko!! So do you.";

	#if DEBUG_MODE
		END_SESSION();
		std::cout << calls << std::endl;
	#endif
}

void inMat(int matrix[][25], int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			std::cin >> matrix[i][j];
		}
	}
}

void outMat(int matrix[][25], int r, int c) {
	std::cout << std::endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			std::cout << matrix[i][j] << " ";
		}

		std::cout << "\n";
	}

	std::cout << std::endl;
}

bool canPlace(int board[][25], const int& n, const int& r, const int& c, const int& number) {
	#if DEBUG_MODE
    	calls++;
    	PROFILE_FUNCTION();
	#endif
	
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

bool sudokuSolver(int board[][25], const int& n, const int& r, const int& c) {
	#if DEBUG_MODE
    	PROFILE_FUNCTION();
	#endif

	if (r == n)
		return true;
	else if (c == n)
		return sudokuSolver(board, n, r+1, 0);

	if (board[r][c] != 0)
		return sudokuSolver(board, n, r, c+1);

	for (int num = 1; num <= n; num++) {
		if (canPlace(board, n, r, c, num)) {
			board[r][c] = num;
			if (sudokuSolver(board, n, r, c+1))
				return true;
			else
				board[r][c] = 0;
		}
	}

	return false;
}