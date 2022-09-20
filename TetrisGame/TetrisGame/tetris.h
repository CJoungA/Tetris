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

using namespace std;

struct BlockData {	//������� ����ü
	int x = 4, y = 0;
	int blockForm = 0;
	int blockRotation = 0;
};

struct CTime {	//�ð����� ����ü
	clock_t startDropTime, endTime, startGroundTime;
};

void setCursor();	//Ŀ�� �����
void gotoxy(int x, int y);	//Ŀ���̵�

int randomCreateBlock();	//����������
bool checkMoveCrash(int x, int y, int blockForm, int blockRotation);	//�浹����
void dropBlock(struct BlockData& b, struct CTime& ctime, int speed);	//1�ʸ��� ��ĭ�� ������
void fixBlock(struct BlockData& b, struct CTime& ctime);	//���� ���� ����� �� ����

int gameScore(int count);	//�������
void removeLine(int& score);	//���������
void keyInputEvent(struct BlockData& b, struct CTime& ctime);	//Ű�Է� �� ���̵�
void pauseGame();	//���� �Ͻ�����

void drawMap();		//�ʱ׸���
void drawBlock(struct BlockData b);	//���׸���
void deleteBlock(struct BlockData b); //�������
void drawInformation();

void gameExit();
#endif