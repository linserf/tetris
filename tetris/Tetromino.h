#pragma once
#include <vector>
enum TetrominoType { I, J, L, O, S, T, Z };
class Tetromino {
public:
	int x, y;
	TetrominoType type;
	int shape[4][4];
	struct Coord { int x, y; };
	std::vector<Coord> relativeCoords; // 存储相对于中心的坐标
	bool InitTetromino(TetrominoType type);
	void rotate();
	void move(int dx, int dy);
	void moveto(int tx, int ty);
	void cast();
	bool isValid();
	void nextcast();
	void InitnextTetromino(TetrominoType type);
}; 