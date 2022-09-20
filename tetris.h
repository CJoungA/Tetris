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

using std::cout;
using std::cin;

struct BlockData {	//블록정보 구조체
	int x = 4, y = 0;
	int blockForm = 0;
	int blockRotation = 0;
	int blockArray[7] = { 0,1,2,3,4,5,6 };
	int arrayIndex = 0;
};

struct CTime {	//시간정보 구조체
	clock_t startDropTime, endTime, startGroundTime;
};

void setCursor();	//커서 숨기기
void gotoxy(int x, int y);	//커서이동

void shuffle(int* arr);	//배열 무작위 정렬

void blockSet(struct BlockData& b);	//블럭 정보초기화 및 겹치지 않도록 블록 종류선택
bool checkMoveCrash(int x, int y, int blockForm, int blockRotation);	//충돌감지
void dropBlock(struct BlockData& b, struct CTime& ctime, int speed);	//1초마다 한칸식 내려옴
void fixBlock(struct BlockData& b, struct CTime& ctime);	//블록이 땅에 닿았을 때 고정

int gameScore(int count);	//점수계산
void removeLine(int& score);	//라인지우기
void keyInputEvent(struct BlockData& b, struct CTime& ctime);	//키입력 및 블럭이동
void pauseGame();	//게임 일시정지

void drawMap();		//맵그리기
void drawBlock(struct BlockData b);	//블록그리기
void deleteBlock(struct BlockData b); //블록지우기
void drawInformation();	//조작키 정보그리기

void gameExit();	//게임 오버
#endif