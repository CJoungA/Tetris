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

void setCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 50;  //커서 두께(1~100)
	cursorInfo.bVisible = 0;  //TRUE커서 보이게 //FALSE숨기기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void shuffle(int* arr) {	//배열섞기
	srand(time(NULL));

	int temp;
	int rn;
	for (int i = 0; i < 6; i++) {
		rn = rand() % (7 - i) + i;    // 0~6까지 임의의 정수 생성
		temp = arr[i];
		arr[i] = arr[rn];
		arr[rn] = temp;
	}
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x * 2;	//x좌표 2비트씩 이동
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}


void Tetris::getGameSpeed() {
	cout << "속도입력: ";
	cin >> speed;
}

void Tetris::blockSet() {
	x = 4;	//블록 생성위치로 초기화
	y = 0;
	blockRotation = 0;

	arrayIndex++;	//블록 랜덤생성
	if (arrayIndex > 6) {
		arrayIndex = 0;
		shuffle(blockArray);
	}
	blockForm = blockArray[arrayIndex];
}


bool Tetris::checkMoveCrash(int x, int y, int blockForm, int blockRotation) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				if (map[i + y][j + x] == 1 || map[i + y][j + x] == 2) {	//벽 또는 고정된 블록일때 트루 반환
					return true;
				}
			}
		}
	}
	return false;
}


void Tetris::dropBlock() { 
	endTime = clock();

	if ((float)(endTime - startDropTime) >= 1000 / speed) {
		if (checkMoveCrash(x, y + 1, blockForm, blockRotation) == true) {
			return;
		}

		moveBlockSoftDrop();

		startDropTime = clock();
		startGroundTime = clock();

		drawMap();
	}
}

void Tetris::fixBlock() {
	if (checkMoveCrash(x, y + 1, blockForm, blockRotation) == true) {
		if ((float)(endTime - startGroundTime) > 500) {	//0.5초
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						map[i + y][j + x] = 2;	//맵에 고정된 블록 저장
					}
				}
			}
			blockSet();	//블록 정보 초기화 및 블록 선택
		}
	}
}

void Tetris::setScore() {
	score += count * 10;
}

void Tetris::removeLine() {
	for (int i = 20; i >= 0; i--) {
		count = 0;	// 루프마다 카운트 초기화
		for (int j = 1; j < 11; j++) {
			if (map[i][j] == 2) {	// 가로줄에 놓인 블록 카운트
				count++;
			}
		}

		if (count >= 10) {	// 가로줄에 블록이 10개 놓였을 때 
			setScore(); // 스코어 저장 한줄당 100점

			for (int j = 0; i - j >= 0; j++) {
				for (int k = 1; k < 11; k++) {
					if (i - j - 1 >= 0) {
						map[i - j][k] = map[i - j - 1][k];
					}

					else {	// 천장부분 테두리 표시
						map[i - j][k] = 1;
					}

					map[1][k] = 0;	// 내려온 천장두리 제거
				}
			}
		}
	}
}

void Tetris::keyInputEvent() {
	int key;

	if (_kbhit()) {
		key = _getch();

		switch (key) {
		case 87:	//W
		case 119:	//w 시계방향 90도 회전
			moveBlockRotate();
			break;

		case 65:	//A
		case 97:	//a 왼쪽이동
			moveBlockLeft();
			break;

		case 68:	//D
		case 100:	//d 오른쪽이동
			moveBlockRight();
			break;

		case 83:	//S
		case 115:	//s 아래로이동
			moveBlockSoftDrop();
			break;

		case 32:	//스페이스바 하드드롭
			moveBlockHardDrop();
			break;

		case 80:	//P
		case 112:	//p 일시정지
			pauseGame();
			break;
		}

		//drawMap();
	}

}//**********************************압축????하지말기

void Tetris::setBlockRotate() {
	blockRotation++;
	if (blockRotation >= 4) {
		blockRotation = 0;
	}

	startGroundTime = clock();
}

void Tetris::moveBlockRotate() {
	deleteBlock();

	if (checkMoveCrash(x, y, blockForm, (blockRotation + 1) % 4) == false) {
		setBlockRotate();
	}

	else if (checkMoveCrash(x - 1, y, blockForm, (blockRotation + 1) % 4) == false) {
		x--;
		setBlockRotate();
	}

	else if (checkMoveCrash(x + 1, y, blockForm, (blockRotation + 1) % 4) == false) {
		x++;
		setBlockRotate();
	}

	else if (checkMoveCrash(x + 2, y, blockForm, (blockRotation + 1) % 4) == false) {
		x+=2;
		setBlockRotate();
	}
}

void Tetris::moveBlockLeft() {
	deleteBlock();

	if (checkMoveCrash(x - 1, y, blockForm, blockRotation) == false) {
		x--;
		startGroundTime = clock();
	}
}

void Tetris::moveBlockRight() {
	deleteBlock();

	if (checkMoveCrash(x + 1, y, blockForm, blockRotation) == false) {
		x++;
		startGroundTime = clock();
	}
}

void Tetris::moveBlockSoftDrop() {
	deleteBlock();

	if (checkMoveCrash(x, y + 1, blockForm, blockRotation) == false) {
		y++;
	}
}

void Tetris::moveBlockHardDrop() {
	deleteBlock();

	while (true) {	//충돌판정이 날때까지 y증가
		if (checkMoveCrash(x, y + 1, blockForm, blockRotation) == true) {
			break;
		}
		y++;
	}
}

void Tetris::pauseGame() {
	int start = 0;

	gotoxy(0, 22);
	cout << "■    P  A  U  S  E   ■";
	gotoxy(15, 19);
	cout << "▶'P' or 'p' start";

	while (true) {
		start = _getch();	//p혹은 P를 누르면 루프종료
		if (start == 80 || start == 112) {
			break;
		}
	}

	gotoxy(15, 19);
	cout << "▶'P' or 'p' pause";
}


void Tetris::drawCeiling() {
	for (int i = 1; i < 11; i++) { //천장 뚫리면 복구
		if (map[0][i] == 0) map[0][i] = 1;
	}
}

void Tetris::drawMap() {
	drawCeiling();//천장 뚫리면 복구

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 12; j++) {
			if (map_cpy[i][j] != map[i][j]) {	//저장된 맵과 변경된 맵 비교후 바뀐 부분만 출력(깜빡임 최소화)
				gotoxy(j, i);	//바뀐부분 좌표이동

				switch (map[i][j])
				{
				case 0:
					cout << "·";
					break;

				case 1:
					cout << "■";
					break;

				case 2:
					cout << "▣";
					break;

				case 3:
					cout << "□";
					break;
				}
			}
		}
	}

	std::copy(&map[0][0], &map[0][0] + 22 * 12, &map_cpy[0][0]);	//변경된 맵 저장
}

void Tetris::drawBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				map[y + i][x + j] = 3;
			}
		}
	}
}

void Tetris::deleteBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				map[y + i][x + j] = 0;
			}
		}
	}
}

void Tetris::drawInformation() {
	gotoxy(15, 9);
	cout << "▶'A' or 'a' left move";
	gotoxy(15, 11);
	cout << "▶'D' or 'd' right move";
	gotoxy(15, 13);
	cout << "▶'W' or 'w' right rotate";
	gotoxy(15, 15);
	cout << "▶'S' or 's' soft drop";
	gotoxy(15, 17);
	cout << "▶'spacebar' hard drop";
	gotoxy(15, 19);
	cout << "▶'P' or 'p' pause";

	gotoxy(0, 23);
	cout << "■                    ■";
	gotoxy(0, 24);
	cout << "■■■■■■■■■■■■";
}

void Tetris::showScore() {
	gotoxy(0, 22);
	printf_s("■ S C O R E : %6d ■", score);
}


void Tetris::gameOver() {
	for (int i = 1; i < 11; i++) {
		if (map[1][i] == 2) {
			gotoxy(0, 23);
			cout << "■  G A M E  O V E R  ■";

			Sleep(2000);

			exit(0);
		}
	}
}

void Tetris::update() {
	dropBlock();	//업데이트

	fixBlock();

	removeLine();
}

void Tetris::render() {
	drawMap();	//렌더링

	drawBlock();

	showScore();
}