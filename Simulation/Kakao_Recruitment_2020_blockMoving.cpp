#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;


int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

int R, C;
vector<vector<int>> boardMap;

struct Robot {
    int y; int x;
    int dir;

    Robot() {}
    Robot(int y, int x, int d) {
        this->y = y;
        this->x = x;
        dir = d;
    }

    bool isReachedEnd() {
        return (y == R - 1 && x == C - 2 && dir == 0) || (y == R - 2 && x == C - 1 && dir == 1);
    }

    bool isMovable() {
        if (y < 0 || x < 0 || y >= R || x >= C) return false;
        if (boardMap[y][x] == 1) return false;
        int y2 = y + dy[dir]; int x2 = x + dx[dir];
        if (y2 < 0 || x2 < 0 || y2 >= R || x2 >= C) return false;
        if (boardMap[y2][x2] == 1) return false;
        return true;
    }
};

bool isVisited[100][100][2];

bool isRotatable(int y, int x) {
    if (y < 0 || x < 0 || y >= R || x >= C) return false;
    if (boardMap[y][x] == 1) return false;
    return true;
}


//dir 0 : 오른쪽, 1: 아래
int solution(vector<vector<int>> board) {
    R = board.size();
    C = board[0].size();
    boardMap = board;
    
    queue<Robot> q;
    q.push(Robot(0,0,0));
    isVisited[0][0][0] = true;
    int answer = 0;
    while (!q.empty()) {
        int qSize = q.size();
        cout << "cnt: " << answer << '\n';
        for (int t = 0; t < qSize; t++) {
            Robot now = q.front();
            cout << "now: (" << now.y << "," << now.x << ")/dir: " << now.dir << '\n';
            q.pop();

            if (now.isReachedEnd())  return answer;
            //회전 없이 이동
            for (int d = 0; d < 4; d++) {
                Robot nr = Robot(now.y + dy[d], now.x + dx[d], now.dir);
                if (nr.isMovable() && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }
            }
            //회전
            if (now.dir == 0) {//오른쪽
                //왼쪽 기준 회전
                Robot nr = Robot(now.y - 1, now.x, 1);
                if (nr.isMovable() && isRotatable(now.y - 1, now.x + 1) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }
                nr = Robot(now.y, now.x, 1);
                if (nr.isMovable() && isRotatable(now.y + 1, now.x + 1) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }

                //오른쪽 기준 회전
                nr = Robot(now.y - 1, now.x + 1, 1);
                if (nr.isMovable() && isRotatable(now.y - 1, now.x) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }

                nr = Robot(now.y, now.x + 1, 1);
                if (nr.isMovable() && isRotatable(now.y + 1, now.x) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }
            }
            else {//위쪽
                //위쪽 기준 회전
                Robot nr = Robot(now.y, now.x - 1, 0);
                if (nr.isMovable() && isRotatable(now.y + 1, now.x - 1) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }

                nr = Robot(now.y, now.x, 0);
                if (nr.isMovable() && isRotatable(now.y + 1, now.x + 1) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }

                //아래 기준 회전
                nr = Robot(now.y + 1, now.x - 1, 0);
                if (nr.isMovable() && isRotatable(now.y, now.x - 1) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }

                nr = Robot(now.y + 1, now.x, 0);
                if (nr.isMovable() && isRotatable(now.y, now.x + 1) && !isVisited[nr.y][nr.x][nr.dir]) {
                    isVisited[nr.y][nr.x][nr.dir] = true;
                    q.push(nr);
                }
            }
        }

        answer++;
    }

    return -1;
}

int main() {
    vector<vector<int>> board = { {0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0} };
    cout << solution(board);
}