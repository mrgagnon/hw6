/* Maylee Gagnon
 * CS 2223 HW6
 *
 */

#include <iostream>
using namespace std;

/*
 *
 */
bool isLegalPosition(int *board, int n){
	for (int i = 0; i < n; i++){
		int colCur = board[i];
		if (colCur != 0){
			for (int j = 0; j < n; j++){
				if (i!=j){
					int colNew = board[j];
					if (colNew != 0){
						if (colCur == colNew){ // checking for same columns
							//cout << "Col" << endl;;
							return false;
						}

						else if (((j-i)+colCur) == colNew){
							//cout << "diag lr" << endl;
							return false;
						}

						else if ((colCur-(j-i)) == colNew ){
							//cout << j << ", " << i << endl;
							//cout << "diag rl" << endl;
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}


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

	return 0;
}
