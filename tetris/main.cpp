#include"Board.h"
#include"Tetromino.h"
#include"render.h"
#include"GameController.h"
#include<Windows.h>
const int TARGET_FPS = 60;//游戏帧率
const int FRAME_DELAY = 1000 / TARGET_FPS;
float DROP_INTERVAL = 0.5f;//下落速度
int main() {
    bool running = true;
    bool isfixed = false;
    unsigned long lastTime = GetTickCount();
    float timeAccumulated = 0.0f;//计时器初始化
	GameController c;
	c.InitGame();//初始化游戏
    c.Spawn();//生成开始时的Tetromino
    while (running) {
        unsigned long currentTime = GetTickCount();
        float dt = (currentTime - lastTime) / 1000.0f;//计算时间间隔
        lastTime = currentTime;
        if (isfixed) {//如果前一Tetromino被fixed，生成新的Tetromino
            c.Spawn();
            isfixed = false;
        }
        c.KeyboardControl(); //接受键盘输入
        timeAccumulated += dt;
        while (timeAccumulated >= DROP_INTERVAL) {//如果计时器大于下落的间隔，执行下落并判断是否fixed
            if (!c.Fixed()) {
                c.Drop();
                timeAccumulated -= DROP_INTERVAL;//减去执行时间
                break;
            }
            isfixed = true;
            timeAccumulated -= DROP_INTERVAL;//减去执行时间
        }
        if (c.ClearLine()) {//消除行
            timeAccumulated -= 1;
        }
        if (dt * 1000 < FRAME_DELAY) {//保护cpu
            Sleep(FRAME_DELAY - (unsigned long)(dt * 1000));
        }
    }
	
}