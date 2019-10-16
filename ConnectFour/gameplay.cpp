//Author: Rutul Thakkar
//Game Name: Connect Four
//Assignment: 2
//Class: GAME 230 Game Engineering
//Optional Implemented and Tested : J, K

#include <iostream>
#include <climits>

using namespace std;

const int COLUMNS_MAX = 20;
const int ROWS_MAX = 20;
int ROWS = 0;
int COLUMNS = 0;
int countToWin = 3;
char grid[ROWS_MAX][COLUMNS_MAX] = {};
bool turn = true; //using boolean to switch player turns
int won = -1; // -1 game not finished yet, 0 is tie. 1 is won 
int noOfWinsPlayerX = 0;
int noOfWinsPlayerO = 0;
bool isWrapAroundOn = false;
bool isRemoveOn = false;
bool userSelectedToRemove = false;

void printGrid();
bool isColumnFull(int columnID);
bool checkIfWon(int rowID, int columnID, char c);
void checkIfWonWrapMode();
bool checkIfInside(int rowID, int columnID, char c);
void addBall(int rowID, int columnID, char c);
int getRow(int columnID);
bool checkIfTie();
void gamePlay(int columnID);
void checkGrid();
void removeAtPosition(int rowID, int columnID);

int main() {
	int choice = 0;
	char wrap, remove;

	newgame:

	system("CLS");

	cout << "CONNECT FOUR" << endl;
	inputRows:
	cout << "Enter the number between 4 and 20 for no of rows: ";
	while (!(cin >> ROWS)) {
		// not an integer
		cout << "Please enter a number between 4 and 20 (including these two nos!)" << endl;
		cout << "Enter the number between 4 and 20 for no of rows: ";
		//clear the previous input
		cin.clear();
		//discarding previous input		
		cin.ignore(INT_MAX,'\n');
	}

	if (ROWS >= 4 && ROWS <= 20) {
		inputColumns:
		cout << "Enter a number between 4 and 20 for no of columns: ";
		while (!(cin >> COLUMNS)) {
			// not an integer
			cout << "Please enter a number between 4 and 20 (including these two nos!)" << endl;
			cout << "Enter a number between 4 and 20 for no of columns: ";
			//clear the previous input
			cin.clear();
			//discarding previous input
			cin.ignore(INT_MAX, '\n');
		}

		if (COLUMNS >= 4 && COLUMNS <= 20) {
			inputWin:
			cout << "Enter a number between 3 and 20 for no of pieces required to win the game: ";

			while (!(cin >> countToWin)) {
				// not an integer
				cout << "Please enter a number between 3 and 20 (including these two nos!)" << endl;
				cout << "Enter No to pieces required to win : ";
				//clear the previous input
				cin.clear();
				//discarding previous input
				cin.ignore(INT_MAX, '\n');
			}

			if (countToWin >= 3 && countToWin <= 20) {
				cout << "Do you want to allow wrap around ? (Press Y or y to enable) ";
				cin >> wrap;
				if (wrap == 'Y' || wrap == 'y') {
					isWrapAroundOn = true;
				}
				else {
					isWrapAroundOn = false;
				}

				cout << "Do you want to allow player to remove an inserted piece? (Press Y or y to enable) ";
				cin >> remove;
				if (remove == 'Y' || remove == 'y') {
					isRemoveOn = true;
				}
				else {
					isRemoveOn = false;
				}

				system("pause");


				system("CLS");

				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLUMNS; j++) {
						grid[i][j] = '*';
					}
				}

				printGrid();

				while (true) {
					if (turn) {
						userSelectedToRemove = false; // resetting
						char ch;
						cout << "\n\n Player X turn: " << "\n\n";

					beginX:

						if (isRemoveOn) {
							cout << "Do you want to [A]dd a piece or [R]emove a piece ? ";
							cin >> ch;
							if (ch == 'A' || ch == 'a') {
								userSelectedToRemove = false;
							}
							else if (ch == 'R' || ch == 'r') {
								userSelectedToRemove = true;
							}
							else {
								cout << "Invalid input ! Please enter A to add a piece or R to remove a piece !" << endl;
								goto beginX;
							}
							if (userSelectedToRemove) {
								cout << "Enter your column No to remove : ";
							}
							else {
								cout << "Enter your column No to insert : ";
							}
						}
						else {
							cout << "Enter your column No to insert : ";
						}
					}
					else {
						userSelectedToRemove = false; // resetting
						char ch;
						cout << "\n\n Player O turn: " << "\n\n";

					beginO:

						if (isRemoveOn) {
							cout << "Do you want to [A]dd a piece or [R]emove a piece ? ";
							cin >> ch;
							if (ch == 'A' || ch == 'a') {
								userSelectedToRemove = false;
							}
							else if (ch == 'R' || ch == 'r') {
								userSelectedToRemove = true;
							}
							else {
								cout << "Invalid input ! Please enter A to add a piece or R to remove a piece !" << endl;
								goto beginO;
							}
							if (userSelectedToRemove) {
								cout << "Enter your column No to remove : ";
							}
							else {
								cout << "Enter your column No to insert : ";
							}
						}
						else {
							cout << "Enter your column No to insert : ";
						}
					}
					while (!(cin >> choice)) {
						// not an integer
						cout << "Please enter a number between 1 and " << COLUMNS << " (including these two nos!)" << endl;
						cout << "Enter your column No to insert : ";
						//clear the previous input
						cin.clear();
						//discarding previous input
						cin.ignore(INT_MAX, '\n');

					}
					if (choice > 0 && choice <= 20) {
						// column array starts from 0 hence passing 1 number less (0 to 6)
						switch (choice) {
						case 1:
							if (choice <= COLUMNS) {
								gamePlay(0);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 2:
							if (choice <= COLUMNS) {
								gamePlay(1);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 3:
							if (choice <= COLUMNS) {
								gamePlay(2);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 4:
							if (choice <= COLUMNS) {
								gamePlay(3);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 5:
							if (choice <= COLUMNS) {
								gamePlay(4);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 6:
							if (choice <= COLUMNS) {
								gamePlay(5);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 7:
							if (choice <= COLUMNS) {
								gamePlay(6);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 8:
							if (choice <= COLUMNS) {
								gamePlay(7);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 9:
							if (choice <= COLUMNS) {
								gamePlay(8);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 10:
							if (choice <= COLUMNS) {
								gamePlay(9);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 11:
							if (choice <= COLUMNS) {
								gamePlay(10);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 12:
							if (choice <= COLUMNS) {
								gamePlay(11);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 13:
							if (choice <= COLUMNS) {
								gamePlay(12);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 14:
							if (choice <= COLUMNS) {
								gamePlay(13);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 15:
							if (choice <= COLUMNS) {
								gamePlay(14);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 16:
							if (choice <= COLUMNS) {
								gamePlay(15);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 17:
							if (choice <= COLUMNS) {
								gamePlay(16);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 18:
							if (choice <= COLUMNS) {
								gamePlay(17);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 19:
							if (choice <= COLUMNS) {
								gamePlay(18);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						case 20:
							if (choice <= COLUMNS) {
								gamePlay(19);
								if (won != -1) {
									goto endGame;
								}
							}
							else {
								cout << "Invalid selection ! Please try again !" << endl;
							}
							break;
						default:
							cout << "Invalid selection ! Please try again !" << endl;
						}
					}
					else {
						cout << "Please enter a number between 1 and " << COLUMNS << " (including these two nos!)" << endl;
					}


				}
			endGame:
				char restart = 'N';
				cout << "Do you want to start a new Game (Enter Y or y to continue) ? ";
				cin >> restart;
				system("pause");
				if (restart == 'Y' || restart == 'y') {
					goto newgame;
				}
			}
			else {
				cout << "Please enter a number between 3 and 20 (including these two no)! " << endl;
				goto inputWin;
			}
		}
		else {
			cout << "Please enter a number between 4 and 20 (including these two nos!)" << endl;
			goto inputColumns;
		}
	}
	else {
		cout << "Please enter a number between 4 and 20 (including these two nos!)" << endl;
		goto inputRows;
	}

	
	return 0;
}

void printGrid() {
	for (int i = 0; i < COLUMNS; i++) {
		cout << i + 1 << "\t";
	}
	cout << endl;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
				cout << grid[i][j] << "\t";
		}
		cout << "\n";
	}
}

bool isColumnFull(int columnID) {
	for (int i = 0; i < ROWS; i++) {
		if (grid[i][columnID] == '*') {
			return false;
		}
	}
	
	return true;
}

bool isColumnEmpty(int columnID) {
	int cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		if (grid[i][columnID] == '*') {
			cnt++;
		}
	}

	if (cnt == ROWS) {
		return true;
	}
	else {
		return false;
	}
}


void checkIfWonWrapMode() {
	//new code
	
	int startPos = countToWin - 1;
	int cnt = 0;
	int k = 0; // using this for iterating till countToWin for diagonals.

	//horizontal for X
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (grid[i][(startPos + COLUMNS - j) % COLUMNS] == 'X') {
				cnt++;
			}
			else {
				cnt = 0;
			}
			if (cnt == countToWin) {
				noOfWinsPlayerX++;
				cnt = 0;
				break;
			}
		}
	}

	//horizontal for O
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (grid[i][(startPos + COLUMNS - j) % COLUMNS] == 'O') {
				cnt++;
			}
			else {
				cnt = 0;
			}
			if (cnt == countToWin) {
				noOfWinsPlayerO++;
				cnt = 0;
				break;
			}
		}
	}

	//diagonal downwards towards bottom right for X ( +1 row, +1 column)
	cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			for (int m = 0; m < countToWin; m++) {
				if (grid[(i + m) % ROWS][(j + m) % COLUMNS] == 'X') {
					cnt++;
				}
				else {
					cnt = 0;
				}

				if (cnt == countToWin) {
					noOfWinsPlayerX++;
					cnt = 0;
					break;
				}
			}
		}
	}

	//diagonal downwards towards bottom right for O ( +1 row, +1 column)
	cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			for (int m = 0; m < countToWin; m++) {
				if (grid[(i + m) % ROWS][(j + m) % COLUMNS] == 'O') {
					cnt++;
				}
				else {
					cnt = 0;
				}

				if (cnt == countToWin) {
					noOfWinsPlayerO++;
					cnt = 0;
					break;
				}
			}
		}
	}

	//diagonal downwards towards bottom left for X ( +1 row, -1 column)
	cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			for (int m = 0; m < countToWin; m++) {
				if (grid[(i + m) % ROWS][(j - m) % COLUMNS] == 'X') {
					cnt++;
				}
				else {
					cnt = 0;
				}

				if (cnt == countToWin) {
					noOfWinsPlayerX++;
					cnt = 0;
					break;
				}
			}
		}
	}

	//diagonal downwards towards bottom left for O ( +1 row, -1 column)
	cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			for (int m = 0; m < countToWin; m++) {
				if (grid[(i + m) % ROWS][(j - m) % COLUMNS] == 'O') {
					cnt++;
				}
				else {
					cnt = 0;
				}

				if (cnt == countToWin) {
					noOfWinsPlayerO++;
					cnt = 0;
					break;
				}
			}
		}
	}

	//diagonal upwards towards top right for X ( -1 row, +1 column)
	cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			for (int m = 0; m < countToWin; m++) {
				if (grid[(i - m) % ROWS][(j + m) % COLUMNS] == 'X') {
					cnt++;
				}
				else {
					cnt = 0;
				}

				if (cnt == countToWin) {
					noOfWinsPlayerX++;
					cnt = 0;
					break;
				}
			}
		}
	}

	//diagonal upwards towards top right for O ( -1 row, +1 column)
	cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			for (int m = 0; m < countToWin; m++) {
				if (grid[(i - m) % ROWS][(j + m) % COLUMNS] == 'O') {
					cnt++;
				}
				else {
					cnt = 0;
				}

				if (cnt == countToWin) {
					noOfWinsPlayerO++;
					cnt = 0;
					break;
				}
			}
		}
	}


	/*cnt = 0;
	for (int i = 0; i < ROWS; i++) {
		cnt = 0;
		for (int j = 0; j < COLUMNS; j++) {
			if (grid[(startPos + j + ROWS) % ROWS][(startPos + 1 + j + COLUMNS) % COLUMNS] == 'O') {
				cout << "Position : ROW  " << (startPos + j + ROWS) % ROWS << " COLUMN " << (startPos + 1 + j + COLUMNS) % COLUMNS << " HAS O !" << endl;
				cnt++;
				cout << "count is " << cnt << endl;
			}
			else {
				cout << "Position : ROW  " << (startPos + j + ROWS) % ROWS << " COLUMN " << (startPos + 1 + j + COLUMNS) % COLUMNS << " DOESNOT HAVE O !" << endl;
				cout << "resetting count to 0" << endl;
				cnt = 0;
			}

			if (cnt == countToWin) {
				cout << "got enough to consider a win for O" << endl;
				noOfWinsPlayerO++;
				cnt = 0;
				break;
			}
		}
	}*/

	//old code
	/*int c1 = 0, c2 = 1, c3 = (COLUMNS - 2), c4 = (COLUMNS - 1);

	for (int i = 0; i < ROWS; i++) {
		//horizontal

		if (grid[i][c1] != '*' && grid[i][c2] != '*' && grid[i][c3] != '*' && grid[i][c4] != '*') {
			if (grid[i][c1] == 'X' && grid[i][c2] == 'X' && grid[i][c3] == 'X' && grid[i][c4] == 'X') {
				noOfWinsPlayerX++;
			}
			if (grid[i][c1] == 'O' && grid[i][c2] == 'O' && grid[i][c3] == 'O' && grid[i][c4] == 'O') {
				noOfWinsPlayerO++;
			}
		}

		//diagonal upwards
		if (i < (ROWS - 3)) {
			if (grid[i][c4] == 'X' && grid[i + 1][c3] == 'X' && grid[i + 2][c2] == 'X' && grid[i + 3][c1] == 'X') {
				noOfWinsPlayerX++;
			}
			if (grid[i][c4] == 'O' && grid[i + 1][c3] == 'O' && grid[i + 2][c2] == 'O' && grid[i + 3][c1] == 'O') {
				noOfWinsPlayerO++;
			}
		}

		//diagonal downwards
		if (i < (ROWS - 3)) {
			if (grid[i][c1] == 'X' && grid[i + 1][c2] == 'X' && grid[i + 2][c3] == 'X' && grid[i + 3][c4] == 'X') {
				noOfWinsPlayerX++;
			}
			if (grid[i][c1] == 'O' && grid[i + 1][c2] == 'O' && grid[i + 2][c3] == 'O' && grid[i + 3][c4] == 'O') {
				noOfWinsPlayerO++;
			}
		}
	}*/

}

bool checkIfWon(int rowID, int columnID, char c) {
	//using the given position find it there is any winning condition (horizontal / vertical / diagonal)
	//goto used to avoid subsequent loops
	bool flag = true;
	while (flag) {
		//edge case top left
		if (rowID == 0) {
			int tempCnt = 0;
			if (columnID == 0) {
				//top left corner
				//checking horizontal
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					} 
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				//checking vertical
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				//checking diagonal (top left towards bottom right)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}
			}
			else if (columnID == (COLUMNS - 1)) {
				//top right corner
				// checking horizontal
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (top right towards bottom left)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}
			} 
			else {
				//top row

				// checking horizontal left side
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				// checking horizontal right side
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal left side down
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal right side down
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition;
				}
				else {
					tempCnt = 0;
				}
			}

			checkCondition:
			if (tempCnt == (countToWin - 1)) {
				flag = true;
				break;
			}
		} 
		else if (columnID == 0) {
			int tempCnt = 0;
			if (rowID == (ROWS - 1)) {
				//bottom left

				// checking horizontal
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical (upwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i , columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (bottom left to top right)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

			}
			else {
				//first column

				// checking horizontal
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical (upwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i , columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical (downwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (upwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (downwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID + i, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition2;
				}
				else {
					tempCnt = 0;
				}
			}

			checkCondition2:
			if (tempCnt == (countToWin - 1)) {
				flag = true;
				break;
			}
		} 
		else if (rowID == (ROWS - 1)) {
			int tempCnt = 0;
			if (columnID == (COLUMNS - 1)) {
				// bottom right

				// checking horizontal
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical (upwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (bottom right towards top left)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}
			} 
			else {
				//last row
				// checking horizontal (left side)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}

				// checking horizontal (right side)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}

				// checking vertical (upwards)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (towards top left)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID - i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}

				// checking diagonal (towards top right)
				for (int i = 1; i < countToWin; i++) {
					bool isInside = checkIfInside(rowID - i, columnID + i, c);
					if (!isInside) { // false
						tempCnt = 0;
						flag = false;
						break;
					}
					else {
						tempCnt++;
					}
				}
				if (tempCnt == (countToWin - 1)) {
					goto checkCondition3;
				}
				else {
					tempCnt = 0;
				}
			}

			checkCondition3:
			if (tempCnt == (countToWin - 1)) {
				flag = true;
				break;
			}
		}
		else if (columnID == (COLUMNS - 1)) {
			//last column
			int tempCnt = 0;
			// checking horizontal
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID, columnID - i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition4;
			}
			else {
				tempCnt = 0;
			}

			// checking vertical (upwards)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID - i, columnID, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition4;
			}
			else {
				tempCnt = 0;
			}

			// checking diagonal (towards top left)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID - i, columnID - i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition4;
			}
			else {
				tempCnt = 0;
			}

			// checking diagonal (towards top right)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID - i, columnID + i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			
			checkCondition4:
			if (tempCnt == (countToWin - 1)) {
				flag = true;
				break;
			}
		}
		else {
			//middle
			int tempCnt = 0;
			// checking horizontal (left side)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID, columnID - i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking horizontal (right side)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID, columnID + i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking vertical (upwards)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID - i, columnID, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking vertical (downwards)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID + i, columnID, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking diagonal (towards top left)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID - i, columnID - i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking diagonal (towards top right)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID - i, columnID + i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking diagonal (towards bottom left)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID + i, columnID - i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			if (tempCnt == (countToWin - 1)) {
				goto checkCondition5;
			}
			else {
				tempCnt = 0;
			}

			// checking diagonal (towards bottom right)
			for (int i = 1; i < countToWin; i++) {
				bool isInside = checkIfInside(rowID + i, columnID + i, c);
				if (!isInside) { // false
					tempCnt = 0;
					flag = false;
					break;
				}
				else {
					tempCnt++;
				}
			}
			
			checkCondition5:
			if (tempCnt == (countToWin - 1)) {
				flag = true;
				break;
			}
		}
	}

	return flag;
}

bool checkIfInside(int rowID, int columnID, char c) {
	if (rowID >= 0 && rowID <= (ROWS - 1)) {
		if (columnID >= 0 && columnID <= (COLUMNS - 1)) {
			if (grid[rowID][columnID] != '*' && grid[rowID][columnID] == c) {
				return true;
			} 
			else {
				return false;
			}
			
		}
		return false;
	}
	return false;
}

void addBall(int rowID, int columnID, char c) {
	if (rowID >= 0 && rowID < ROWS) {
		if (columnID >= 0 && columnID < COLUMNS) {
			grid[rowID][columnID] = c;
		}
	}
}

int getRow(int columnID) {
	for (int i = (ROWS - 1); i >= 0; i--) {
		if (grid[i][columnID] == '*') {
			return i;
		}
	}
	return -1;
}

bool checkIfTie() {
	for (int i = 0; i < ROWS ; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (grid[i][j] == '*') {
				return false;
			}
		}
	}
	return true;
}

void gamePlay(int columnID) {
	//this function performs the basic steps by calling the necessary functions
	if (userSelectedToRemove) {
		//user has choosen to remove a piece
		bool isEmpty = isColumnEmpty(columnID);

		if (isEmpty) {
			cout << "Column is Empty ! Please select another column!" << endl;
		}
		else {
			removeAtPosition((ROWS - 1), columnID);
			checkGrid();

			if (turn) {
				turn = false;
			}
			else {
				turn = true;
			}
		}
	}
	else {
		//user has choosen to add a piece

		bool isFull = isColumnFull(columnID);
		if (isFull) {
			cout << "Column is Full ! Please select another column!" << endl;
		}
		else {
			int rowID = getRow(columnID); // finds the row where to insert
			if (rowID != -1) {
				if (turn) {
					addBall(rowID, columnID, 'X');
					system("CLS");
					printGrid();
					checkGrid();
					turn = false;
				}
				else {
					addBall(rowID, columnID, 'O');
					system("CLS");
					printGrid();
					checkGrid();
					turn = true;
				}
			}
		}
	}
}

void removeAtPosition(int rowID, int columnID) {
	for (int i = (ROWS - 1); i > 0; i--) {
		grid[i][columnID] = grid[i - 1][columnID];
	}
	grid[0][columnID] = '*';
	system("CLS");
	printGrid();
}

void checkGrid() {
	noOfWinsPlayerO = 0;
	noOfWinsPlayerX = 0;
	if (isWrapAroundOn) {
		checkIfWonWrapMode();
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (grid[i][j] != '*') {
				bool result = checkIfWon(i, j, grid[i][j]);
				if (result) {
					if (grid[i][j] == 'X') {
						noOfWinsPlayerX++;
					}
					else {
						noOfWinsPlayerO++;
					}
				}
			}
		}
	}

	if (noOfWinsPlayerO > 0 || noOfWinsPlayerX > 0) {
		if (noOfWinsPlayerO > noOfWinsPlayerX) {
			cout << "Player O wins !"<< endl;
			won = 1;
		}
		else if (noOfWinsPlayerX > noOfWinsPlayerO) {
			cout << "Player X wins !" << endl;
			won = 1;
		}
		else {
			cout << "Its a tie !" << endl;
			won = 0;
		}
	}
	else {
		won = -1;
	}
}