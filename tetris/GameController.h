#pragma once
class GameController {
public:
	Board board;
	Tetromino currentTetromino;
	void InitGame();
	void Spawn();
	void Drop();
	bool Fixed();
	void KeyboardControl();
	int  GetInput();
	bool isClearLine(int y);
	bool ClearLine();
};