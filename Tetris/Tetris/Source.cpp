//under git


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <windows.h>
//#include <conio.h>

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22
#define MINO_WIDTH 4
#define MINO_HEIGHT 4
#define ASCII_HEIGHT 7
#define ASCII_WIDTH 7


char field[FIELD_HEIGHT][FIELD_WIDTH];
char minobuff[MINO_WIDTH][MINO_HEIGHT];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];

enum {
	MINO_TYPE_I,
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_T,
	MINO_TYPE_MAX,
};

enum {
	MINO_ANGLE_0,
	MINO_ANGLE_90,
	MINO_ANGLE_180,
	MINO_ANGLE_270,
	MINO_ANGLE_MAX
};


char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] = {
	//MINO_TYPE_I,
	{
		//MINO_ANGLE_0,
		{
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			0,0,0,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
		},
		//MINO_ANGLE_270,
		{
			0,0,0,0,
			1,1,1,1,
			0,0,0,0,
			0,0,0,0,
		}
	},
	//MINO_TYPE_O,
	{
		//MINO_ANGLE_0,
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270,
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
		}
	},
	//MINO_TYPE_S,
	{
		//MINO_ANGLE_0,
		{
			0,0,0,0,
			0,1,1,0,
			1,1,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			0,1,0,0,
			0,1,1,0,
			0,0,1,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,0,0,
			0,0,1,1,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_270,
		{
			0,1,0,0,
			0,1,1,0,
			0,0,1,0,
			0,0,0,0,
		}
	},
	//MINO_TYPE_Z,
	{
		//MINO_ANGLE_0,
		{
			0,0,0,0,
			1,1,0,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			0,0,1,0,
			0,1,1,0,
			0,1,0,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,0,0,
			0,1,1,0,
			0,0,1,1,
			0,0,0,0,
		},
		//MINO_ANGLE_270,
		{
			0,0,1,0,
			0,1,1,0,
			0,1,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_J,
	{
		//MINO_ANGLE_0,
		{
			0,0,1,0,
			0,0,1,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			1,1,1,0,
			0,0,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,0,0,
			0,1,1,0,
			0,1,0,0,
			0,1,0,0,
		},
		//MINO_ANGLE_270,
		{
			0,0,0,0,
			0,1,0,0,
			0,1,1,1,
			0,0,0,0,
		},
	},
	//MINO_TYPE_L,
	{
		//MINO_ANGLE_0,
		{
			0,1,0,0,
			0,1,0,0,
			0,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			0,0,1,0,
			1,1,1,0,
			0,0,0,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,0,0,
			0,1,1,0,
			0,0,1,0,
			0,0,1,0,
		},
		//MINO_ANGLE_270,
		{
			0,0,0,0,
			0,1,1,1,
			0,1,0,0,
			0,0,0,0,
		},
	},
	//MINO_TYPE_T,
	{
		//MINO_ANGLE_0,
		{
			0,1,0,0,
			1,1,1,0,
			0,0,0,0,
			0,0,0,0,
		},
		//MINO_ANGLE_90,
		{
			0,0,0,0,
			0,1,0,0,
			1,1,0,0,
			0,1,0,0,
		},
		//MINO_ANGLE_180,
		{
			0,0,0,0,
			0,0,0,0,
			0,1,1,1,
			0,0,1,0,
		},
		//MINO_ANGLE_270,
		{
			0,0,1,0,
			0,0,1,1,
			0,0,1,0,
			0,0,0,0,
		},
	},
};
char ASCII[3][ASCII_HEIGHT][ASCII_WIDTH] = {
	//when 1
  { 0,0,0,0,0,0,0,
	0,0,0,1,0,0,0,
	0,0,1,1,0,0,0,
	0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,
	0,0,1,1,1,0,0,
	0,0,0,0,0,0,0 },
	//when 2
  { 0,0,0,0,0,0,0,
	0,0,1,1,1,0,0,
	0,0,0,0,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,0,0,0,0,
	0,0,1,1,1,0,0,
	0,0,0,0,0,0,0 },
	//when 3
  { 0,0,0,0,0,0,0,
	0,0,1,1,1,0,0,
	0,0,0,0,1,0,0,
	0,0,1,1,1,0,0,
	0,0,0,0,1,0,0,
	0,0,1,1,1,0,0,
	0,0,0,0,0,0,0 },
};

time_t t = time(NULL);  // t is globalize so that it can be used in resetMino()

int minoType = 0, minoAngle = 0;
int minoX = 5, minoY = 0;

int b_minoT, b_minoA;

bool buff;

bool isHit(int _minoX, int _minoY, int _minoType, int _minoAngle);


bool isGameover() {
	int c = 0;
	for (int i = 1; i < FIELD_WIDTH - 1; i++) {
		if (field[1][i])return true;
	}
	return false;
}

void display() {
	if (!buff)memset(minobuff, 0, sizeof(minobuff));//initialize minobuff after start or restart
	if (isGameover()) {
		system("cls");
		printf("Game over!\n");
		printf("Hit ESC to close the window\n");
		printf("Or hit space-key to restart\n");
	}
	else {
		memcpy(displayBuffer, field, sizeof(field));	//update displaybuffer

		for (int i = 0; i < MINO_HEIGHT; i++)
			for (int j = 0; j < MINO_WIDTH; j++)
				displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];	//orイコールとは？

		system("cls");
		printf("storage\n\n");
		for (int i = 0; i < MINO_HEIGHT; i++) {
			for (int j = 0; j < MINO_WIDTH; j++)
				printf(minobuff[i][j] ? "■" : "　");
			printf("\n");
		}

		printf("\n\nyour field\n\n");
		for (int i = 0; i < FIELD_HEIGHT; i++) {
			for (int j = 0; j < FIELD_WIDTH; j++)
				printf(displayBuffer[i][j] ? "■" : "　");
			printf("\n");
		}
		printf("Hit ESC to close the window\n");
		printf("Or hit space-key to restart\n");
	}

}

void resetMino() {
	minoX = rand() % (FIELD_WIDTH - 6) + 1;
	minoY = 0;
	minoType = t % MINO_TYPE_MAX;
	minoAngle = t % MINO_ANGLE_MAX;
}

void store() {
	if (!buff) {
		buff = true;
		b_minoT = minoType;
		b_minoA = minoAngle;
		memcpy(minobuff, minoShapes[minoType][minoAngle], sizeof(minoShapes[minoType][minoAngle]));
		resetMino();
	}
	else {
		if (!isHit(minoX, minoY, b_minoT, b_minoA)) {
			int T = b_minoT, A = b_minoA;
			memcpy(minobuff, minoShapes[minoType][minoAngle], sizeof(minoShapes[minoType][minoAngle]));
			b_minoT = minoType;
			b_minoA = minoAngle;
			minoType = T;
			minoAngle = A;
		}
	}
}

bool isHit(int _minoX, int _minoY, int _minoType, int _minoAngle) {
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			if (minoShapes[_minoType][_minoAngle][i][j]
				&& field[_minoY + i][_minoX + j])
				return true;
	return false;
}

int main() {

	//set window 
	BOOL bRtn;
	HANDLE hand;
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD dwCoord = { 100, 40 };
	SMALL_RECT rctWindowRect = { 0, 0, 30, 35 };

	hand = GetStdHandle(STD_OUTPUT_HANDLE);
	bRtn = SetConsoleScreenBufferSize(hand, dwCoord);
	bRtn = SetConsoleWindowInfo(hand, TRUE, &rctWindowRect);

	//initialization
	t = time(NULL);
	buff = false;
	memset(field, 0, sizeof(field)); // initialize field
	
	//use ASCII art to count down
	system("cls");
	int i = 3;
	while (i > 0) {
		if (t != time(NULL)) {
			system("cls");
			for (int j = 0; j < ASCII_HEIGHT; j++) {
				for (int k = 0; k < ASCII_WIDTH; k++)
					printf(ASCII[i - 1][j][k] ? "■" : "　");
				printf("\n");
			}
			i--;
			t = time(NULL);
		}
	}


	//prepare frame
	for (int i = 0; i < FIELD_HEIGHT; i++)
		field[i][0] = field[i][FIELD_WIDTH - 1] = 1;

	for (int i = 0; i < FIELD_HEIGHT; i++)
		field[FIELD_HEIGHT - 1][i] = 1;
	resetMino();


	while (1) {
		
		//if (_kbhit()) {
			switch (getch()) {
			case 0x1b: //hit esc to exit
				return 0;
			case 0x20: //hit space to restart
				main();
				return 0; //end old game
			case 'j':
				if (!isHit(
					minoX,
					minoY + 1,
					minoType,
					minoAngle))
					minoY++;
				break;
			case 'h':
				if (!isHit(
					minoX - 1,
					minoY,
					minoType,
					minoAngle))
					minoX--;
				break;
			case 'l':
				if (!isHit(
					minoX + 1,
					minoY,
					minoType,
					minoAngle))
					minoX++;
				break;
			case 'k':
				if (!isHit(
					minoX,
					minoY,
					minoType,
					(minoAngle + 1) % MINO_ANGLE_MAX))
					minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
				break;
			case 'r':
				if (!isHit(
					minoX,
					minoY,
					minoType,
					minoAngle))
					store();
				break;
			//}
			display();
		}
		if (t != time(NULL)) {
			t = time(NULL);
			if (isHit(minoX, minoY + 1, minoType, minoAngle))
			{
				for (int i = 0; i < MINO_HEIGHT; i++)
					for (int j = 0; j < MINO_WIDTH; j++)
						//if mino hit the block beneath it, fix it as a field
						field[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
				for (int i = 0; i < FIELD_HEIGHT - 1; i++) {
					bool lineFill = true;
					for (int j = 0; j < FIELD_WIDTH - 1; j++) {
						if (!field[i][j])
							lineFill = false;
					}

					if (lineFill) {

						for (int j = i; 0 < j; j--)
							memcpy(field[j], field[j - 1], FIELD_WIDTH);
					}
				}
				resetMino();
			}
			else
				minoY++;
			display();
		}
	}

	return 0;
}