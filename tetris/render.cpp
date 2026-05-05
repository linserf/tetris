#include "Board.h"
#include"Tetromino.h"
void render(Board& b, Tetromino& t){//Ë¢ÐÂ»­Ãæ
	b.InitMap();
	t.cast();
	b.Draw();
}