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

int selectOption()
{
	int optionNum = 0;

	while (true)
	{
		cout << "[1. Player Play]" << std::endl;
		cout << "[2.  CPU  Play ]" << std::endl;
		cout << " >> ";
		cin >> optionNum;

		if (optionNum == 1 || optionNum == 2)
		{
			break;
		}

		gotoxy(0, 0);
		std::cout << "다시 선택하세요!" << std::endl;
	}

	return optionNum;
}

void setCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 50;  //커서 두께(1~100)
	cursorInfo.bVisible = 0;  //TRUE커서 보이게 //FALSE숨기기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void shuffle(int* arr) {	//배열섞기
	srand((unsigned int)time(NULL));

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

	if ((float)(endTime - startDropTime) >= 1000.0f / speed) {
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
			removeLine();
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



// 생성자 & 소멸자
CPU::CPU()
{
	blockPosInfo.clear();
	blankCheckBlock.clear();
	blankCheckBlock_cpy.clear();
	blockPlacementInfo.clear();

	blockLeftmostPosX = 0;
	blockRightmostPosX = 0;
	selectedRotationNum = 0;
	selectedMovePosX = 0;

	startMoveTime = 0;

	isRun = true;
	checkWall = false;
	turnComplete = false;
}

CPU::~CPU()
{

}



// 오버라이딩 & 게임 루프
void CPU::keyInputEvent() 
{
	if (_kbhit()) 
	{
		int key = _getch();
		switch (key)
		{
		case 32:
			gameExit(); // 게임 종료
			break;
		case 80:
		case 112:
			pauseGame(); // 일시 정지
			break;
		}
	}
}

void CPU::update()
{
	AI_Pipeline();
	MoveToSelectPos();
	dropBlock();
	fixBlock();
}

void CPU::render() 
{
	drawMap();
	drawBlock();
	showScore();
}



// 오버라이딩
void CPU::drawInformation() 
{
	gotoxy(15, 17);
	cout << "▶'spacebar' exit";
	gotoxy(15, 19);
	cout << "▶'P' or 'p' pause";

	gotoxy(0, 23);
	cout << "■                    ■";
	gotoxy(0, 24);
	cout << "■■■■■■■■■■■■";
}

void CPU::fixBlock() 
{
	if (checkMoveCrash(x, y + 1, blockForm, blockRotation) == true) 
	{
		if ((float)(endTime - startGroundTime) > 500) 
		{
			for (int i = 0; i < 4; i++) 
			{
				for (int j = 0; j < 4; j++) 
				{
					if (block[blockForm][blockRotation][i][j] == 1) 
					{
						map[i + y][j + x] = 2;
					}
				}
			}
			removeLine();
			blockSet();

			isRun = true; // AI 파이프라인을 다시 수행
			turnComplete = false; // 블록 회전 완료 상태를 false로 전환
		}
	}
}

void CPU::removeLine() 
{
	for (int i = 20; i >= 0; i--) 
	{
		count = 0;
		for (int j = 1; j < 11; j++) 
		{
			if (map[i][j] == 2) 
			{
				count++;
			}
		}

		if (count >= 10) 
		{
			setScore();

			for (int j = 0; i - j >= 0; j++) 
			{
				for (int k = 1; k < 11; k++) 
				{
					if (i - j - 1 >= 0) 
					{
						map[i - j][k] = map[i - j - 1][k];
					}
					else 
					{
						map[i - j][k] = 1;
					}
					map[1][k] = 0;
				}
			}
			i++;
		}
	}
}



// 게임 종료
void CPU::gameExit()
{
	gotoxy(0, 22);
	cout << "■  G A M E  E I X T  ■";
	gotoxy(0, 25);

	exit(0);
}



// AI 파이프라인
void CPU::AI_Pipeline() {

	// 블록을 배치할 좌표를 확인했는데 다시 검사를 하면 배치할 좌표가 달라질 수 있기 때문에 좌표를 확인하면 isRun은 false로 전환
	if (isRun == true) {

		// 블록이 회전했을 때 모양이 달라지므로 빈 칸 개수 계산을 총 4번 실행
		for (blockRotation = 0; blockRotation < 4; blockRotation++) {

			// 빈 칸 확인용 블록 생성
			CreateBlankCheckBlock();

			// 빈 칸 확인용 블록을 검사할 위치로 이동
			MoveBlankCheckBlock();

			// O 블록은 회전해도 모양이 모두 똑같음으로 한 번만 확인 후 break
			if (blockForm == 1) {
				break;
			}
			// I, S, Z 블록은 두 번만 회전하면 나머지는 똑같은 모양이 나오기 때문에 두 번만 확인하고 break
			else if ((blockForm == 0 || blockForm == 3 || blockForm == 4) && blockRotation == 1) {
				break;
			}
		}
		blockRotation = 0;

		// 블록을 이동시킬 좌표 선택
		SelectBlockMovePos();
		isRun = false;
	}
}

// 빈 칸 확인용 블록 생성
void CPU::CreateBlankCheckBlock() {

	// I 블록이 1 번, 3 번 회전한 상태로 (4, 0)좌표에서 생성되면 천장에 겹쳐서 생성되므로 y 값을 +1
	if (blockForm == 0 && (blockRotation == 1 || blockRotation == 3)) {
		y++;
	}
	// J 블록이 3 번 회전한 상태로 (4, 0)좌표에서 생성되면 천장에 겹쳐서 생성되므로 y 값을 +1
	else if (blockForm == 5 && blockRotation == 3) {
		y++;
	}
	// L 블록이 1 번 회전한 상태로 (4, 0)좌표에서 생성되면 천장에 겹쳐서 생성되므로 y 값을 +1
	else if (blockForm == 6 && blockRotation == 1) {
		y++;
	}

	// 블록의 모든 칸의 좌표 정보를 담는 blockPosInfo벡터에 블록의 모든 칸의 좌표 저장
	for (int blockFrameNum = 0; blockFrameNum < 16; blockFrameNum++) {
		std::vector<int> inputValue;

		if (block[blockForm][blockRotation][blockFrameNum / 4][blockFrameNum % 4] == 1) {
			inputValue.push_back(x + (blockFrameNum % 4)); // x 좌표
			inputValue.push_back(y + (blockFrameNum / 4)); // y 좌표
			blockPosInfo.push_back(inputValue);
		}
	}

	// 빈 칸 확인용 블록의 크기를 정하기 위해 현재 블록의 크기 확인
	int startPosX = blockPosInfo[0][0];
	int endPosX = blockPosInfo[0][0];
	int startPosY = blockPosInfo[0][1];
	int endPosY = blockPosInfo[0][1];

	for (int vectorNum = 1; vectorNum < 4; vectorNum++) {
		if (startPosX > blockPosInfo[vectorNum][0]) {
			startPosX = blockPosInfo[vectorNum][0];
		}

		if (endPosX < blockPosInfo[vectorNum][0]) {
			endPosX = blockPosInfo[vectorNum][0];
		}

		if (startPosY > blockPosInfo[vectorNum][1]) {
			startPosY = blockPosInfo[vectorNum][1];
		}

		if (endPosY < blockPosInfo[vectorNum][1]) {
			endPosY = blockPosInfo[vectorNum][1];
		}
	}

	int blockSize_X = (endPosX - startPosX) + 1; // 블록 가로 길이
	int blockSize_Y = (endPosY - startPosY) + 1; // 블록 세로 길이

	// 빈 칸 확인용 블록 생성
	for (int vectorCreatePosY = 0; vectorCreatePosY < blockSize_Y + 1; vectorCreatePosY++) { // 블록의 한 칸 밑까지 공간 상태를 확인하기 위해 블록 세로 길이에 +1
		std::vector<int> inputValue;

		for (int vectorCreatePosX = 0; vectorCreatePosX < blockSize_X + 2; vectorCreatePosX++) { // 블록의 좌, 우로 한 칸씩 더 공간 상태를 확인하기 위해 블록의 가로 길이에 +1
			inputValue.push_back(0);
		}
		blankCheckBlock.push_back(inputValue);
	}

	// 빈 칸 확인용 블록 안에 현재 map에 나올 블록을 저장
	for (int vectorNum = 0; vectorNum < blockPosInfo.size(); vectorNum++) {
		int blockPosX = (blockPosInfo[vectorNum][0] + 1) - startPosX; // 빈 칸 확인용 블록의 가운데에 현재 map에 나올 블록을 저장하기 위해 블록 삽입 시작 X좌표에 +1
		int blockPosY = blockPosInfo[vectorNum][1] - startPosY;

		blankCheckBlock[blockPosY][blockPosX] = 1;
	}

	// 블록이 배치될 수 있는 가장 왼쪽의 X 좌표
	int moveLeftCount = 0; // 블록이 왼쪽으로 움직인 횟수

	while (checkWall != true) {
		// 블록이 생성되는 위치에 벽이 있는지 확인
		for (int blockFrameNum = 0; blockFrameNum < 16; blockFrameNum++) {
			if (block[blockForm][blockRotation][blockFrameNum / 4][blockFrameNum % 4] == 1) {
				// 블록의 좌표를 map 기준으로 계산
				int mapPosX = (x - moveLeftCount) + (blockFrameNum % 4);
				int mapPosY = y + (blockFrameNum / 4);

				if (map[mapPosY][mapPosX] == 1) {
					checkWall = true;
				}
			}
		}

		// 블록과 벽이 겹치지 않았을 경우 왼쪽으로 한 칸 이동
		if (checkWall == false) {
			moveLeftCount++;
		}
		// 블록과 벽이 겹쳤을 경우 오른쪽으로 한 칸 이동 후 X좌표를 blockLeftmostPosX에 저장
		else {
			moveLeftCount--;
			blockLeftmostPosX = x - moveLeftCount;
		}
	}
	checkWall = false;

	// 블록이 배치될 수 있는 가장 오른쪽의 X 좌표
	int moveRightCount = 0; // 블록이 오른쪽으로 움직인 횟수

	while (checkWall != true) {
		// 블록이 생성되는 위치에 벽이 있는지 확인
		for (int blockFrameNum = 0; blockFrameNum < 16; blockFrameNum++) {
			if (block[blockForm][blockRotation][blockFrameNum / 4][blockFrameNum % 4] == 1) {
				// 블록의 좌표를 map 기준으로 계산
				int mapPosX = (x + moveRightCount) + (blockFrameNum % 4);
				int mapPosY = y + (blockFrameNum / 4);

				if (map[mapPosY][mapPosX] == 1) {
					checkWall = true;
				}
			}
		}

		// 블록과 벽이 겹치지 않았을 경우 오른쪽으로 한 칸 이동
		if (checkWall == false) {
			moveRightCount++;
		}
		// 블록과 벽이 겹쳤을 경우 왼쪽으로 한 칸 이동 후 X좌표를 blockRightmostPosX에 저장
		else {
			moveRightCount--;
			blockRightmostPosX = x + moveRightCount;
		}
	}
	checkWall = false;
}

// 빈 칸 확인용 블록을 검사할 위치로 이동
void CPU::MoveBlankCheckBlock() {
	int blankCheckBlockCreatePosX = 0; // map벡터를 기준 빈 칸 확인용 블록이 생성되는 X좌표
	int blankCheckBlockCreatePosY = 1; // map벡터를 기준 빈 칸 확인용 블록이 생성되는 Y좌표

	// 블록이 배치될 수 있는 모든 X 좌표를 확인할 때까지 반복
	while (blockLeftmostPosX < blockRightmostPosX + 1) {
		// 빈 칸 확인용 블록 안에 저장된 블록이 바닥이 겹쳤는지 확인
		for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock.size(); vectorSearchingPosY++) {
			for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock[0].size(); vectorSearchingPosX++) {
				// 빈 칸 확인용 블록이 있는 좌표를 map 기준으로 계산
				int mapPosX = blankCheckBlockCreatePosX + vectorSearchingPosX;
				int mapPosY = blankCheckBlockCreatePosY + vectorSearchingPosY;

				if (blankCheckBlock[vectorSearchingPosY][vectorSearchingPosX] == 1 && (map[mapPosY][mapPosX] == 1 || map[mapPosY][mapPosX] == 2)) {
					checkWall = true;
				}
			}
		}

		// 빈 칸 확인용 블록 안에 저장된 블록이 바닥과 겹치치 않았으면 아래로 한 칸 이동
		if (checkWall == false) {
			blankCheckBlockCreatePosY++;
		}
		// 빈 칸 확인용 블록 안에 저장된 블록이 바닥과 겹쳤으면 위로 한 칸 이동 후 빈 칸 확인
		else {
			blankCheckBlockCreatePosY--;
			blankCheckBlock_cpy = blankCheckBlock; // 빈 칸 확인을 위해 빈 칸 확인용 블록을 복사

			// 빈 칸 확인용 블록 중 벽 또는 저장된 블록과 겹친 부분의 값을 1로 변경
			UpdateBlockOverlapPart(blankCheckBlockCreatePosX, blankCheckBlockCreatePosY);

			std::vector<int> inputValue;
			inputValue.push_back(blockRotation); // 블록 회전 횟수
			inputValue.push_back(blockLeftmostPosX); // 블록이 배치된 부분의 X 좌표
			inputValue.push_back(blankCheckBlockCreatePosY); // 블록이 배치된 부분의 Y 좌표
			inputValue.push_back(GetBlankCount()); // 빈 칸 개수
			blockPlacementInfo.push_back(inputValue); // 검사한 위치의 빈 칸 개수와 블록 회전 횟수, 블록이 배치된 X 좌표, 블록이 배치된 Y 좌표 저장

			blankCheckBlock_cpy.clear();

			blankCheckBlockCreatePosX++; // 빈 칸 확인용 블록이 생성될 X좌표에 +1
			blockLeftmostPosX++; // 빈 칸 확인용 블록 안에 들어있는 블록의 X좌표에도 +1
			blankCheckBlockCreatePosY = 1; // 빈 칸 확인용 블록을 위에서부터 다시 내리면서 검사하기 위해 Y좌표는 1로 초기화
			checkWall = false;
		}
	}

	blockPosInfo.clear();
	blankCheckBlock.clear();
	y = 0;
}

// 빈 칸 확인용 블록과 겹친 부분을 1로 변경
void CPU::UpdateBlockOverlapPart(int posX, int posY) {
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {
			// 빈 칸 확인용 블록이 있는 좌표를 map 기준으로 계산
			int mapPosX = posX + vectorSearchingPosX;
			int mapPosY = posY + vectorSearchingPosY;

			// 벽 또는 블록과 겹쳤을 경우 빈 칸 확인용 블록과 겹친 부분을 1로 변경
			if (map[mapPosY][mapPosX] == 1 || map[mapPosY][mapPosX] == 2) {
				blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] = 1;
			}
		}
	}
}

// 빈 칸 확인용 블록 안의 빈 칸의 개수 가져오기
int CPU::GetBlankCount() {
	int blankCount = 0; // 빈 칸 개수

	// 블록 모양 별로 빈 칸 확인
	// 빈 칸 개수에 변동이 생기는 경우
	// - 빈 칸 개수가 1개 증가 하는 경우 : 블록이 map에 저장되었을 때 map에 구멍이 생기게 하지 않는 부분
	// - 빈 칸 개수가 7개 증가 하는 경우 : 블록이 map에 저장되었을 때 map에 구멍이 생기게 할 수 있는 부분
	// -- 7개를 증가 시키는 이유 : 가능한 map에 구멍이 생겨서 점점 쌓이는 일이 없게 하기 위해서 해당 부분에 빈 칸이 생길 경우 빈 칸 개수를 더 크게 증가시킨다.

	// 빈 칸 개수에 변동이 없는 경우
	// - 블록하고 직접적으로 붙어있지 않는 곳에 빈칸이 있을 경우에는 빈 칸 개수를 변동시키지 않는다.

	switch (blockForm) {
	case 0:
	case 1:
		blankCount = CurrentBlock_IorO(blankCount);
		break;
	case 2:
		blankCount = CurrentBlock_T(blankCount);
		break;
	case 3:
		blankCount = CurrentBlock_S(blankCount);
		break;
	case 4:
		blankCount = CurrentBlock_Z(blankCount);
		break;
	case 5:
		blankCount = CurrentBlock_J(blankCount);
		break;
	case 6:
		blankCount = CurrentBlock_L(blankCount);
		break;
	}
	
	return blankCount;
}

// 현재 블록이 I 또는 O 일때 빈 칸 개수 확인
int CPU::CurrentBlock_IorO(int count) {

	// 빈 칸 확인용 블록 안에 I 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
	// 1□□□□1		1□1				
	// 077770			1□1				
	//					1□1				
	//					1□1
	//					070

	// 빈 칸 확인용 블록 안에 O 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
	// 1□□1
	// 1□□1
	// 0770

	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {

			// 빈 칸 확인용 블록의 해당 좌표가 빈 칸일 경우
			if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0) {

				// 빈 칸 확인용 블록의 가장 밑 왼쪽 또는 오른쪽이 빈 공간이면 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == (blankCheckBlock_cpy.size() - 1) && (vectorSearchingPosX == 0 || vectorSearchingPosX == blankCheckBlock_cpy[0].size() - 1)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 가장 밑 좌/우를 제외한 나머지가 빈 공간이면 빈 칸 개수가 7 만큼 증가
				else if (vectorSearchingPosY == (blankCheckBlock_cpy.size() - 1) && (vectorSearchingPosX > 0 && vectorSearchingPosX < blankCheckBlock_cpy[0].size() - 1)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}
		}
	}

	return count;
}

// 현재 블록이 T 일때 빈 칸 개수 확인
int CPU::CurrentBlock_T(int count) {
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {		

			// 빈 칸 확인용 블록 안에 0 번 회전한 T 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 01□10 						
			// 0□□□0 				
			// 07770		
			if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 0) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 0 또는 4 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 보다 크고 4 보다 작을 경우 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX > 0 && vectorSearchingPosX < 4)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가 
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 1 번 회전한 T 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□10 						
			// 1□□1 				
			// 1□70
			// 0700
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 1) {

				// 빈 칸 확인용 블록의 Y좌표가 0 또는 2 이고 X좌표가 3 인 경우 빈 칸 개수는 변동 X
				if ((vectorSearchingPosY == 0 || vectorSearchingPosY == 2) && vectorSearchingPosX == 3) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 2 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 2 번 회전한 T 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□□□1 						
			// 07□70 				
			// 00700
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 2) {

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 0 또는 4 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 1 또는 3 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 3)) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 1 또는 3 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 3 번 회전한 T 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 01□1 						
			// 1□□1 				
			// 07□1
			// 0070
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 3) {

				// 빈 칸 확인용 블록의 Y좌표가 0 또는 2 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if ((vectorSearchingPosY == 0 || vectorSearchingPosY == 2) && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 1 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}
		}
	}

	return count;
}

// 현재 블록이 S 일때 빈 칸 개수 확인
int CPU::CurrentBlock_S(int count) {
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {

			// 빈 칸 확인용 블록 안에 0 번 회전한 S 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 01□□1 						
			// 1□□70 				
			// 07700	
			if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 0) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 3 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 3) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 4) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 3 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 3 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 1 또는 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 1 번 회전한 S 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□10 						
			// 1□□1 				
			// 07□1	
			// 0070
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 1) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 3 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 3) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 1 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}
		}
	}

	return count;
}

// 현재 블록이 Z 일때 빈 칸 개수 확인
int CPU::CurrentBlock_Z(int count) {
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {

			// 빈 칸 확인용 블록 안에 0 번 회전한 Z 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□□10 						
			// 07□□1 				
			// 00770	
			if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 0) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 4 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 4) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 1 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 2 또는 3 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 2 || vectorSearchingPosX == 3)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 1 번 회전한 Z 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 01□1 						
			// 1□□1 				
			// 1□70	
			// 0700
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 1) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 3) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 2 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}
		}
	}

	return count;
}

// 현재 블록이 J 일때 빈 칸 개수 확인
int CPU::CurrentBlock_J(int count) {
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {

			// 빈 칸 확인용 블록 안에 0 번 회전한 J 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□110 						
			// 1□□□1 				
			// 07770	
			if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 0) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 4 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 4) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 보다 크거나 4 보다 작은 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX > 0 && vectorSearchingPosX < 4)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 1 번 회전한 J 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□□1 						
			// 1□70 				
			// 1□70
			// 0700
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 1) {

				// 빈 칸 확인용 블록의 Y좌표가 1 또는 2 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 또는 2 이고 X좌표가 3 인 경우 빈 칸 개수는 변동 X
				else if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 3) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 2 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 2 번 회전한 J 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□□□1 						
			// 077□1 				
			// 00071
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 2) {

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 1 && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 1 또는 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2)) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 1 또는 2 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 2 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 3 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 3) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 3 번 회전한 J 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 01□1 						
			// 01□1 				
			// 1□□1
			// 0770
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 3) {

				// 빈 칸 확인용 블록의 Y좌표가 0 또는 1 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if ((vectorSearchingPosY == 0 || vectorSearchingPosY == 1) && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 1 또는 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}
		}
	}

	return count;
}

// 현재 블록이 L 일때 빈 칸 개수 확인
int CPU::CurrentBlock_L(int count) {
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < blankCheckBlock_cpy.size(); vectorSearchingPosY++) {
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < blankCheckBlock_cpy[0].size(); vectorSearchingPosX++) {

			// 빈 칸 확인용 블록 안에 0 번 회전한 L 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 011□1 						
			// 1□□□1 				
			// 07770
			if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 0) {

				// 빈 칸 확인용 블록의 Y좌표가 0 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 보다 크거나 4 보다 작을 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX > 0 && vectorSearchingPosX < 4)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 1 번 회전한 L 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□10 						
			// 1□10 				
			// 1□□1
			// 0770
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 1) {

				// 빈 칸 확인용 블록의 Y좌표가 0 또는 1 이고 X좌표가 3 인 경우 빈 칸 개수는 변동 X
				if ((vectorSearchingPosY == 0 || vectorSearchingPosY == 1) && vectorSearchingPosX == 3) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 1 또는 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2)) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 2 번 회전한 L 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			// 1□□□1 						
			// 1□770 				
			// 07000
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 2) {

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 2 또는 3 인 경우 빈 칸 개수는 7 만큼 증가
				if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 2 || vectorSearchingPosX == 3)) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 이고 X좌표가 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 4) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 0 또는 2 또는 3 또는 4 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3 || vectorSearchingPosX == 4)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 2 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}

			// 빈 칸 확인용 블록 안에 3 번 회전한 L 블록이 들어있는 경우 숫자에 해당하는 부분이 빈 칸일 경우 그 숫자만큼 빈 칸 개수 증가
			//1□□1 						
			//07□1 				
			//07□1
			//0070
			else if (blankCheckBlock_cpy[vectorSearchingPosY][vectorSearchingPosX] == 0 && blockRotation == 3) {

				// 빈 칸 확인용 블록의 Y좌표가 1 또는 2 이고 X좌표가 0 인 경우 빈 칸 개수는 변동 X
				if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 0) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 1 또는 2 이고 X좌표가 1 인 경우 빈 칸 개수는 7 만큼 증가
				else if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 1) {
					count += 7;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 0 또는 1 또는 3 인 경우 빈 칸 개수는 변동 X
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3)) {
					count += 0;
				}

				// 빈 칸 확인용 블록의 Y좌표가 3 이고 X좌표가 2 인 경우 빈 칸 개수는 7 만큼 증가
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 2) {
					count += 7;
				}

				// 나머지 부분은 1 만큼 증가
				else {
					count++;
				}
			}
		}
	}

	return count;
}

// 블록을 이동시킬 좌표 선택
void CPU::SelectBlockMovePos() {

	// 가장 낮은 곳에 배치된 블록의 Y 좌표 탐색
	int placementPosY = blockPlacementInfo[0][2];

	for (int vectorNum = 1; vectorNum < blockPlacementInfo.size(); vectorNum++) {
		if (placementPosY < blockPlacementInfo[vectorNum][2]) {
			placementPosY = blockPlacementInfo[vectorNum][2];
		}
	}

	// 가장 낮은 곳에 배치된 블록하고 높이 차이가 6 이상되면 탑을 쌓게 되는 경우가 많아서 가장 낮은 곳에 배치된 블록하고 높이 차이가 6 이상 되지 않는 것만 저장
	std::vector<std::vector<int>> heightComparison; // blockPlacementInfo 벡터에서 가장 낮은 곳에 배치된 블록하고 높이 차이가 6 이상되지 않는 부분만 저장할 벡터

	for (int vectorNum = 0; vectorNum < blockPlacementInfo.size(); vectorNum++) {
		std::vector<int> inputValue;

		if (blockPlacementInfo[vectorNum][2] + 6 > placementPosY) {
			inputValue.push_back(blockPlacementInfo[vectorNum][0]); // 블록 회전 횟수
			inputValue.push_back(blockPlacementInfo[vectorNum][1]); // 블록이 배치된 부분의 X 좌표
			inputValue.push_back(blockPlacementInfo[vectorNum][2]); // 블록이 배치된 부분의 Y 좌표
			inputValue.push_back(blockPlacementInfo[vectorNum][3]); // 빈 칸 개수
			heightComparison.push_back(inputValue);
		}
	}
	blockPlacementInfo.clear();

	// 가장 적은 빈 칸 개수 탐색
	int smallestBlankCountNum = heightComparison[0][3];

	for (int vectorNum = 1; vectorNum < heightComparison.size(); vectorNum++) {
		if (smallestBlankCountNum > heightComparison[vectorNum][3]) {
			smallestBlankCountNum = heightComparison[vectorNum][3];
		}
	}

	// 가장 적은 빈 칸 개수 정보를 가지고 있는 부분만 따로 저장
	std::vector<std::vector<int>> smallestBlank; // heightComparison벡터에서 가장 적은 빈 칸을 정보를 담고 있는 벡터 부분만 저장할 벡터

	for (int vectorNum = 0; vectorNum < heightComparison.size(); vectorNum++) {
		std::vector<int> inputValue;

		if (smallestBlankCountNum == heightComparison[vectorNum][3]) {
			inputValue.push_back(heightComparison[vectorNum][0]); // 블록 회전 횟수
			inputValue.push_back(heightComparison[vectorNum][1]); // 블록이 배치된 부분의 X 좌표
			inputValue.push_back(heightComparison[vectorNum][2]); // 블록이 배치된 부분의 Y 좌표
			smallestBlank.push_back(inputValue);
		}
	}

	// 가장 낮은 곳에 배치된 블록의 Y 좌표 탐색
	placementPosY = smallestBlank[0][2];

	for (int vectorNum = 1; vectorNum < smallestBlank.size(); vectorNum++) {
		if (placementPosY < smallestBlank[vectorNum][2]) {
			placementPosY = smallestBlank[vectorNum][2];
		}
	}

	// 가장 낮은 곳에 배치된 블록의 Y 좌표와 같은 Y 좌표를 가진 벡터 부분만 따로 저장
	std::vector<std::vector<int>> biggestPosY; // smallestBlank벡터에서 가장 낮은 Y 좌표 정보를 담고 있는 벡터 부분만 저장할 벡터

	for (int vectorNum = 0; vectorNum < smallestBlank.size(); vectorNum++) {
		std::vector<int> inputValue;

		if (placementPosY == smallestBlank[vectorNum][2]) {
			inputValue.push_back(smallestBlank[vectorNum][0]);
			inputValue.push_back(smallestBlank[vectorNum][1]);
			biggestPosY.push_back(inputValue);
		}
	}

	// 회전상태 및 이동시킬 X좌표 선택
	int randValue = rand() % biggestPosY.size();

	selectedRotationNum = biggestPosY[randValue][0];
	selectedMovePosX = biggestPosY[randValue][1];
}

// 선택한 위치로 블록을 이동
void CPU::MoveToSelectPos() {
	endTime = clock();

	if ((float)(endTime - startMoveTime) >= 200.0f) {
		
		// 블록을 0.5초마다 회전
		if (turnComplete != true) {
			if (selectedRotationNum != blockRotation) {
				moveBlockRotate();
			}
			else {
				turnComplete = true;
			}
		}
		// 회전을 완료했으면 블록을 0.5초마다 이동
		else if (turnComplete == true) {
			if (selectedMovePosX > x) {
				moveBlockRight();
			}
			else if (selectedMovePosX < x) {
				moveBlockLeft();
			}
			// 회전 및 이동 모두 완료했으면 블록을 하드드롭
			else {
				moveBlockHardDrop();
			}
		}
		startMoveTime = clock();
	}
}