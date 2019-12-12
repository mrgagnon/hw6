/* Maylee Gagnon
 * CS 2223 HW6
 * 12.13.2019
 */

#include <iostream>
using namespace std;

/* Checks to the given board to see if all of the queens are in a legal position
 * @param board Contains the locations of the queens. The position is the row, and the value is the column
 * @param n The number of queens
 * @return True if the board is legal False otherwise
 */
bool isLegalPosition(int *board, int n){
	for (int i = 0; i < n; i++){
		int colCur = board[i];
		if (colCur != 0){
			for (int j = 0; j < n; j++){
				if (i!=j){
					int colNew = board[j];
					if (colNew != 0){
						if (colCur == colNew){ // check cols
							return false;
						}
						else if (((j-i)+colCur) == colNew){ // check diag (lr)
							return false;
						}
						else if ((colCur-(j-i)) == colNew ){ // check diag (rl)
							return false;
						}
					}
				}
			} // end 2nd for loop
		}
	} // end 1st for loop
	return true;
}

int firstEmptyRow(int* board, int n){
	int ctQueens = 0;
	for (int i = 0; i < n; i++){
		if (board[i] != 0){
			ctQueens++;
		}
	}
	return ctQueens;
}

/* Returns a board where the last row with a queen the queen is moved one to the right
 * @returns The next board configuration despite whether it's legal or not
 */
int* successor(int* board, int n){
	cout << "In successor" << endl;
	int rLastQueen = firstEmptyRow(board, n)-1;
	board[rLastQueen] = board[rLastQueen]+1;
	return board;
}

int* nextLegalPosition(int* board, int n){
	bool isBoardLegal= isLegalPosition(board, n);

	if (isBoardLegal == true){
		cout << "Board Legal" << endl;
		int r = firstEmptyRow(board, n);
		//cout << r << endl;
		board[r] = 1;
		nextLegalPosition(board, n);
	}

	else if (isBoardLegal == false){
		cout << "Board Illegal" << endl;
		int * nextBoard = board;
		do {
			nextBoard = successor(nextBoard, n);
		} while (!isLegalPosition(nextBoard, n));
		board = nextBoard;

	}
	return board;
}

/*
int* nextLegalPosition(int* board, int n){
	cout << "In nextLegalPosition" << endl;;
	int curQueenRow = 0;
	for (int i = 0; i < n; i++){
		if (board[i] != 0){
			curQueenRow++;
		}
	}

	int curBoard[n];
	for (int i = 0; i < n; i++){
		curBoard[i] = board[i];
	}

	curBoard[curQueenRow] = 1; // Place newest queen in the first column
	if (isLegalPosition(curBoard,n)){ // if it works return the board
		return curBoard;
	}

	int* nextBoard;
	bool flag = true;
	while (flag) {
		nextBoard = successor(nextBoard,n); //gets what the next board configuration looks like,
		if (isLegalPosition(nextBoard,n)){
			return curBoard;
		}
		else if (nextBoard[curQueenRow] == n){ //illegal and new queen reached the last column/potentional positions
			nextBoard[curQueenRow] = 0;
		}
	}


	//loop, successor, if true move on to next row, if false try again, if false and end of row set to zero go to previous row
	// move to next legal position, move back down to next row and try again

	return curBoard;
}*/

int main() {
	cout << "hello" << endl;

	// Testing isLegalPosition
	int b1[8] = {1,6,8,3,7,4,2,5};
	bool r1 = isLegalPosition(b1, 8);
	cout << "Should be true: " << r1 << endl;

	int b2[8] = {1,6,8,3,7,0,0,0};
	bool r2 = isLegalPosition(b2, 8);
	cout << "Should be true: " << r2 << endl;

	int b3[8] = {1,6,8,3,5,0,0,0};
	bool r3 = isLegalPosition(b3, 8);
	cout << "Should be false: (lr diag) " << r3 << endl;

	int b4[8] = {1,6,8,3,2,0,0,0};
	bool r4 = isLegalPosition(b4, 8);
	cout << "Should be false: (rl diag) " << r4 << endl;

	int b5[8] = {1,6,8,3,8,0,0,0};
	bool r5 = isLegalPosition(b5, 8);
	cout << "Should be false: (col) " << r5 << endl;

	int b6[8] = {1,6,6,3,8,4,3};
	bool r6 = isLegalPosition(b6, 7);
	cout << "Should be false: (col) " << r6 << endl;

	int arr[8] = {1,6,8,3,0,0,0,0};
	int* result = nextLegalPosition(arr, 8);
	for (int i = 0; i < 8; i++){
		cout << result[i] << "  ";
	}


	return 0;
}
