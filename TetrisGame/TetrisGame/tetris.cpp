
#include "tetris.h"

const int block[7][4][4][4] = {
	{   // I
		{
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0}
		},
		{
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0}
		}
	},
	{   // O
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	},
	{ // T
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // S
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // Z
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // J
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	}

};

int map[22][12]{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

int map_cpy[22][12]{
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4}
};

void setCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 50;  //Ŀ�� �β�(1~100)
	cursorInfo.bVisible = 0;  //TRUEĿ�� ���̰� //FALSE�����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x * 2;	//x��ǥ 2��Ʈ�� �̵�
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int randomCreateBlock() {	//���� �Լ� ��� �յ��ϰ� ����?
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> r(0, 6);
	return r(gen);
}


bool checkMoveCrash(int x, int y, int blockForm, int blockRotation) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				if (map[i + y][j + x] == 1 || map[i + y][j + x] == 2) {	//���̳� ��� �̸� Ʈ�� ��ȯ
					return true;
				}
			}
		}
	}
	return false;
}


void dropBlock(struct BlockData& b, struct CTime& ctime, int speed) {
	ctime.endTime = clock();

	if ((float)(ctime.endTime - ctime.startDropTime) >= 1000 / speed) {
		if (checkMoveCrash(b.x, b.y + 1, b.blockForm, b.blockRotation) == true) {
			return;
		}
		deleteBlock(b);

		b.y++;

		ctime.startDropTime = clock();
		ctime.startGroundTime = clock();

		drawMap();
	}
}

void fixBlock(struct BlockData& b, struct CTime& ctime) {
	if (checkMoveCrash(b.x, b.y + 1, b.blockForm, b.blockRotation) == true) {
		if ((float)(ctime.endTime - ctime.startGroundTime) > 500) {	//0.5��
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[b.blockForm][b.blockRotation][i][j] == 1) {
						map[i + b.y][j + b.x] = 2;
					}
				}
			}

			b.x = 4;	//��� ������ġ�� �ʱ�ȭ
			b.y = 0;
			b.blockForm = randomCreateBlock();	//��� ��������
			b.blockRotation = 0;
		}
	}
}

int gameScore(int count) {
	return count * 10;
}

void removeLine(int& score) {
	int count;

	for (int i = 20; i >= 0; i--) {
		count = 0;	// �������� ī��Ʈ �ʱ�ȭ
		for (int j = 1; j < 11; j++) {
			if (map[i][j] == 2) {	// �����ٿ� ���� ��� ī��Ʈ
				count++;
			}
		}

		if (count >= 10) {	// �����ٿ� ����� 10�� ������ �� 
			score = score + gameScore(count); // ���ھ� ���� ���ٴ� 100��

			for (int j = 0; i - j >= 0; j++) {
				for (int k = 1; k < 11; k++) {
					if (i - j - 1 >= 0) {
						map[i - j][k] = map[i - j - 1][k];
					}

					else {	// õ��κ� �׵θ� ǥ��
						map[i - j][k] = 1;
					}

					map[1][k] = 0;	// ������ õ��θ� ����
				}
			}
		}
	}

	gotoxy(0, 22);
	printf_s("�� S C O R E : %6d ��", score);
}

void keyInputEvent(struct BlockData& b, struct CTime& ctime) {
	int key;

	if (_kbhit()) {
		key = _getch();

		switch (key) {
		case 87:	//W
		case 119:	//w �ð���� 90�� ȸ��
			deleteBlock(b);

			if (checkMoveCrash(b.x, b.y, b.blockForm, (b.blockRotation + 1) % 4) == false) {
				b.blockRotation++;
				if (b.blockRotation >= 4) {
					b.blockRotation = 0;
					ctime.startGroundTime = clock();
				}
			}

			else if (checkMoveCrash(b.x - 1, b.y, b.blockForm, (b.blockRotation + 1) % 4) == false) {
				b.blockRotation++;
				b.x--;
				if (b.blockRotation >= 4) {
					b.blockRotation = 0;
					ctime.startGroundTime = clock();
				}
			}

			else if (checkMoveCrash(b.x + 1, b.y, b.blockForm, (b.blockRotation + 1) % 4) == false) {
				b.blockRotation++;
				b.x++;
				if (b.blockRotation >= 4) {
					b.blockRotation = 0;
					ctime.startGroundTime = clock();
				}
			}
			break;

		case 65:	//A
		case 97:	//a �����̵�
			deleteBlock(b);

			if (checkMoveCrash(b.x - 1, b.y, b.blockForm, b.blockRotation) == false) {
				b.x--;
				ctime.startGroundTime = clock();
			}
			break;

		case 68:	//D
		case 100:	//d �������̵�
			deleteBlock(b);

			if (checkMoveCrash(b.x + 1, b.y, b.blockForm, b.blockRotation) == false) {
				b.x++;
				ctime.startGroundTime = clock();
			}
			break;

		case 83:	//S
		case 115:	//s �Ʒ����̵�
			deleteBlock(b);

			if (checkMoveCrash(b.x, b.y + 1, b.blockForm, b.blockRotation) == false) {
				b.y++;
			}
			break;

		case 32:	//�����̽��� �ϵ���
			deleteBlock(b);

			while (true) {	//�浹������ �������� b.y����
				if (checkMoveCrash(b.x, b.y + 1, b.blockForm, b.blockRotation) == true) {
					break;
				}
				b.y++;
			}
			break;

		case 80:	//P
		case 112:	//p �Ͻ�����
			pauseGame();
		}

		drawMap();
	}

}

void pauseGame() {
	int start = 0;

	gotoxy(0, 22);
	cout << "��    P  A  U  S  E   ��";
	gotoxy(15, 17);
	cout << "��'P' or 'p' start";

	while (true) {
		start = _getch();	//pȤ�� P�� ������ ��������
		if (start == 80 || start == 112) {
			break;
		}
	}

	gotoxy(15, 17);
	cout << "��'P' or 'p' pause";
}

void drawMap() {
	for (int i = 1; i < 11; i++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
		if (map[0][i] == 0) map[0][i] = 1;
	}

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 12; j++) {
			if (map_cpy[i][j] != map[i][j]) {	//����� �ʰ� ����� �� ���� �ٲ� �κи� ���(������ �ּ�ȭ)
				gotoxy(j, i);	//�ٲ�κ� ��ǥ�̵�

				switch (map[i][j])
				{
				case 0:
					cout << "��";
					break;

				case 1:
					cout << "��";
					break;

				case 2:
					cout << "��";
					break;

				case 3:
					cout << "��";
					break;
				}
			}
		}
	}

	copy(&map[0][0], &map[0][0] + 22 * 12, &map_cpy[0][0]);	//����� �� ����
}
void drawBlock(struct BlockData b) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[b.blockForm][b.blockRotation][i][j] == 1) {
				map[b.y + i][b.x + j] = 3;
			}
		}
	}
}

void drawInformation() {
	gotoxy(15,9);
	cout << "��'A' or 'a' left move";
	gotoxy(15,11);
	cout << "��'D' or 'd' right move";
	gotoxy(15, 13);
	cout << "��'W' or 'w' right rotate";
	gotoxy(15, 15);
	cout << "��'S' or 's' soft drop";
	gotoxy(15, 17);
	cout << "��'spacebar' hard drop";
	gotoxy(15, 19);
	cout << "��'P' or 'p' pause";

	gotoxy(0, 23);
	cout << "��                    ��";
	gotoxy(0, 24);
	cout << "�������������";
}

void deleteBlock(struct BlockData b) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[b.blockForm][b.blockRotation][i][j] == 1) {
				map[b.y + i][b.x + j] = 0;
			}
		}
	}
}

void gameExit() {
	for (int i = 1; i < 11; i++) {
		if (map[1][i] == 2) {
			gotoxy(0, 23);
			cout << "��  G A M E  O V E R  ��";
			Sleep(2000);
			exit(0);
		}
	}
}
