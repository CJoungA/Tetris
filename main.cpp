#include "tetris.h"

int main() {
	struct BlockData b;	//블럭 정보 구조체
	b.blockForm = randomCreateBlock();	//블록 정하기

	struct CTime ctime;	//시간 정보 구조체
	ctime.startDropTime = clock();

	int score = 0;

	setCursor();	//커서숨기기

	int speed = 0;
	cout << "속도입력: ";
	cin >> speed;

	drawInformation();	//조작키 정보그리기

	while (true) {

		keyInputEvent(b, ctime);	//키이벤트

		dropBlock(b, ctime, speed);	//업데이트
		fixBlock(b, ctime);
		removeLine(score);

		drawMap();					//렌더링
		drawBlock(b);

		gameExit();					//루프 종료
	}

	return 0;
}