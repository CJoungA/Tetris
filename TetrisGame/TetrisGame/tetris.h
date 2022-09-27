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

	clock_t startDropTime, endTime, startGroundTime;	//시간정보

};

class CPU : public Tetris
{
public:
	CPU();
	~CPU();

	void keyInputEvent();
	void update();
	void render();

	void drawInformation();
	void fixBlock();
	void gameExit();

	void TetrisAIAlgorithm(); // 테트리스 AI 알고리즘
	void TetroPosCheck(); // 테트로미노의 모든 좌표 확인
	void CreateSpaceStateVector(); // 공간 상태를 저장하는 벡터 생성
	void LeftmostPosXThatTetroCanMove(); // 테트로미노가 움직일 수 있는 가장 왼쪽 X 좌표
	void RightmostPosXThatTetroCanMove(); // 테트로미노가 움직일 수 있는 가장 오른쪽 X 좌표
	void TetroMoveToBottom(); // 움직일 수 있는 모든 X 좌표에서 바닥으로 이동
	void CheckWeightLogic(int posX, int posY); // 가중치를 확인하기 위한 로직

	void SearchSmallestWeight(); // 가중치가 가장 적은 벡터를 찾는 로직
	void SearchMovePos(); // 테트로미노를 움직일 위치를 선택하는 로직

	void MoveToSelectPos(); // 선택한 위치로 테트로미노를 이동


private:
	std::vector<std::vector<int>> tetroPos; // 테트로미노의 모든 칸의 위치가 저장되는 벡터
	std::vector<std::vector<int>> tetro; // 테트로미노가 저장되어 있는 벡터
	std::vector<std::vector<int>> spaceState; // 공간이 차있는지 비었는지 저장하는 벡터
	std::vector<std::vector<int>> weightInfo; // 가중치 정보를 저장하는 벡터
	std::vector<std::vector<int>> smallestWeight; // 가중치가 가장 적은 정보만 저장하는 벡터

	int tetroRotationNum; // 알고리즘을 위한 테트리스 회전 번호
	int tetroCreatePosX; // 알고리즘을 위한 테트로미노가 생성되는 위치의 X 좌표
	int tetroCreatePosY; // 알고리즘을 위한 테트로미노가 생성되는 위치의 Y 좌표

	int tetroLeftmostPosX; // 테트로미노가 움직일 수 있는 가장 왼쪽 X 좌표
	int tetroRightmostPosX; // 테트로미노가 움직일 수 있는 가장 오른쪽 X 좌표

	int weight; // 가중치

	int selectedRotationNum;
	int selectedMovePosX;

	bool searchComplete;
	bool checkWall; // 벽을 확인하는 변수
};