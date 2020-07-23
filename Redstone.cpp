#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

bool isWorking;
const int mapW = 20;
const int mapH = 20;
int Map[mapW][mapH];
string mod;
int editChar;
int editCharX, editCharY;

/*
-1 '.' nothing
0 '0' wire (no_signal)
1 '1' wire (signal)
2 '!' redstone_torch (do signal)
3 '*' lamp (off)
4 'X' lamp (on)
E (ERROR) Error
*/

void StartSettings()
{
	isWorking = true;
	mod = "edit";
	editChar = 2;
	editCharX = 0;
	editCharY = 0;
	for (int i=0; i<mapH; i++)
	{
		for (int j=0; j<mapW; j++)
		{
			Map[i][j] = -1;
		}
	}
}

void EditCharMove (int c)
{
	if (c == 0)
	{
		if (editCharX > 0)
		{
			editCharX--;
		}
	}
	else if (c == 2)
	{
		if (editCharX < mapH-1)
		{
			editCharX++;
		}
	}
	else if (c == 1)
	{
		if (editCharY > 0)
		{
			editCharY--;
		}
	}
	else if (c == 3)
	{
		if (editCharY < mapW-1)
		{
			editCharY++;
		}
	}
}

void EditCharChange()
{
	if (editChar == 4)
	{
		editChar = -1;
	}
	else
	{
		editChar++;
	}
}

void ChangeMod()
{
	if (mod == "edit")
	{
		mod = "work";
	}
	else
	{
		mod = "edit";
	}
}

void Control()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'x':
				isWorking = false;
				break;
			case 'r':
				StartSettings();
				break;
			case 'w':
				EditCharMove(0);
				break;
			case 'a':
				EditCharMove(1);
				break;
			case 's':
				EditCharMove(2);
				break;
			case 'd':
				EditCharMove(3);
				break;
			case 'f':
				Map[editCharX][editCharY] = editChar;
				break;
			case 'q':
				ChangeMod();
				break;
			case 'e':
				EditCharChange();
				break;
		}
	}
}

void Logic()
{
	if (mod == "work")
	{
		for (int i=0; i<mapH; i++)
		{
			for (int j=0; j<mapW; j++)
			{
				if (Map[i][j] == 1 || Map[i][j] == 4)
				{
					Map[i][j]--;
				}
			}
		}
		int maxi = mapW*mapH;
		for (int m=0; m<maxi; m++)
		{
			for (int i=0; i<mapH; i++)
			{
				for (int j=0; j<mapW; j++)
				{
					if (Map[i][j] == 1)
					{
						if (i+1 < mapH)
						{
							if (Map[i+1][j] == 0 || Map[i+1][j] == 3) Map[i+1][j]++;
						}
						if (i-1 >= 0)
						{
							if (Map[i-1][j] == 0 || Map[i-1][j] == 3) Map[i-1][j]++;
						}
						if (j+1 < mapW)
						{
							if (Map[i][j+1] == 0 || Map[i][j+1] == 3) Map[i][j+1]++;
						}
						if (j-1 >= 0)
						{
							if (Map[i][j-1] == 0 || Map[i][j-1] == 3) Map[i][j-1]++;
						}
					}
					else if (Map[i][j] == 2)
					{
						if (i+1 < mapH)
						{
							if (Map[i+1][j] == 0 || Map[i+1][j] == 3) Map[i+1][j]++;
						}
						if (i-1 >= 0)
						{
							if (Map[i-1][j] == 0 || Map[i-1][j] == 3) Map[i-1][j]++;
						}
						if (j+1 < mapW)
						{
							if (Map[i][j+1] == 0 || Map[i][j+1] == 3) Map[i][j+1]++;
						}
						if (j-1 >= 0)
						{
							if (Map[i][j-1] == 0 || Map[i][j-1] == 3) Map[i][j-1]++;
						}
					}
				}
			}
		}
	}
}

void Draw()
{
	string s;
	for (int i=0; i<mapH; i++)
	{
		for (int j=0; j<mapW; j++)
		{
			if (mod == "edit" && i == editCharX && j == editCharY)
			{
				s += '/';
			}
			else if (Map[i][j] == -1)
			{
				s += '.';
			}
			else if (Map[i][j] == 0)
			{
				s += '0';
			}
			else if (Map[i][j] == 1)
			{
				s += '1';
			}
			else if (Map[i][j] == 2)
			{
				s += '!';
			}
			else if (Map[i][j] == 3)
			{
				s += '*';
			}
			else if (Map[i][j] == 4)
			{
				s += 'X';
			}
			else
			{
				s += 'E';
			}
		}
		s += "\n";
	}
	system("cls");
	cout << "Redstone Simulator\n\n" << s << "\nMod: " << mod;
	if (mod == "edit")
	{
		cout << "\neditChar: ";
		if (editChar == -1)
		{
			cout << ".";
		}
		else if (editChar == 0)
		{
			cout << "0";
		}
		else if (editChar == 1)
		{
			cout << "1";
		}
		else if (editChar == 2)
		{
			cout << "!";
		}
		else if (editChar == 3)
		{
			cout << "*";
		}
		else if (editChar == 4)
		{
			cout << "X";
		}
		else
		{
			cout << "(ERROR)";
		}
	}
}

int main()
{
	StartSettings();
	while (isWorking)
	{
		Control();
		Logic();
		Draw();
	}
	
	return 0;
}
