#pragma once
inline constexpr int WIDTH=17;
inline constexpr int HEIGHT=22;
inline int map[WIDTH][HEIGHT] = { 0 };
class Board {
public:
	void Draw();
	void InitMap();
	void SetPos(int x, int y);
	void HideCursor();
};