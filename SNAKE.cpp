using namespace std;
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <windows.h>

//#define MAX 50
int InitialLength =15,q,e;
char Screen[25][80]; // What to show on the screen
char bait;
bool akbar=true;
bool masoudd=false;
int Direction[25][80]; // Movement direction of each part of the snake body (1 -> Right, 2 -> Up, 3 -> Left, 4 ->  Down, 0 -> No part of the snake)
int BreakPoint[25][80]; // Changing direction of each part of the snake body due to pressing arror keys. Numbering is the sam as above.
int head_col, head_row, endd = 1, bait_col, bait_row; // Cooredinates of the snake head. 
// Gets a 25*80 character matrix and shows simlutaneously ob the screen.
void raandom()
{
	while (akbar)
	{
		bait_col = rand() % 80;
		bait_row = rand() % 25;
	
				
			if (Screen[bait_row][bait_col]==' ')
			{
				Screen[bait_row][bait_col] = '$';
				return;
			}
		
	}
}
void WriteScreenData(char Buffer[25][80])
{
	HANDLE hNewScreenBuffer;
	SMALL_RECT screenRect;
	CHAR_INFO chiBuffer[25 * 80];
	COORD coordBufSize, coordBufCoord;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			chiBuffer[i * 80 + j].Char.AsciiChar = chiBuffer[i * 80 + j].Char.UnicodeChar = Buffer[i][j];
			chiBuffer[i * 80 + j].Attributes = 7;
		}
	}
	hNewScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hNewScreenBuffer);
	screenRect.Top = 0; screenRect.Left = 0;
	screenRect.Bottom = 24; screenRect.Right = 79;
	coordBufSize.Y = 25; coordBufSize.X = 80;
	coordBufCoord.X = 0; coordBufCoord.Y = 0;
	WriteConsoleOutput(hNewScreenBuffer, chiBuffer, coordBufSize, coordBufCoord, &screenRect);
}
void DrawSnake()
{
	system("cls");
	WriteScreenData(Screen);
}
void Start()
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{

			Screen[i][j] = ' ';
			Direction[i][j] = BreakPoint[i][j] = 0;

		}

	}
	//DrawSnake();
	srand(time(NULL));

}
void Get()
{
	if (_kbhit())
	{
		char ch = _getch();
		if (ch == 27)
			exit(0);

		if (ch == -32)
		{
			ch = _getch();
			if (ch == 77 && endd != 3)
			{
				endd = 1;
				BreakPoint[head_row][head_col] = 1; // Go right when arrived at this coordination
			}

			else if (ch == 72 && endd != 4)
			{
				endd = 2;
				BreakPoint[head_row][head_col] = 2; // Go up when arrived at this coordination
			}

			else if (ch == 75 && endd != 1)
			{
				endd = 3;
				BreakPoint[head_row][head_col] = 3; // Go left when arrived at this coordination
			}

			else if (ch == 80 && endd != 2)
			{
				endd = 4;
				BreakPoint[head_row][head_col] = 4; // Go down when arrived at this coordination

			}

		}
	}

}
void masoud()
{
	
	

	for (int x = 0; x <25; x++)
	{

		for (int y = 0; y < 80; y++)
		{

			if (Screen[x][y] == '+')
			{

				if (Direction[x][y] == 1)
				{
					//going right
					if (y>0)
					{
						Screen[x][y] = '*';
						Screen[x][y - 1] = '+';
						Direction[x][y] = 1;


						
						Direction[x][y-1]=1;
						InitialLength++;
						cout << "\a";
						raandom();
						
					}
					else
					{
						Screen[x][y] = '*';
						Screen[x][79] = '+';
						Direction[x][y] = 1;


						InitialLength++;
						cout << "\a";
						Direction[x][79] = 1;

						raandom();
					}
					
					return;
				}

				else if (Direction[x][y] == 2)
				{//going up

					if (x<24)
					{
						Screen[x][y] = '*';
						Screen[x + 1][y] = '+';
						Direction[x][y] = 2;


						InitialLength++;
						cout << "\a";
						Direction[x+1][y] = 2;

						raandom();
					}
					else
					{
						Screen[x][y] = '*';
						Screen[0][y] = '+';
						Direction[x][y] = 2;					
						Direction[0][y] = 2;
						InitialLength++;
						cout << "\a";
						raandom();
					}
					
					return;

				}

				else if (Direction[x][y] == 3)
				{//going left

					if (y<79)
					{
						Screen[x][y] = '*';
						Screen[x][y + 1] = '+';
						Direction[x][y] = 3;
						cout << "\a";
						InitialLength++;
						
						Direction[x][y+1] = 3;

						raandom();
					}
					else
					{
						Screen[x][y] = '*';
						Screen[x][0] = '+';
						Direction[x][y] = 3;
						cout << "\a";
						InitialLength++;
						
						Direction[x][0] = 3;

						raandom();
					}
					return;

				}

				else if (Direction[x][y] == 4)
				{//going down

					if (x>0)
					{
						Screen[x][y] = '*';
						Screen[x - 1][y] = '+';
						Direction[x][y] = 4;
						Direction[x-1][y] = 4;
						cout << "\a";
						InitialLength++;
						raandom();
						return;
					}
					else
					{
						Screen[x][y] = '*';
						Direction[x][y] = 4;
						Screen[24][y] = '+';
						Direction[24][y] = 4;
						cout << "\a";
						InitialLength++;
						raandom();
						return;


					}
					
				}



			}

		}
	}
}
void FirstStep()
{

	head_col = rand() % 80;

	if (head_col< InitialLength - 1)
	{
		head_col = InitialLength - 1;
	}
	head_row = rand() % 25;
	Screen[head_row][head_col] = '&';
	Direction[head_row][head_col] = 1;
	bait_col = rand() % 80;
	bait_row = rand() % 25;


	//between + , &
	for (int i = 1; i < InitialLength - 1; i++)
	{

		Screen[head_row][head_col - i] = '*';
		Direction[head_row][head_col - i] = 1;//first Direction//set for all charactors//right

	}

	Screen[bait_row][bait_col] = '$';
	Screen[head_row][head_col - InitialLength + 1] = '+';
	Direction[head_row][head_col - InitialLength + 1] = 1;

	DrawSnake();
	//_getch();
}
void Newlocation()
{
	Get();
	
	
	char NewScreen[25][80];
	int NewDirection[25][80];

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			NewScreen[i][j] = ' ';
			NewDirection[i][j] = 0;

		}
	}

	/////////////////////////////////////////////////////////////////////////
	//chech all parts of snake

	for (int i = 0; i < 25; i++)
	{

		for (int j = 0; j < 80; j++)
		{

			if (Screen[head_row][head_col]=='*')
			{
				
					masoudd = true;
					return;
				
			}


			if (Screen[i][j] != ' ')
			{

				if ( BreakPoint[i][j] != 0 )
				{
					Direction[i][j] = BreakPoint[i][j];
				}
				if (Screen[i][j] == '+')
				{
					BreakPoint[i][j] = 0;
				}


				switch (Direction[i][j])
				{
					//Direction and Screen are our variables;
				case 1://go right//one charactar
				{
					if (j<79)
					{

						if (Screen[bait_row][bait_col] == Screen[head_row][head_col] && Direction[head_row][head_col]==1)
						{
							Screen[bait_row][bait_col] = ' ';
							Direction[bait_row][bait_col] = 0;

							Screen[bait_row][bait_col] = '&';
							Direction[bait_row][bait_col] = 1;

							masoud();							
							return;
						}
						
						
						NewScreen[i][j + 1] = Screen[i][j];
						NewDirection[i][j + 1] = 1;
						if (Screen[i][j] == '&')
							{
								head_col = j + 1;
								head_row = i;
							}	
					}
					else
					{

					
						NewScreen[i][0] = Screen[i][j];
						NewDirection[i][0] = 1;
						if (Screen[i][j] == '&')
						{
							head_col = 0;
							head_row = i;
						}

					}


				}break;

				case 2://going up
				{
					if (i>0)
					{
						if (Screen[bait_row][bait_col] == Screen[head_row][head_col] && Direction[head_row][head_col] == 2)
						{
							Screen[bait_row][bait_col] = ' ';
							Direction[bait_row][bait_col] = 0;
							Screen[bait_row][bait_col] = '&';
							Direction[bait_row][bait_col] = 2;


							masoud();
							return;
						}


						NewScreen[i - 1][j] = Screen[i][j];
						NewDirection[i - 1][j] = 2;
						if (Screen[i][j] == '&'){ 
							head_row = i - 1;
							head_col = j;
						}

					}
					else
					{
						NewScreen[24][j] = Screen[i][j];
						NewDirection[24][j] = 2;
						if (Screen[i][j] == '&'){
							head_row = 24;
						}

					}

				}
				break;

				case 3://going left
				{
					if (j>0)
					{

						if (Screen[bait_row][bait_col] == Screen[head_row][head_col] && Direction[head_row][head_col] == 3)
						{
							Screen[bait_row][bait_col] = ' ';
							Direction[bait_row][bait_col] = 0;
							Screen[bait_row][bait_col] = '&';
							Direction[bait_row][bait_col] = 3;
							masoud();
							return;
						}

						
						NewScreen[i][j - 1] = Screen[i][j];
						NewDirection[i][j - 1] = 3;
						if (Screen[i][j] == '&')
						{
							head_col = j - 1;
						
						}

					}
					else
					{
						NewScreen[i][79] = Screen[i][j];
						NewDirection[i][79] = 3;
						if (Screen[i][j] == '&'){ head_col = 79; }

					}

				}
				break;

				case 4:
				{
					if (i<24)
					{
						if (Screen[bait_row][bait_col] == Screen[head_row][head_col] && Direction[head_row][head_col] == 4)
						{
							Screen[bait_row][bait_col] = ' ';
							Direction[bait_row][bait_col] = 0;
							Screen[bait_row][bait_col] = '&';
							Direction[bait_row][bait_col] = 4;

							masoud();
							return;
						}

						NewScreen[i + 1][j] = Screen[i][j];
						NewDirection[i + 1][j] = 4;
						if (Screen[i][j] == '&'){ head_row = i + 1; }

					}
					else
					{
						NewScreen[0][j] = Screen[i][j];
						NewDirection[0][j] = 4;
						if (Screen[i][j] == '&'){ head_row = 0; }

					}

				}
				break;
				}
			}
		}

	}

	
	for (int i = 0; i <25; i++)
	{
		for (int j = 0; j < 80; j++)
		{


			Screen[i][j] = NewScreen[i][j];
			Direction[i][j] = NewDirection[i][j];


		}


	}

	Screen[bait_row][bait_col] = '$';
	

}
void main(void)
{
	Start();
	FirstStep();

	while (1)
	{
		Sleep(100);
		Newlocation();
		DrawSnake();
		if (masoudd==true)
		{
			system("cls");
			break;
		}

	}

	cout<<"you lose :("<<"\n";
	cout << "YOUR SCORE :=>" << (InitialLength - 15);



	_getch();
}
