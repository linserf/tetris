#include "Board.h"
#include"Tetromino.h"
void render(Board& b, Tetromino& t,bool color){//Ë¢ÐÂ»­Ãæ
	b.InitMap();
	t.cast();
	b.Draw(color);
}