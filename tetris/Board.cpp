#include<iostream>
#include<Windows.h>
#include<vector>
#include"Board.h"
#include"GameController.h"
#include<iomanip>

void Board::SetPos(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄
    COORD pos = { (SHORT)x, (SHORT)y };            // 定义坐标结构体
    SetConsoleCursorPosition(hOut, pos);           // 设置光标位置
}
void Board::HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE; // 设置为不可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void Board::InitMap() {//初始化地图
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < AWIDTH; x++) {
            if (map[x][y] != -1 && map[x][y] != -3 && map[x][y] != 14) {
                map[x][y] = -2;
            }
        }
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[x][y] != -1){
                map[x][y] = 0;
            }
        }
    }
    for (int x = 0; x < WIDTH; x++) {
        map[x][0] = 2;
    }//上边界
    for (int y = 0; y < HEIGHT; y++) {
        map[0][y] = 3;
    }//左边界
    for (int x = 0; x < WIDTH; x++) {
        map[x][HEIGHT - 1] = 4;
    }//下边界
    for (int y = 0; y < HEIGHT; y++) {
        map[WIDTH - 1][y] = 5;
    }//右边界
    map[0][HEIGHT - 1] = 9;
    map[WIDTH - 1][0] = 8;
    map[WIDTH - 1][HEIGHT - 1] = 7;
    map[0][0] = 6;
    //四角
    map[19][1] = 10;
    map[20][2] = 11;
	map[19][5] = 12;
	map[20][6] = 13;
	map[21][18] = 15;
    map[19][12] = 16;
    //输出菜单
}
void Board::Draw(bool color) {// 绘制函数
    // 1. 先把光标移到屏幕左上角 (0,0)，准备覆盖旧画面
    SetPos(0, 0);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < AWIDTH; x++) {
            switch (map[x][y]) {
            case -2: std::cout << " "; break; // 菜单区域
            case 0:
                if (color) {
                    SetConsoleTextAttribute(hConsole, 8);
                    std::cout << "□";
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else {
                    std::cout << "□";
                }
                break; // 空白
            case 1: case -1:case -3:std::cout << "■"; break; // 方块
            case 2:std::cout << "─"; break; // 下边界
            case 3: std::cout << "│"; break; // 左边界
            case 4: std::cout << "─"; break; // 上边界
            case 5: std::cout << "│"; break; // 右边界
            case 6: std::cout << "┌"; break; // 左上角
            case 7: std::cout << "┘"; break; // 右下角
            case 8: std::cout << "┐"; break; // 右上角
            case 9: std::cout << "└"; break; // 左下角
            case 10: std::cout << "linserf's:"; break;
            case 11: std::cout << "Tetris"; break;
            case 12: std::cout << "Score:"; break;
            case 13: std::cout << std::setfill('0') << std::setw(10) << score; break;
            case 14: std::cout << "Game Over"; break;
            case 16: std::cout << "next:"; break;
            case 15:
                switch (combo) {
				case 0: std::cout << ""; break;
                case 1: std::cout << "Single!"; break;
                case 2: std::cout << "Double!"; break;
                case 3: std::cout << "Triple!"; break;
                case 4: std::cout << "Tetris!"; break;
                }
            }
            if (x == 31) {
                std::cout << "\n";
            }
        }
    }
    std::cout.flush(); // 确保立即输出
}