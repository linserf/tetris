#include "Board.h"
#include"Tetromino.h"
void render(Board& b, Tetromino& t,Tetromino & nt,bool color){//Ë¢ÐÂ»­Ãæ
	b.InitMap();
	t.cast();
	nt.nextcast();
	b.Draw(color);
}