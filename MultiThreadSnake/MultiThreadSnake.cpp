#include "pch.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>

#define MAP_Y 20
#define MAP_X 50

using namespace std;

int Map[MAP_Y][MAP_X];

int snakeSize;
int x;
int y;
int score;
char direction;
bool sleep;
int current = 0;
bool gameOn = true;

void fruit()
{
	int fruitX;
	int fruitY;
	bool valid = false;

	while (!valid)
	{
		fruitY = rand() % (MAP_Y - 3) + 1;
		fruitX = rand() % (MAP_X - 3) + 1;

		valid = true;

		if (Map[fruitY][fruitX] > 0)
		{
			valid = false;
		}
		else if (Map[fruitY - 1][fruitX] > 0 || Map[fruitY + 1][fruitX] > 0)
		{
			valid = false;
		}
		else if (Map[fruitY][fruitX - 1] > 0 || Map[fruitY][fruitX + 1] > 0)
		{
			valid = false;
		}
		else if (Map[fruitY - 1][fruitX - 1] > 0 || Map[fruitY + 1][fruitX - 1] > 0 || Map[fruitY - 1][fruitX + 1] > 0 || Map[fruitY + 1][fruitX + 1] > 0)
		{
			valid = false;
		}
	}
	Map[fruitY][fruitX] = -2;
}



void show_console_cursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void set_cursor_position(int cursorX, int cursorY)
{
	static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	static COORD WritePos;
	WritePos.X = cursorX;
	WritePos.Y = cursorY;
	SetConsoleCursorPosition(hStdOut, WritePos);
}

void find_node(int arg)
{
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (Map[i][j] == arg)
			{
				x = j;
				y = i;
				break;
			}
		}
	}
}

void inputs()
{
	while (gameOn)
	{
		char temp = 0;
		if (_kbhit())
		{
			temp = _getch();
		}
		
		if (temp != 0)
		{
			switch (direction)
			{
				case 'w':
				{
					if (temp == 's')
						temp = 'w';
					break;
				}
				case 's':
				{
					if (temp == 'w')
						temp = 's';
					break;
				}
				case 'd':
				{
					if (temp == 'a')
						temp = 'd';
					break;
				}
				case 'a':
				{
					if (temp == 'd')
						temp = 'a';
					break;
				}
			}
			direction = temp;
		}
	}
}

void repaint()
{
	while (gameOn)
	{
		set_cursor_position(0, 0);
		for (int i = 0; i < MAP_Y; i++)
		{
			for (int j = 0; j < MAP_X; j++)
			{
				if (Map[i][j] == -1)
					cout << '#';
				if (Map[i][j] == 0)
					cout << ' ';
				if (Map[i][j] == 1)
					cout << 'O';
				if (Map[i][j] > 1)
					cout << 'o';
				if (Map[i][j] == -2)
					cout << 'F';
			}
			cout << endl;
		}
		cout << endl << endl << "SCORE: " << score;
	}
}

void move_snake(int plusX, int plusY)
{
	swap(Map[y + plusY][x + plusX], Map[y][x]);
	for (int i = 2; i <= snakeSize; i++)
	{
		int prevX = x;
		int prevY = y;
		find_node(i);
		swap(Map[y][x], Map[prevY][prevX]);
	}
}

void move(int plusX, int plusY)
{
	if (Map[y + plusY][x + plusX] == 0)
	{
		swap(Map[y + plusY][x + plusX], Map[y][x]);
		for (int i = 2; i <= snakeSize; i++)
		{
			int prevX = x;
			int prevY = y;
			find_node(i);
			swap(Map[y][x], Map[prevY][prevX]);
		}
	}
	else if (Map[y + plusY][x + plusX] == -1 || Map[y + plusY][x + plusX] > 0)
	{
		gameOn = false;
		_putch(0);
	}
	else if (Map[y + plusY][x + plusX] == -2)
	{
		Map[y + plusY][x + plusX] = 0;
		swap(Map[y + plusY][x + plusX], Map[y][x]);
		for (int i = 2; i <= snakeSize; i++)
		{
			int prevX = x;
			int prevY = y;
			find_node(i);
			swap(Map[y][x], Map[prevY][prevX]);
		}
		for (int i = 1; i < MAP_Y - 1; i++)
		{
			for (int j = 1; j < MAP_X - 1; j++)
			{
				if (Map[i][j] == snakeSize)
				{
					if (Map[i - 1][j] == snakeSize - 1)
					{
						Map[i + 1][j] = snakeSize + 1;
					}
					else if (Map[i + 1][j] == snakeSize - 1)
					{
						Map[i - 1][j] = snakeSize + 1;
					}
					else if (Map[i][j - 1] == snakeSize - 1)
					{
						Map[i][j + 1] = snakeSize + 1;
					}
					else if (Map[i][j + 1] == snakeSize - 1)
					{
						Map[i][j - 1] = snakeSize + 1;
					}
					snakeSize++;
					score += 10;
					fruit();
					return;
				}
			}
		}
	}
}

void movement()
{
	while (gameOn)
	{
		find_node(1);
		this_thread::sleep_for(0.1s);
		switch (direction)
		{
			case 'w':
			{
				move(0, -1);
				continue;
			}
			case 's':
			{
				move(0, 1);
				continue;
			}
			case 'd':
			{
				move(1, 0);
				continue;
			}
			case 'a':
			{
				move(-1, 0);
				continue;
			}
		}
	}
}

void init_map()
{
	system("cls");
	int tempMap[MAP_Y][MAP_X] =
	{
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1 },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
	};
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			Map[i][j] = tempMap[i][j];
		}
	}
	fruit();
	snakeSize = 5;
	score = 0;
	direction = 'a';
	thread inputs(inputs);
	thread repaint(repaint);
	thread movement(movement);
	inputs.join();
	repaint.join();
	movement.join();
}

int main()
{
	srand(time(NULL));
	char again = 'r';
	while (again == 'r')
	{
		gameOn = true;
		show_console_cursor(false);
		init_map();
		show_console_cursor(true);
		system("cls");
		cout << "GAME OVER\nChcesz zagrac jescze raz? (r)";
		again = _getch();
	}
	return 0;
}