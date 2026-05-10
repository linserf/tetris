#pragma once
#include "Board.h"
#include "Tetromino.h"
#include<vector>
inline int score = 0;
inline int combo = 0;
inline bool isGameOver = false;
class GameController {
public:
	std::vector<TetrominoType> tetrominosList = { TetrominoType::I, TetrominoType::J, TetrominoType::L, TetrominoType::O, TetrominoType::S, TetrominoType::T, TetrominoType::Z };
	std::vector<TetrominoType>::iterator currentTetrominoType;
	Board board;
	Tetromino currentTetromino;
	Tetromino nextTetromino;
	void InitGame();
	bool Spawn();
	void Drop();
	bool Fixed();
	void KeyboardControl();
	int  GetInput();
	bool isClearLine(int y);
	bool ClearLine();
	void initlist();
	void nextcast();
};