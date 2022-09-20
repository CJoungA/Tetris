
#include "tetris.h"

int main() {
	struct BlockData b;	//�� ���� ����ü
	b.blockForm = randomCreateBlock();	//��� ���ϱ�

	struct CTime ctime;	//�ð� ���� ����ü
	ctime.startDropTime = clock();

	setCursor();	//Ŀ�������

	int score = 0;

	int speed = 0;
	cout << "�ӵ��Է�: ";
	cin >> speed;

	drawInformation();

	while (true) {

		keyInputEvent(b, ctime);//Ű�̺�Ʈ

		dropBlock(b, ctime, speed);//������Ʈ
		fixBlock(b, ctime);
		removeLine(score);

		drawMap();//������
		drawBlock(b);

		gameExit();//���� ����
	}

	return 0;
}