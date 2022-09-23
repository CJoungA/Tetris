#include "Tetris.h"

int main() {
	Tetris tetris;

	setCursor();	//커서숨기기

	tetris.getGameSpeed();	//속도 입력 받기

	tetris.drawInformation();	//조작키 정보그리기

	while (true) {

		tetris.keyInputEvent();	//키이벤트

		tetris.update();	//업데이트	

		tetris.render();	//렌더링

		tetris.gameOver();	//루프종료
	}
	// 바보 바보
	// 바보 바보
	return 0;
}