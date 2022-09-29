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



// 생성자 & 소멸자
CPU::CPU()
{
	tetroPos.clear();
	tetroContainer.clear();
	spaceStateContainer.clear();
	deploymentInfo.clear();
	smallestBlank.clear();

	tetroRotationNum = 0;
	tetroCreatePosX = 4;
	tetroCreatePosY = 0;
	tetroLeftmostPosX = 0;
	tetroRightmostPosX = 0;
	blankCount = 0;
	selectedRotationNum = 0;
	selectedMovePosX = 0;

	startMoveTime = 0.0f;

	runAlgorithm = true;
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
	AIAlgorithm();

	MoveToSelectPos();

	dropBlock();

	fixBlock();

	removeLine();
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
			blockSet();

			runAlgorithm = true; // AI 알고리즘 다시 작동
			turnComplete = false; // 테트로미노 회전 완료 상태를 false로 전환
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



// AI
void CPU::AIAlgorithm()
{
	// 이동할 좌표를 정했으면 테트로미노가 저장될 때까지 알고리즘 사용중지
	if (runAlgorithm == true)
	{
		// 모든 회전상태 확인
		for (tetroRotationNum = 0; tetroRotationNum < 4; tetroRotationNum++) 
		{
			TetroPosCheck();

			CreateTetroContainer();

			LeftmostPosXThatTetroCanMove();

			RightmostPosXThatTetroCanMove();

			TetroMoveToBottom();

			// O 테트로미노는 회전해도 모양이 모두 똑같음으로 한 번만 확인 후 break
			if (blockForm == 1)
			{
				break;
			}
			// I, S, Z 테트로미노는 회전상태를 2번만 확인하면 나머지는 똑같은 모양이 나오기 때문에 tetroRotationNum이 1이 될 때까지만 확인하고 break
			else if ((blockForm == 0 || blockForm == 3 || blockForm == 4) && tetroRotationNum == 1)
			{
				break;
			}
		}

		SearchSmallestBlankNum();

		SelectMovePos();

		runAlgorithm = false; // 테트로미노를 이동시킬 위치를 찾았으면 알고리즘 작동정지
	}
}

void CPU::TetroPosCheck()
{
	// I 테트로미노 회전상태가 1, 3일 때 (4, 0)좌표에서 생성되면 천장에 겹치므로 tetroCreatePosY 값을 +1
	if (blockForm == 0 && (tetroRotationNum == 1 || tetroRotationNum == 3))
	{
		tetroCreatePosY++;
	}
	// J 테트로미노 회전상태가 3일 때 (4, 0)좌표에서 생성되면 천장에 겹치므로 tetroCreatePosY 값을 +1
	else if (blockForm == 5 && tetroRotationNum == 3)
	{
		tetroCreatePosY++;
	}
	// L 테트로미노 회전상태가 1일 때 (4, 0)좌표에서 생성되면 천장에 겹치므로 tetroCreatePosY 값을 +1
	else if (blockForm == 6 && tetroRotationNum == 1)
	{
		tetroCreatePosY++;
	}

	// tetroPos벡터에 테트로미노의 모든 칸의 좌표를 저장
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

void CPU::CreateTetroContainer()
{
	// 테트로미노를 담을 벡터 크기 계산
	int startPosX = tetroPos[0][0];
	int endPosX = tetroPos[0][0];
	int startPosY = tetroPos[0][1];
	int endPosY = tetroPos[0][1];

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

	// 테트로미노를 담을 벡터 생성
	int tetroSize_X = (endPosX - startPosX) + 1;
	int tetroSize_Y = (endPosY - startPosY) + 1;

	for (int vectorCreatePosY = 0; vectorCreatePosY < tetroSize_Y + 1; vectorCreatePosY++) // 테트로미노의 한 칸 밑까지 빈공간을 확인하기 위해서 Y좌표는 +1
	{
		std::vector<int> inputValue;

		for (int vectorCreatePosX = 0; vectorCreatePosX < tetroSize_X + 2; vectorCreatePosX++) // 테트로미노의 왼쪽, 오른쪽 한 칸씩 빈공간을 더 확인하기 위해서 X좌표에 +2
		{
			inputValue.push_back(0);
		}
		tetroContainer.push_back(inputValue);
	}

	// 테트로미노를 담을 벡터 안에 테트로미노 저장
	for (int vectorNum = 0; vectorNum < tetroPos.size(); vectorNum++)
	{
		int tetroPosX = (tetroPos[vectorNum][0] + 1) - startPosX; // tetroContainer벡터 가운데에 테트로미노를 저장하기 위해 테트로미노 X좌표에 +1
		int tetroPosY = tetroPos[vectorNum][1] - startPosY;

		tetroContainer[tetroPosY][tetroPosX] = 1;
	}
}

void CPU::LeftmostPosXThatTetroCanMove()
{
	int moveLeft = 0; // 테트로미노가 왼쪽으로 움직인 횟수

	while (checkWall != true)
	{
		// 테트로미노가 생성되는 위치에 벽이 있는지 확인
		for (int tetroFrameY = 0; tetroFrameY < 4; tetroFrameY++)
		{
			for (int tetroFrameX = 0; tetroFrameX < 4; tetroFrameX++)
			{
				if (block[blockForm][tetroRotationNum][tetroFrameY][tetroFrameX] == 1)
				{
					int mapPosX = (tetroCreatePosX - moveLeft) + tetroFrameX;
					int mapPosY = tetroCreatePosY + tetroFrameY;

					if (map[mapPosY][mapPosX] == 1)
					{
						checkWall = true;
					}
				}
			}
		}

		// 테트로미노가 벽에 겹치지 않았을 경우 생성되는 위치를 왼쪽으로 한 칸 이동
		if (checkWall == false)
		{
			moveLeft++;
		}
		// 테트로미노가 벽에 겹쳤을 경우 생성되는 위치를 오른쪽으로 한 칸 이동 후 X좌표를 tetroLeftmostPosX에 저장
		else
		{
			moveLeft--;
			tetroLeftmostPosX = tetroCreatePosX - moveLeft;
		}
	}
	checkWall = false;
}

void CPU::RightmostPosXThatTetroCanMove()
{
	int moveRight = 0; // 테트로미노가 오른쪽으로 움직인 횟수

	while (checkWall != true)
	{
		// 테트로미노가 생성되는 위치에 벽이 있는지 확인
		for (int tetroFrameY = 0; tetroFrameY < 4; tetroFrameY++)
		{
			for (int tetroFrameX = 0; tetroFrameX < 4; tetroFrameX++)
			{
				if (block[blockForm][tetroRotationNum][tetroFrameY][tetroFrameX] == 1)
				{
					int mapPosX = (tetroCreatePosX + moveRight) + tetroFrameX;
					int mapPosY = tetroCreatePosY + tetroFrameY;

					if (map[mapPosY][mapPosX] == 1)
					{
						checkWall = true;
					}
				}
			}
		}

		// 테트로미노가 벽에 겹치지 않았을 경우 생성되는 위치를 오른쪽으로 한 칸 이동
		if (checkWall == false)
		{
			moveRight++;
		}
		// 테트로미노가 벽에 겹쳤을 경우 생성되는 위치를 왼쪽으로 한 칸 이동 후 X좌표를 tetroRightmostPosX에 저장
		else
		{
			moveRight--;
			tetroRightmostPosX = tetroCreatePosX + moveRight;
		}
	}
	checkWall = false;
}

void CPU::TetroMoveToBottom()
{
	int tetroContainerCreatePosX = 0; // map벡터를 기준 tetroContainer벡터가 생성되는 X좌표
	int tetroContainerCreatePosY = 1; // map벡터를 기준 tetroContainer벡터가 생성되는 Y좌표

	// 테트로미노가 생성될 수 있는 모든 X 좌표를 확인할 때까지 반복
	while (tetroLeftmostPosX < tetroRightmostPosX + 1)
	{
		// 테트로미노와 바닥이 겹쳤는지 확인
		for (int vectorSearchingPosY = 0; vectorSearchingPosY < tetroContainer.size(); vectorSearchingPosY++)
		{
			for (int vectorSearchingPosX = 0; vectorSearchingPosX < tetroContainer[0].size(); vectorSearchingPosX++)
			{
				int mapPosX = tetroContainerCreatePosX + vectorSearchingPosX;
				int mapPosY = tetroContainerCreatePosY + vectorSearchingPosY;

				if (tetroContainer[vectorSearchingPosY][vectorSearchingPosX] == 1 && (map[mapPosY][mapPosX] == 1 || map[mapPosY][mapPosX] == 2))
				{
					checkWall = true;
				}
			}
		}

		// 테트로미노가 바닥과 겹치치 않았으면 아래로 한 칸 이동
		if (checkWall == false)
		{
			tetroContainerCreatePosY++;
		}
		// 테트로미노가 바닥과 겹쳤으면 위로 한 칸 이동 후 빈칸 확인
		else
		{
			tetroContainerCreatePosY--;
			
			CheckBlank(tetroContainerCreatePosX, tetroContainerCreatePosY);

			tetroContainerCreatePosX++;
			tetroContainerCreatePosY = 1;
			tetroLeftmostPosX++;
			checkWall = false;
		}
	}

	tetroPos.clear();
	tetroContainer.clear();
	tetroCreatePosY = 0;
}

void CPU::CheckBlank(int posX, int posY)
{
	spaceStateContainer = tetroContainer; // spaceStateContainer벡터에 tetroContainer벡터를 삽입

	// 테트로미노 주변에 채워진 공간 확인
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			int mapPosX = posX + vectorSearchingPosX;
			int mapPosY = posY + vectorSearchingPosY;

			if (map[mapPosY][mapPosX] == 1 || map[mapPosY][mapPosX] == 2)
			{
				spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] = 1;
			}
		}
	}

	// 테트로미노 모양 별로 빈칸 확인
	switch (blockForm)
	{
	case 0:
	case 1:
		IAndOTetroBlank();
		break;
	case 2:
		TTetroBlank();
		break;
	case 3:
		STetroBlank();
		break;
	case 4:
		ZTetroBlank();
		break;
	case 5:
		JTetroBlank();
		break;
	case 6:
		LTetroBlank();
		break;
	}

	// 빈칸 정보 저장
	std::vector<int> inputValue;
	inputValue.push_back(tetroRotationNum); // 테트로미노 회전상태
	inputValue.push_back(tetroLeftmostPosX); // 테트로미노를 배치할 X좌표
	inputValue.push_back(posY); // 테트로미노가 배치되었을 때 Y좌표
	inputValue.push_back(blankCount); // 빈칸 개수
	deploymentInfo.push_back(inputValue);

	// 초기화
	spaceStateContainer.clear();
	blankCount = 0;
}

void CPU::IAndOTetroBlank()
{
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0)
			{
				if (vectorSearchingPosY == (spaceStateContainer.size() - 1) && (vectorSearchingPosX == 0 || vectorSearchingPosX == spaceStateContainer[0].size() - 1))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == (spaceStateContainer.size() - 1) && (vectorSearchingPosX > 0 && vectorSearchingPosX < spaceStateContainer[0].size() - 1))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
		}
	}
}

void CPU::TTetroBlank()
{
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 0)
			{
				if (vectorSearchingPosY == 0 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX > 0 && vectorSearchingPosX < 4))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 1)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 3)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 3)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 2)
			{
				if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 3))
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 3)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
		}
	}
}

void CPU::STetroBlank()
{
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 0)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 4)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 3)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 3 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 1)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 3)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
		}
	}
}

void CPU::ZTetroBlank()
{
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 0)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 4)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 2 || vectorSearchingPosX == 3))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 1)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 3)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
		}
	}
}

void CPU::JTetroBlank()
{
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 0)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 4)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX > 0 && vectorSearchingPosX < 4))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 1)
			{
				if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 3)
				{
					blankCount += 0;
				}
				else if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 2)
			{
				if (vectorSearchingPosY == 1 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2))
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 2 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 3)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 3)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
		}
	}
}

void CPU::LTetroBlank()
{
	for (int vectorSearchingPosY = 0; vectorSearchingPosY < spaceStateContainer.size(); vectorSearchingPosY++)
	{
		for (int vectorSearchingPosX = 0; vectorSearchingPosX < spaceStateContainer[0].size(); vectorSearchingPosX++)
		{
			if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 0)
			{
				if (vectorSearchingPosY == 0 && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX > 0 && vectorSearchingPosX < 4))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 1)
			{
				if ((vectorSearchingPosY == 0 || vectorSearchingPosY == 1) && vectorSearchingPosX == 3)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 1 || vectorSearchingPosX == 2))
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 2)
			{
				if (vectorSearchingPosY == 1 && vectorSearchingPosX == 4)
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 1 && (vectorSearchingPosX == 2 || vectorSearchingPosX == 3))
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 2 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 2 || vectorSearchingPosX == 3 || vectorSearchingPosX == 4))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 2 && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
			else if (spaceStateContainer[vectorSearchingPosY][vectorSearchingPosX] == 0 && tetroRotationNum == 3)
			{
				if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 0)
				{
					blankCount += 0;
				}
				else if ((vectorSearchingPosY == 1 || vectorSearchingPosY == 2) && vectorSearchingPosX == 1)
				{
					blankCount += 7;
				}
				else if (vectorSearchingPosY == 3 && (vectorSearchingPosX == 0 || vectorSearchingPosX == 1 || vectorSearchingPosX == 3))
				{
					blankCount += 0;
				}
				else if (vectorSearchingPosY == 3 && vectorSearchingPosX == 2)
				{
					blankCount += 7;
				}
				else
				{
					blankCount++;
				}
			}
		}
	}
}

void CPU::SearchSmallestBlankNum()
{
	// 가장 적은 빈칸 개수 탐색
	int smallestWeightNum = deploymentInfo[0][3];

	for (int vectorNum = 1; vectorNum < deploymentInfo.size(); vectorNum++)
	{
		if (smallestWeightNum > deploymentInfo[vectorNum][3])
		{
			smallestWeightNum = deploymentInfo[vectorNum][3];
		}
	}

	// 가장 적은 빈칸 개수 정보를 가지고 있는 부분만 따로 저장
	for (int vectorNum = 0; vectorNum < deploymentInfo.size(); vectorNum++)
	{
		std::vector<int> inputValue;

		if (smallestWeightNum == deploymentInfo[vectorNum][3])
		{
			inputValue.push_back(deploymentInfo[vectorNum][0]);
			inputValue.push_back(deploymentInfo[vectorNum][1]);
			inputValue.push_back(deploymentInfo[vectorNum][2]);
			smallestBlank.push_back(inputValue);
		}
	}
}

void CPU::SelectMovePos()
{
	// 테트로미노가 배치될 가장 낮은 자리 탐색
	int biggestPosYNum = smallestBlank[0][2];

	for (int i = 1; i < smallestBlank.size(); i++)
	{
		if (biggestPosYNum < smallestBlank[i][2])
		{
			biggestPosYNum = smallestBlank[i][2];
		}
	}

	// 가장 낮은 자리 정보를 가지고 있는 부분만 따로 저장
	std::vector<std::vector<int>> biggestPosY;

	for (int i = 0; i < smallestBlank.size(); i++)
	{
		std::vector<int> inputValue;

		if (biggestPosYNum == smallestBlank[i][2])
		{
			inputValue.push_back(smallestBlank[i][0]);
			inputValue.push_back(smallestBlank[i][1]);
			biggestPosY.push_back(inputValue);
		}
	}

	// 회전상태 및 이동시킬 X좌표 선택
	int randValue = rand() % biggestPosY.size();

	selectedRotationNum = biggestPosY[randValue][0];
	selectedMovePosX = biggestPosY[randValue][1];
	biggestPosY.clear();

	deploymentInfo.clear();
	smallestBlank.clear();
}

void CPU::MoveToSelectPos()
{
	endTime = clock();

	if ((float)(endTime - startMoveTime) >= 200.0f) 
	{
		// 회전
		if (turnComplete != true)
		{
			if (selectedRotationNum != blockRotation)
			{
				moveBlockRotate();
			}
			else
			{
				turnComplete = true;
			}
		}
		// 회전을 완료했으면 이동
		else if (turnComplete == true)
		{
			if (selectedMovePosX > x)
			{
				moveBlockRight();
			}
			else if (selectedMovePosX < x)
			{
				moveBlockLeft();
			}
			// 회전 및 이동 모두 완료시 하드드롭
			else
			{
				moveBlockHardDrop();
			}
		}

		startMoveTime = clock();
	}
}
