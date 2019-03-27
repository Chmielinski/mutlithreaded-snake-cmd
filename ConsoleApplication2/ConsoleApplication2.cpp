#include "pch.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <thread>

#define MAP_Y 20
#define MAP_X 50

using namespace std;

int Map[MAP_Y][MAP_X];

int snakeSize;
int x;
int y;
int score;
char direction;

void fruit()
{
	int fruitX;
	int fruitY;
	bool valid = false;

	while (!valid)
	{
		fruitY = rand() % (MAP_Y - 3) + 1;
		fruitX = rand() % (MAP_X - 3) + 1;

		if (Map[fruitY][fruitX] > 0)
		{
			valid = false;
			continue;
		}
		else if (Map[fruitY - 1][fruitX] > 0 || Map[fruitY + 1][fruitX] > 0)
		{
			valid = false;
			continue;
		}
		else if (Map[fruitY][fruitX - 1] > 0 || Map[fruitY][fruitX + 1] > 0)
		{
			valid = false;
			continue;
		}
		else if (Map[fruitY - 1][fruitX - 1] > 0 || Map[fruitY + 1][fruitX - 1] > 0 || Map[fruitY - 1][fruitX + 1] > 0 || Map[fruitY + 1][fruitX + 1] > 0)
		{
			valid = false;
			continue;
		}
		else
		{
			valid = true;
		}
	}
	Map[fruitY][fruitX] = -2;
}

void init_map()
{
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
	direction = 'a';
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
	while (true)
	{
		char temp = _getch();
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
	while (true)
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
		move_snake(plusX, plusY);
	}
	else if (Map[y + plusY][x + plusX] == -1 || Map[y + plusY][x + plusX] > 0)
	{
		set_cursor_position(0, 20);
		cout << "GAME OVER" << endl;
		exit(0);
	}
	else if (Map[y + plusY][x + plusX] == -2)
	{
		Map[y + plusY][x + plusX] = 0;
		move_snake(plusX, plusY);

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
					break;
				}
			}
		}
	}
}

void movement()
{
	while (true)
	{
		find_node(1);
		Sleep(150);
		switch (direction)
		{
			case 'w':
			{
				move(0, -1);
				break;
			}
			case 's':
			{
				move(0, 1);
				break;
			}
			case 'd':
			{
				move(1, 0);
				break;
			}
			case 'a':
			{
				move(-1, 0);
				break;
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	init_map();
	show_console_cursor(false);
	thread inputs(inputs);
	thread repaint(repaint);
	thread movement(movement);
	inputs.join();
	repaint.join();
	movement.join();
	return 0;
}