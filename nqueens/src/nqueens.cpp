/* Maylee Gagnon
 * CS 2223 HW6
 * 12.13.2019
 */

#include <iostream>
using namespace std;

/*Prints the given board
 * @param board The board to be printed
 * @param n The number of elements
 */
void printBoard(int* board, int n){
	for (int i = 0; i < n; i++){
		cout << board[i] << ", ";
	}
	cout << endl;
}

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

/* Finds the position of the first empty row
 * @param board The board to be checked
 * @param n The number of elements
 * @return an int representing the position
 */
int firstEmptyRow(int* board, int n){
	int ctQueens = 0;
	for (int i = 0; i < n; i++){
		if (board[i] != 0){
			ctQueens++;
		}
	}
	return ctQueens;
}

/* Either moves the last queen over by one or reaches a dead end and needs to backtrack
 * @param board The board holding the board configuration
 * @param n The number of elements
 * @returns The next board configuration despite whether it's legal or not
 */
int* successor(int* board, int n){
	int rLastQueen = firstEmptyRow(board, n)-1;

	if (board[n-1] != 0){
		rLastQueen = n-1;
	}

	if (board[rLastQueen] < n){ //move to right by one, not at the end
		board[rLastQueen] = board[rLastQueen]+1;
	}
	else {
		board[rLastQueen] = 0; // remove this queen because reached dead-end
		rLastQueen--;
		while (board[rLastQueen] == n){ // back tracking, find the first queen that can be to the right by one
			board[rLastQueen] = 0;
			rLastQueen--;
		}
		board[rLastQueen] = board[rLastQueen]+1;
	}
	return board;
}

/* Find the next legal configuartion of the board
 * @param board The board to be changed
 * @param n The number of elements
 * @return The new board with the legal configuration or all zeros if impossible
 */
int* nextLegalPosition(int* board, int n){
	bool isBoardLegal= isLegalPosition(board, n);

	if (isBoardLegal == true){ //Legal
		if (board[n-1] != 0){ //full
			int* nextBoard = board;
			do {
				nextBoard = successor(nextBoard, n);
			} while (!isLegalPosition(nextBoard, n));
			board = nextBoard;
		}
		else { //partial, legal
			int r = firstEmptyRow(board, n);
			board[r] = 1;
			nextLegalPosition(board, n);
		}
	}

	else if (isBoardLegal == false){ // partial, illegal
		int* nextBoard = board;
		do {
			nextBoard = successor(nextBoard, n);
		} while (!isLegalPosition(nextBoard, n));
		board = nextBoard;
	}
	return board;
}

/*Prints first solution for 4 queens to 30 queens
 */
void makeBoard(){
	for (int i = 4; i < 31; i++){
		int b[i] = {0};
		int* board = b;
		board[0] = 1;

		do {
			board = nextLegalPosition(board, i);
		} while (board[i-1]==0);
		printBoard(board, i);
	}
}

int main() {
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

	//Testing nextLegalPosition
	int arr1[8] = {1,6,8,3,5,0,0,0};
	int* result1 = nextLegalPosition(arr1, 8);
	cout << "Next expected 1: (1, 6, 8, 3, 7, 0, 0, 0) Actual: ";
	printBoard(result1, 8);

	int arr2[8] = {1,6,8,3,7,0,0,0};
	int* result2 = nextLegalPosition(arr2, 8);
	cout << "Next expected 2: (1, 6, 8, 3, 7, 4, 0, 0) Actual: ";
	printBoard(result2, 8);

	int arr3[3] = {2,0,0};
	int* result3 = nextLegalPosition(arr3,3);
	cout << "Next expected 3a: (3,0,0) Actual: ";
	printBoard(result3, 3);

	int* res3 = nextLegalPosition(result3, 3);
	cout << "Next expected 3b No sol'n: (0,0,0) Actual: ";
	printBoard(res3,3);

	int arr4[8] = {1,6,8,3,7,4,2,5};
	int* result4 = nextLegalPosition(arr4,8);
	cout << "Next expected 4: (1, 6, 8, 5, 0, 0, 0, 0) Actual: ";
	printBoard(result4, 8);

	//Printing boards
	makeBoard();

	return 0;
}
