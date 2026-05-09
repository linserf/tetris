#pragma once
#include "Board.h"
#include "Tetromino.h"
inline int score = 0;
inline int combo = 0;
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