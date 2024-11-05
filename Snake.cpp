///////////////////////////////////////////////////////////
// Sean King                                             //
// C++ file to make a version of the popular snake game. //
// Authored: 5-21-2024                                   //
///////////////////////////////////////////////////////////

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Game Values.
bool GameOver;
const int width = 20;
const int height = 10;
int SnakeX, SnakeY;         // Coordinates of the snake head.
int FruitX, FruitY;         // Coordinates of the fruit.
int score;
int TailX[100], TailY[100]; // Coordinates of the snake tail.
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

/////////////////////////////////////////////////////////////

// Game Functions.
void Setup() {
	GameOver = false;
	dir = STOP;
	SnakeX = width / 2;
	SnakeY = height / 2;
	FruitX = rand() % width;
	FruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls"); // Clears the console after the fruit is eaten by the snake.

	for (int i = 0; i < width + 2; i++) {
		cout << "|";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "|"; // The left wall of the game board.
			}
			if (i == SnakeY && j == SnakeX) {
				cout << "0"; // Head of the snake.
			}
			else if (i == FruitY && j == FruitX) {
				cout << "@"; // The fruit.
			}
			else {
				bool PrintTail = false;
				for (int k = 0; k < nTail; k++) {
					if (TailX[k] == j && TailY[k] == i) {
						cout << "o"; // The tail of the snake.
						PrintTail = true;
					}
				}
				if (!PrintTail) {
					cout << " ";
				}
			}
			if (j == width - 1) {
				cout << "|"; // The right wall of the game board.
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {
		cout << "|";
	}
	cout << endl;

	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		    case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				GameOver = true;
				break;
		}
	}
}

void Logic() {
	int PrevX = TailX[0];
	int PrevY = TailY[0];
	int Prev2X, Prev2Y;

	TailX[0] = SnakeX;
	TailY[0] = SnakeY;

	for (int i = 1; i < nTail; i++) {
		Prev2X = TailX[i];
		Prev2Y = TailY[i];
		TailX[i] = PrevX;
		TailY[i] = PrevY;
		PrevX = Prev2X;
		PrevY = Prev2Y;
	}
	switch (dir) {
	    case LEFT:
		    SnakeX--;
		    break;
		case RIGHT:
			SnakeX++;
			break;
		case UP:
			SnakeY--;
			break;
		case DOWN:
			SnakeY++;
			break;
		default:
			break;
	}
	if (SnakeX < 0 || SnakeX >= width || SnakeY < 0 || SnakeY >= height) {
		GameOver = true;
	}
	for (int i = 0; i < nTail; i++) {
		if (TailX[i] == SnakeX && TailY[i] == SnakeY) {
			GameOver = true;
		}
	}
	if (SnakeX == FruitX && SnakeY == FruitY) {
		score += 10;
		FruitX = rand() % width;
		FruitY = rand() % height;
		nTail++;
	}
}

///////////////////////////////////////////////////////////////////////////////

// Setting up and playing the game.
int main() {

	char Difficulty;
	cout << "Please enter which difficulty you want to play at (H/M/E): ";
	cin >> Difficulty;

	Setup();
	while (!GameOver) {
		Draw();
		Input();
		Logic();
		if (Difficulty == 'H' || Difficulty == 'h') {
			Sleep(50); // Slows down the game so it can play at a normal speed.
		}
		else if (Difficulty == 'M' || Difficulty == 'm') {
			Sleep(100);
		}
		else if (Difficulty == 'E' || Difficulty == 'e') {
			Sleep(200);
		}
	}

	return 0;
}