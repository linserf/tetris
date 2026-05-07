#include<iostream>
#include<Windows.h>
#include<vector>
#include"Board.h"

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
}
void Board::Draw() {// 绘制函数
    // 1. 先把光标移到屏幕左上角 (0,0)，准备覆盖旧画面
    SetPos(0, 0);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            switch (map[x][y]) {
            case 0: 
                SetConsoleTextAttribute(hConsole, 8);
                std::cout <<"□"; 
                SetConsoleTextAttribute(hConsole, 7);
                break; // 空白
            case 1: case -1:std::cout << "■"; break; // 方块
            case 2:std::cout << "─"; break; // 下边界
            case 3: std::cout << "│"; break; // 左边界
            case 4: std::cout << "─"; break; // 上边界
            case 5: std::cout << "│\n"; break; // 右边界
            case 6: std::cout << "┌"; break; // 左上角
            case 7: std::cout << "┘\n"; break; // 右下角
            case 8: std::cout << "┐\n"; break; // 右上角
            case 9: std::cout << "└"; break; // 左下角
            }
        }
    }
    std::cout.flush(); // 确保立即输出
}