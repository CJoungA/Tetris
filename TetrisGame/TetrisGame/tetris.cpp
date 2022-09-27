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



// ------------------------- Orange Code -------------------------
CPU::CPU()
{
	tetroPos.clear();
	tetro.clear();
	spaceState.clear();
	weightInfo.clear();
	smallestWeight.clear();

	tetroRotationNum = 0;
	tetroCreatePosX = 4;
	tetroCreatePosY = 0;

	tetroLeftmostPosX = 0;
	tetroRightmostPosX = 0;

	weight = 0;

	selectedRotationNum = 0;
	selectedMovePosX = 0;

	searchComplete = false;
	checkWall = false;
}

CPU::~CPU()
{

}

void CPU::keyInputEvent() 
{
	if (_kbhit()) 
	{
		int key = _getch();
		switch (key)
		{
		case 32:
			gameExit();
			break;
		case 80:
		case 112:
			pauseGame();
			break;
		}
	}
}

void CPU::update()
{
	// 시뮬레이션
	TetrisAIAlgorithm();

	// 선택한 위치로 이동 
	MoveToSelectPos();

	// 블록 하강
	dropBlock();

	// 블록 저장
	fixBlock();

	// 라인 제거
	removeLine();

}

void CPU::render() 
{
	// 맵 그리기
	drawMap();

	// 블록 그리기
	drawBlock();

	// 점수
	showScore();
}

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
		{	//0.5초
			for (int i = 0; i < 4; i++) 
			{
				for (int j = 0; j < 4; j++) 
				{
					if (block[blockForm][blockRotation][i][j] == 1) 
					{
						map[i + y][j + x] = 2;	//맵에 고정된 블록 저장
					}
				}
			}
			blockSet();	//블록 정보 초기화 및 블록 선택
			searchComplete = false;
		}
	}
}

void CPU::gameExit()
{
	gotoxy(0, 22);
	cout << "■  G A M E  E I X T  ■";
	gotoxy(0, 25);

	exit(0);
}



// 테트리스 AI 알고리즘
void CPU::TetrisAIAlgorithm()
{
	if (searchComplete != true)
	{
		for (tetroRotationNum = 0; tetroRotationNum < 4; tetroRotationNum++)
		{
			// 테트로미노의 모든 좌표 확인
			TetroPosCheck();

			// 공간 상태를 저장하는 벡터 생성
			CreateSpaceStateVector();

			// 테트로미노가 움직일 수 있는 가장 왼쪽 X 좌표
			LeftmostPosXThatTetroCanMove();

			// 테트로미노가 움직일 수 있는 가장 오른쪽 X 좌표
			RightmostPosXThatTetroCanMove();

			// 움직일 수 있는 모든 X 좌표에서 바닥으로 이동
			TetroMoveToBottom();
		}

		// 가중치가 가장 적은 벡터 찾기
		SearchSmallestWeight();

		// 가장 적은 벡터들 중에서 랜덤으로 하나 뽑기
		SearchMovePos();

		searchComplete = true;
	}
}

// 테트로미노의 모든 좌표 확인
void CPU::TetroPosCheck()
{
	if (blockForm == 0 && (tetroRotationNum == 1 || tetroRotationNum == 3))
	{
		tetroCreatePosY++;
	}

	else if (blockForm == 5 && tetroRotationNum == 3)
	{
		tetroCreatePosY++;
	}

	else if (blockForm == 6 && tetroRotationNum == 1)
	{
		tetroCreatePosY++;
	}

	for (int tetroFrameY = 0; tetroFrameY < 4; tetroFrameY++)
	{
		for (int tetroFrameX = 0; tetroFrameX < 4; tetroFrameX++)
		{
			std::vector<int> inputValue;

			if (block[blockForm][tetroRotationNum][tetroFrameY][tetroFrameX] == 1)
			{
				inputValue.push_back(tetroCreatePosX + tetroFrameX);
				inputValue.push_back(tetroCreatePosY + tetroFrameY);
				tetroPos.push_back(inputValue);
			}
		}
	}
}

// 공간 상태를 저장하는 벡터 생성
void CPU::CreateSpaceStateVector()
{
	int startPosX = tetroPos[0][0];
	int endPosX = tetroPos[0][0];
	int startPosY = tetroPos[0][1];
	int endPosY = tetroPos[0][1];

	// 공간 상태를 저장하는 벡터의 크기 계산
	for (int vectorNum = 1; vectorNum < 4; vectorNum++)
	{
		if (startPosX > tetroPos[vectorNum][0])
		{
			startPosX = tetroPos[vectorNum][0];
		}

		if (endPosX < tetroPos[vectorNum][0])
		{
			endPosX = tetroPos[vectorNum][0];
		}

		if (startPosY > tetroPos[vectorNum][1])
		{
			startPosY = tetroPos[vectorNum][1];
		}

		if (endPosY < tetroPos[vectorNum][1])
		{
			endPosY = tetroPos[vectorNum][1];
		}
	}

	// 공간 상태를 저장하는 벡터 생성
	for (int vectorPosY = 0; vectorPosY < (endPosY - startPosY) + 2; vectorPosY++) // 한 칸 밑까지 빈공간을 확인하기 위해서 Y 좌표는 + 1
	{
		std::vector<int> inputValue;

		for (int vectorPosX = 0; vectorPosX < (endPosX - startPosX) + 1; vectorPosX++)
		{
			inputValue.push_back(0);
		}
		tetro.push_back(inputValue);
	}

	// 공간 상태를 저장하는 벡터 안에 테트로미노 저장
	for (int vectorNum = 0; vectorNum < tetroPos.size(); vectorNum++)
	{
		int tetroPosX = tetroPos[vectorNum][0] - startPosX;
		int tetroPosY = tetroPos[vectorNum][1] - startPosY;

		tetro[tetroPosY][tetroPosX] = 1;
	}
}

// 테트로미노가 움직일 수 있는 가장 왼쪽 X 좌표
void CPU::LeftmostPosXThatTetroCanMove()
{
	int moveTetroLeft = 0;

	while (checkWall != true)
	{
		// 생성되는 위치에 벽이 있을 때까지 확인
		for (int tetroFrameY = 0; tetroFrameY < 4; tetroFrameY++)
		{
			for (int tetroFrameX = 0; tetroFrameX < 4; tetroFrameX++)
			{
				if (block[blockForm][tetroRotationNum][tetroFrameY][tetroFrameX] == 1)
				{
					int mapPosX = (tetroCreatePosX - moveTetroLeft) + tetroFrameX;
					int mapPosY = tetroCreatePosY + tetroFrameY;

					if (map[mapPosY][mapPosX] == 1)
					{
						checkWall = true;
					}
				}
			}
		}

		// 벽을 확인하지 못했으면 왼쪽으로 한 칸 이동
		if (checkWall == false)
		{
			moveTetroLeft++;
		}
		// 벽을 확인했으면 오른쪽으로 한 칸 이동 후 좌표 저장
		else
		{
			moveTetroLeft--;
			tetroLeftmostPosX = tetroCreatePosX - moveTetroLeft;
		}
	}
	checkWall = false;
}

// 테트로미노가 움직일 수 있는 가장 오른쪽 X 좌표
void CPU::RightmostPosXThatTetroCanMove()
{
	int moveTetroRight = 0;

	while (checkWall != true)
	{
		// 생성되는 위치에 벽이 있을 때까지 확인
		for (int tetroFrameY = 0; tetroFrameY < 4; tetroFrameY++)
		{
			for (int tetroFrameX = 0; tetroFrameX < 4; tetroFrameX++)
			{
				if (block[blockForm][tetroRotationNum][tetroFrameY][tetroFrameX] == 1)
				{
					int mapPosX = (tetroCreatePosX + moveTetroRight) + tetroFrameX;
					int mapPosY = tetroCreatePosY + tetroFrameY;

					if (map[mapPosY][mapPosX] == 1)
					{
						checkWall = true;
					}
				}
			}
		}

		// 벽을 확인하지 못했으면 오른쪽으로 한 칸 이동
		if (checkWall == false)
		{
			moveTetroRight++;
		}
		// 벽을 확인했으면 왼쪽으로 한 칸 이동 후 좌표 저장
		else
		{
			moveTetroRight--;
			tetroRightmostPosX = tetroCreatePosX + moveTetroRight;
		}
	}
	checkWall = false;
}

// 움직일 수 있는 모든 X 좌표에서 바닥으로 이동
void CPU::TetroMoveToBottom()
{
	int tetroPosX = 1;
	int tetroPosY = 1;

	// 움직일 수 있는 모든 X 좌표를 확인할 때까지 반복
	while (tetroLeftmostPosX < tetroRightmostPosX + 1)
	{
		// 바닥 확인
		for (int tetroVectorBlockPosY = 0; tetroVectorBlockPosY < tetro.size(); tetroVectorBlockPosY++)
		{
			for (int tetroVectorBlockPosX = 0; tetroVectorBlockPosX < tetro[0].size(); tetroVectorBlockPosX++)
			{
				int mapPosX = tetroPosX + tetroVectorBlockPosX;
				int mapPosY = tetroPosY + tetroVectorBlockPosY;

				if (tetro[tetroVectorBlockPosY][tetroVectorBlockPosX] == 1 && (map[mapPosY][mapPosX] == 1 || map[mapPosY][mapPosX] == 2))
				{
					checkWall = true;
				}
			}
		}

		// 바닥이 확인되지 않았으면 Y축 방향으로 1칸 이동
		if (checkWall == false)
		{
			tetroPosY++;
		}
		// 바닥이 확인되었으면 Y축 방향으로 -1칸 이동 후 가중치 확인
		else
		{
			tetroPosY--;
			spaceState = tetro;

			// 가중치 확인
			CheckWeightLogic(tetroPosX, tetroPosY);

			// 가중치 정보 저장
			std::vector<int> inputValue;

			inputValue.push_back(tetroRotationNum);
			inputValue.push_back(tetroLeftmostPosX);
			inputValue.push_back(weight);
			inputValue.push_back(tetroPosY); // <<------------------------------------------ 추가

			weightInfo.push_back(inputValue);

			inputValue.clear();

			// 일부 값 초기화
			tetroPosX++;
			tetroPosY = 1;
			tetroLeftmostPosX++;
			checkWall = false;
			spaceState.clear();
			weight = 0;
		}
	}

	// 초기화
	tetroPos.clear();
	tetro.clear();
	tetroCreatePosY = 0;
}

// 가중치를 확인하기 위한 로직
void CPU::CheckWeightLogic(int posX, int posY)
{
	// 테트로미노 주변에 채워진 공간 확인
	for (int spaceStatePosY = 0; spaceStatePosY < tetro.size(); spaceStatePosY++)
	{
		for (int spaceStatePosX = 0; spaceStatePosX < tetro[0].size(); spaceStatePosX++)
		{
			int mapPosX = posX + spaceStatePosX;
			int mapPosY = posY + spaceStatePosY;

			if (map[mapPosY][mapPosX] == 1 || map[mapPosY][mapPosX] == 2)
			{
				spaceState[spaceStatePosY][spaceStatePosX] = 1;
			}
		}
	}

	// 테트로미노 주변에 빈 공간 개수 확인
	for (int spaceStatePosY = 0; spaceStatePosY < tetro.size(); spaceStatePosY++)
	{
		for (int spaceStatePosX = 0; spaceStatePosX < tetro[0].size(); spaceStatePosX++)
		{
			if ((blockForm == 5 && selectedRotationNum == 3) || (blockForm == 6 && selectedRotationNum == 1))
			{
				if (spaceState[spaceStatePosY][spaceStatePosX] == 0 && spaceStatePosY < 2)
				{
					weight++;
				}
				else
				{
					weight += 2;
				}
			}
			else
			{
				if (spaceState[spaceStatePosY][spaceStatePosX] == 0 && spaceStatePosY < spaceState.size() / 2)
				{
					weight++;
				}
				else
				{
					weight += 2;
				}
			}

		}
	}
}

// 가중치가 가장 적은 벡터를 찾는 로직
void CPU::SearchSmallestWeight()
{
	int smallestWeightNum = weightInfo[0][2];

	// 가장 적은 가중치 확인
	for (int vectorNum = 1; vectorNum < weightInfo.size(); vectorNum++)
	{
		if (smallestWeightNum > weightInfo[vectorNum][2])
		{
			smallestWeightNum = weightInfo[vectorNum][2];
		}
	}

	// 가장 적은 가중치의 정보를 가지고 있는 벡터 부분만 따로 저장
	for (int vectorNum = 0; vectorNum < weightInfo.size(); vectorNum++)
	{
		std::vector<int> inputValue;

		if (smallestWeightNum == weightInfo[vectorNum][2])
		{
			inputValue.push_back(weightInfo[vectorNum][0]);
			inputValue.push_back(weightInfo[vectorNum][1]);
			inputValue.push_back(weightInfo[vectorNum][3]);
			smallestWeight.push_back(inputValue);
		}
	}
}

// 테트로미노를 움직일 위치를 선택하는 로직
void CPU::SearchMovePos()
{
	
	int biggestPosY = smallestWeight[0][2];

	for (int i = 1; i < smallestWeight.size(); i++)
	{
		if (biggestPosY < smallestWeight[i][2])
		{
			biggestPosY = smallestWeight[i][2];
		}
	}

	for (int i = 0; i < smallestWeight.size(); i++)
	{
		if (biggestPosY == smallestWeight[i][2])
		{
			selectedRotationNum = smallestWeight[i][0];
			selectedMovePosX = smallestWeight[i][1];
		}
	}
	
	weightInfo.clear();
	smallestWeight.clear();
}

// 선택한 위치로 테트로미노를 이동
void CPU::MoveToSelectPos()
{
	if (selectedRotationNum != blockRotation)
	{
		moveBlockRotate();
	}

	if (selectedMovePosX > x)
	{
		moveBlockRight();
	}

	if (selectedMovePosX < x)
	{
		moveBlockLeft();
	}

	/*
	if ((selectedRotationNum == blockRotation) && (selectedMovePosX == x))
	{
		moveBlockHardDrop();
	}
	*/
}