#pragma once
inline constexpr int WIDTH=17;
inline constexpr int AWIDTH = 32;
inline constexpr int HEIGHT=22;
inline int map[AWIDTH][HEIGHT] = { 0 };
class Board {
public:
	void Draw(bool color);
	void InitMap();
	void SetPos(int x, int y);
	void HideCursor();
};