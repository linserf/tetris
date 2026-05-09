#include"Board.h"
#include"Tetromino.h"
#include"GameController.h"
#include"render.h"
#include<vector>
#include<conio.h>
#include<Windows.h>
#include<random>
void GameController::InitGame() {//初始化游戏（初始化map，隐藏光标，绘制map）
	board.InitMap();
	board.HideCursor();
	board.Draw(true);
}


void GameController::Spawn() {//生成新的Tetromino，并移动至地图上方
	std::vector<TetrominoType> tetrominosList = { TetrominoType::I, TetrominoType::J, TetrominoType::L, TetrominoType::O, TetrominoType::S, TetrominoType::T, TetrominoType::Z };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 100); 
	int random_num = distrib(gen);
    int randomIndex = random_num % tetrominosList.size();
	currentTetromino.InitTetromino(tetrominosList[randomIndex]);
	currentTetromino.moveto(6,1);
	render(board,currentTetromino,true);

}
void GameController::Drop() {//Tetromino下落
	currentTetromino.move(0, 1);
	if (!currentTetromino.isValid()) {
		currentTetromino.move(0, -1);
	}
	render(board, currentTetromino,true);
}
bool GameController::Fixed() {//Tetromino落到最低端或是接触到以fixed的Tetromino时在map上绘制信息
	bool isbottom=false;
	bool isfixed = false;
	for (const auto& block : currentTetromino.relativeCoords) {
		int nextX = currentTetromino.x + block.x;
		int nextY = currentTetromino.y + block.y;
		if (nextY >= 0 && (map[nextX][nextY+1] ==4||map[nextX][nextY+1] == -1)) {
			isbottom = true;
			break;
		}
		isbottom = false;
	}
	if (isbottom) {
		for (const auto& block : currentTetromino.relativeCoords) {
			int nextX = currentTetromino.x + block.x;
			int nextY = currentTetromino.y + block.y;
			map[nextX][nextY] = -1;//已fixed的tetromino为-1
		}
		isfixed = true;
	}
	return isfixed;
}
int GameController::GetInput() {//获取输入的函数，用于KeyboardControl
	if (_kbhit()) {
		return _getch();
	}
	return 0;
}
void GameController::KeyboardControl() {//获取键盘输入，进行相应的操作
	int key = GetInput(); // 非阻塞获取

	if (key != 0) {
		switch (key) {
		case 'a': // 左移
			currentTetromino.move(-1, 0);
			break;
		case 'd': // 右移
			currentTetromino.move(1, 0);
			break;
		case 'w': // 旋转
			currentTetromino.rotate();
			break;
		case 's': // 加速下落
			currentTetromino.move(0, 1);
			break;
		}
	}

}
bool GameController::isClearLine(int y) {//判断是否有可以消除的行
	for (int x = 1; x < WIDTH-1; x++) {
		if (map[x][y] != -1) {
			return false;
		}
	}
	return true;
}
bool GameController::ClearLine() {//消除行
  // Determine all clearable rows (playable rows: 1 .. HEIGHT-2)
	std::vector<bool> clearRow(HEIGHT, false);
	int clearCount = 0;
	for (int y = HEIGHT - 2; y > 0; y--) {
		if (isClearLine(y)) {
			clearRow[y] = true;
			clearCount++;
		}
	}
	combo = clearCount;
	switch (combo) {
	case 1: score += 100; break;
	case 2: score += 300; break;
	case 3: score += 500; break;
	case 4: score += 800; break;
	}
	if (clearCount == 0) return false;

	// Blink effect for cleared lines
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 2; i++) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		render(board, currentTetromino,false);
		Sleep(200);
		SetConsoleTextAttribute(hConsole, 7);
		render(board, currentTetromino,false);
		Sleep(200);
	}


	// Build new column data for playable columns only, pushing non-cleared rows down
	for (int x = 1; x < WIDTH-1; x++) {
		int writeY = HEIGHT - 2; // start from bottom playable row
		for (int y = HEIGHT - 2; y > 0; y--) {
			if (!clearRow[y]) {
				map[x][writeY] = map[x][y];
				writeY--;
			}
		}
		// fill remaining rows at top with empty
		for (int y = writeY; y > 0; y--) {
			map[x][y] = 0;
		}
	}
	return true;
}
