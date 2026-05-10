#include "Tetromino.h"
#include "Board.h"
#include <utility>
#include"GameController.h"
const std::vector<std::pair<int, int>> KICK_TESTS = {
    {0, 0},   // 1. 原位尝试
    {1, 0},   // 2. 向右踢 1格
    {-1, 0},  // 3. 向左踢 1格
    {0, -1},  // 4. 向上踢 1格 (防止贴地旋转卡住)
    {2, 0},   // 5. 向右踢 2格 (针对长条I方块贴墙的情况)
    {-2, 0}   // 6. 向左踢 2格
};
bool Tetromino::InitTetromino(TetrominoType type) {//初始化Tetromino（根据输入的类型绘制）
    if (map[6][1] != 0) {
        isGameOver = true;
        return false; // 无法生成新方块，游戏结束
	}
    relativeCoords.clear();
    Tetromino::type = type;

    // 以方块自身的逻辑中心为 (0,0) 来定义相对坐标
    switch (type) {
    case TetrominoType::I:
        // I 形方块，中心在 (1.5, 1.5)，我们用整数坐标近似
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {2, 0} };
        break;
    case TetrominoType::O:
        // O 形方块，不需要旋转
        relativeCoords = { {0, 0}, {1, 0}, {0, 1}, {1, 1} };
        break;
    case TetrominoType::T:
        // T 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {0, 1} };
        break;
    case TetrominoType::L:
        // L 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {1, 1} };
        break;
    case TetrominoType::J:
        // J 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {-1, 1} };
        break;
    case TetrominoType::Z:
        // Z 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {0, 1}, {1, 1} };
        break;
    case TetrominoType::S:
        // S 形方块，中心在 (1, 1)
        relativeCoords = { {0, 0}, {1, 0}, {-1, 1}, {0, 1} };
        break;
    }
	return true;
}
void Tetromino::InitnextTetromino(TetrominoType type) {//初始化Tetromino（根据输入的类型绘制）
    relativeCoords.clear();
    Tetromino::type = type;

    // 以方块自身的逻辑中心为 (0,0) 来定义相对坐标
    switch (type) {
    case TetrominoType::I:
        // I 形方块，中心在 (1.5, 1.5)，我们用整数坐标近似
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {2, 0} };
        break;
    case TetrominoType::O:
        // O 形方块，不需要旋转
        relativeCoords = { {0, 0}, {1, 0}, {0, 1}, {1, 1} };
        break;
    case TetrominoType::T:
        // T 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {0, 1} };
        break;
    case TetrominoType::L:
        // L 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {1, 1} };
        break;
    case TetrominoType::J:
        // J 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {1, 0}, {-1, 1} };
        break;
    case TetrominoType::Z:
        // Z 形方块，中心在 (1, 1)
        relativeCoords = { {-1, 0}, {0, 0}, {0, 1}, {1, 1} };
        break;
    case TetrominoType::S:
        // S 形方块，中心在 (1, 1)
        relativeCoords = { {0, 0}, {1, 0}, {-1, 1}, {0, 1} };
        break;
    }
}
bool Tetromino::isValid() {//判断Tetromino目前的位置是否合法
    // 遍历当前方块的每一个小方块
    for (const auto& block : relativeCoords) {
        int nextX = x + block.x;
        int nextY = y + block.y;

        // 1. 边界检测 (是否撞墙)
        if (nextX < 0 || nextX >= WIDTH || nextY >= HEIGHT) {
            return false;
        }

        // 2. 碰撞检测 (是否撞到已有的方块)
        // 注意：nextY < 0 的情况通常允许（方块刚生成在屏幕上方），所以这里不判断 < 0
        if (nextY >= 0 && (map[nextX][nextY] != 0 && map[nextX][nextY] != 2 && map[nextX][nextY] != 1)) {
            return false;
        }
    }
    return true;
}

void Tetromino::rotate() {//旋转Tetromino
    // O 形方块不需要旋转
    if (type == TetrominoType::O) {
        return;
    }

    // 1. 保存旧的相对坐标，以便旋转失败时恢复
    auto oldCoords = relativeCoords;
    int oldX = x;
    int oldY = y;


    // 2. 对每个相对坐标应用旋转公式
    // 顺时针旋转90度的公式：(x, y) -> (y, -x)

    for (auto& coord : relativeCoords) {
        int newX = coord.y;
        int newY = -coord.x;
        coord.x = newX;
        coord.y = newY;
    }
    // 4. 踢墙测试 (Wall Kick)
    // 如果旋转后直接检测是合法的，则不需要踢墙，直接返回
    if (this->isValid()) {
        return;
    }

    // 如果直接旋转不合法，遍历踢墙测试表
    bool kickSuccess = false;
    for (const auto& kick : KICK_TESTS) {
        // 尝试应用偏移量
        x = oldX + kick.first;
        y = oldY + kick.second;

        // 检查应用偏移量后的位置是否合法
        if (this->isValid()) {
            kickSuccess = true;
            break; // 找到合法位置，跳出循环
        }
    }

    // 5. 如果所有踢墙尝试都失败，回滚到旋转前的状态
    if (!kickSuccess) {
        relativeCoords = oldCoords;
        x = oldX;
        y = oldY;
    }

}
void Tetromino::move(int dx, int dy) {//将Tetromino移动相应的距离

	x += dx;
	y += dy;
    if (isValid()) {
        return;
    }
    x -= dx;
    y -= dy;
}
void Tetromino::moveto(int tx, int ty) {//将Tetromino移动到相应的坐标
    x = tx;
    y = ty;
}
void Tetromino::cast() {
    // 1. 遍历方块的 4 个小方块
    // 如果你用的是 std::vector<Coord>，可以用范围 for 循环
    for (const auto& block : relativeCoords) {

        // 2. 计算在地图上的绝对坐标
        // 绝对坐标 = 方块中心位置 + 相对偏移量
        int mapX = this->x + block.x;
        int mapY = this->y + block.y;

        // 3. 边界检查 (防止数组越界崩溃)
        // 注意：这里通常只检查 mapY >= 0，因为方块可能在屏幕上方生成 (mapY < 0)
        if (mapX >= 0 && mapX < WIDTH && mapY >= 0 && mapY < HEIGHT) {
            // 4. 写入地图
            // 这里只在当前位置不是已固定方块(-1)时写入活动方块标记，避免覆盖已固定方块
            if (map[mapX][mapY] != -1) {
                map[mapX][mapY] = 1;
            }
        }
    }
}
void Tetromino::nextcast() {
    int x, y;
    for (x = 20; x < 30; x++) {
        for (y = 13; y < 17; y++) {
            map[x][y] = -2;
        }
    }
    for (const auto& block : relativeCoords) {
        int mapX = 23 + block.x;
        int mapY = 14 + block.y;
        map[mapX][mapY] = -3;
    }
}

