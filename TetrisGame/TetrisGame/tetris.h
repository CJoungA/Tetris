#ifndef TETRIS_H_
#define TETRIS_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include <vector>

using std::cout;
using std::cin;
#endif

int selectOption(); // 옵션 선택

void setCursor();	//커서 숨기기
void gotoxy(int x, int y);	//커서이동

void shuffle(int* arr);	//배열 무작위 정렬

class Tetris {
public:
	void blockSet();	//블럭 정보초기화 및 겹치지 않도록 블록 종류선택

	void getGameSpeed();	//게임 속도 입력

	bool checkMoveCrash(int x, int y, int blockForm, int blockRotation);	//충돌감지
	void dropBlock();	//1초마다 한칸식 내려옴
	void fixBlock();	//블록이 땅에 닿았을 때 고정

	void setScore();	//점수계산
	void removeLine();	//라인지우기

	void keyInputEvent();	//키보드 이벤트

	void setBlockRotate(); //블록 rotate설정

	void moveBlockRotate();	//키입력 및 블럭이동
	void moveBlockLeft();	//왼쪽
	void moveBlockRight();	//오른쪽
	void moveBlockSoftDrop();	//소프트 드랍
	void moveBlockHardDrop();	//하드 드랍

	void pauseGame();	//게임 일시정지

	void drawCeiling(); //천장그리기
	void drawMap();		//맵그리기
	void drawBlock();	//블록그리기
	void deleteBlock(); //블록지우기
	void drawInformation();	//조작키 정보그리기
	void showScore();	//점수보기

	void gameOver();	//게임 오버

	void update();	//게임 업데이트
	void render();	//게임 렌더링

protected:
	int x = 4, y = 0;	//블록 위치

	int blockForm = 0;	//블록 형태 0~6
	int blockRotation = 0;	//블록 회전 0~3
	int blockArray[7] = { 0,1,2,3,4,5,6 };	//블록 형태 배열에 저장
	int arrayIndex = 0;	//배열 인덱스

	int count = 0;	//고정된 블록 카운트 
	int score = 0;	//점수
	int speed = 0;	//게임 속도

	int map[22][12]{	//맵
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

	int map_cpy[22][12]{	//변경되기 전을 저장하는 맵_복사본
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

	//시간정보
	clock_t startDropTime = 0;
	clock_t endTime = 0; 
	clock_t startGroundTime = 0;	

};

class CPU : public Tetris
{
public:
	// 생성자 & 소멸자
	CPU();
	~CPU();

	// 오버라이딩 & 게임 루프
	void keyInputEvent();
	void update();
	void render();

	// 오버라이딩
	void drawInformation();
	void fixBlock();
	void removeLine();

	// 게임 종료
	void gameExit();

	// AI
	void AI_Pipeline(); // AI 파이프라인
	void CreateBlankCheckBlock(); // 빈 칸 확인용 블록 생성
	void MoveBlankCheckBlock(); // 빈 칸 확인용 블록을 검사할 위치로 이동
	void UpdateBlockOverlapPart(int posX, int posY); // 빈 칸 확인용 블록 중 벽 또는 저장된 블록과 겹친 부분의 값을 1로 변경

	int GetBlankCount(); // 빈 칸 확인용 블록 안의 빈 칸의 개수 가져오기
	int CurrentBlock_IorO(int count); // 현재 블록이 I 또는 O 일때 빈 칸 개수 확인
	int CurrentBlock_T(int count); // 현재 블록이 T 일때 빈 칸 개수 확인
	int CurrentBlock_S(int count); // 현재 블록이 S 일때 빈 칸 개수 확인
	int CurrentBlock_Z(int count); // 현재 블록이 Z 일때 빈 칸 개수 확인
	int CurrentBlock_J(int count); // 현재 블록이 J 일때 빈 칸 개수 확인
	int CurrentBlock_L(int count); // 현재 블록이 L 일때 빈 칸 개수 확인

	void SelectBlockMovePos(); // 블록을 이동시킬 좌표 선택

	void MoveToSelectPos(); // 선택한 위치로 블록을 이동

private:
	std::vector<std::vector<int>> blockPosInfo; // 블록의 모든 칸의 좌표 정보를 담는 벡터
	std::vector<std::vector<int>> blankCheckBlock; // 빈 칸 확인용 블록
	std::vector<std::vector<int>> blankCheckBlock_cpy; // 공간상태를 저장하는 벡터
	std::vector<std::vector<int>> blockPlacementInfo; // 블록이 배치되었을 때의 정보를 담는 벡터

	int blockLeftmostPosX; // 블록이 생성될 수 있는 가장 왼쪽 X 좌표
	int blockRightmostPosX; // 블록이 생성될 수 있는 가장 오른쪽 X 좌표
	int selectedRotationNum; // 선택된 회전 상태
	int selectedMovePosX; // 선택된 배치할 X 좌표

	clock_t startMoveTime; // 0.2초가 지났는지 확인하는 변수

	bool isRun;  // 실행 여부 확인
	bool checkWall; // 벽 확인
	bool turnComplete; // 회전완료 여부
};