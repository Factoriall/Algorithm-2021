#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
bool pillars[101][101];
bool beams[101][101];
int N;

bool returnResultOfDestructPillar(int x, int y);
bool returnResultOfConstructPillar(int x, int y);
bool returnResultOfDestructBeam(int x, int y);
bool returnResultOfConstructBeam(int x, int y);
bool checkPillar(int x, int y);
bool checkBeam(int x, int y);
bool isPillarOutOfRange(int x, int y);
bool isBeamOutOfRange(int x, int y);

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    N = n;

    for (vector<int> frame : build_frame) {
        int x = frame[0];
        int y = frame[1];
        int a = frame[2];
        int b = frame[3];

        if (a == 0) {//기둥
            if (b == 0) {//삭제
                pillars[x][y] = returnResultOfDestructPillar(x, y) ? false : true;
            }
            else {//건설
                pillars[x][y] = returnResultOfConstructPillar(x, y) ? true : false;
            }
        }
        else {//보
            if (b == 0) {//삭제
                beams[x][y] = returnResultOfDestructBeam(x, y) ? false : true;
            }
            else {//건설
                beams[x][y] = returnResultOfConstructBeam(x, y) ? true : false;
            }
        }

        printf("Pillar\n");
        for (int y = n; y >= 0; y--) {
            for (int x = 0; x <= n; x++) {
                printf(pillars[x][y] == true ? "1" : "0");
            }
            printf("\n");
        }
        printf("Beam\n");
        for (int y = n; y >= 0; y--) {
            for (int x = 0; x <= n; x++) {
                printf(beams[x][y] == true ? "1" : "0");
            }
            printf("\n");
        }
        printf("\n");
    }
    vector<vector<int>> ans;
    for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= n; y++) {
            if (pillars[x][y]) {
                ans.push_back({x,y,0});
            }
            if (beams[x][y]) {
                ans.push_back({ x,y,1 });
            }
        }
    }
    
    return ans;
}

// 기둥은 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나, 또는 다른 기둥 위에 있어야 합니다.
bool returnResultOfConstructPillar(int x, int y) {
    if (y == 0) return true;//바닥
    if (checkPillar(x, y - 1)) return true;//다른 기둥 위
    if (checkBeam(x - 1, y)) return true;//왼쪽 보 위
    if (checkBeam(x, y)) return true;//오른쪽 보 위

    return false;
}

//보는 한쪽 끝 부분이 기둥 위에 있거나, 또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 합니다.
bool returnResultOfConstructBeam(int x, int y) {
    if (checkPillar(x, y - 1) || checkPillar(x + 1, y - 1)) return true;//기둥
    if (checkBeam(x - 1, y) && checkBeam(x + 1, y)) return true;//보

    return false;
}

bool returnResultOfDestructPillar(int x, int y) {
    pillars[x][y] = false;
    if (checkBeam(x, y + 1) && !returnResultOfConstructBeam(x, y + 1)) return false;//x,y+1 보
    if (checkBeam(x - 1, y + 1) && !returnResultOfConstructBeam(x - 1, y + 1)) return false;//x-1, y+1보
    if (checkPillar(x, y + 1) && !returnResultOfConstructPillar(x, y + 1)) return false;//x, y+1 기둥

    return true;
}

bool returnResultOfDestructBeam(int x, int y) {
    beams[x][y] = false;
    if (checkBeam(x - 1, y) && !returnResultOfConstructBeam(x - 1, y)) return false;//x-1,y 보
    if (checkBeam(x + 1, y) && !returnResultOfConstructBeam(x + 1, y)) return false;//x+1,y 보
    if (checkPillar(x, y) && !returnResultOfConstructPillar(x, y)) return false;//x,y 기둥
    if (checkPillar(x + 1, y) && !returnResultOfConstructPillar(x + 1, y)) return false;//x+1,y 기둥

    return true;
}

bool checkPillar(int x, int y) {
    return !isPillarOutOfRange(x, y) && pillars[x][y];
}

bool checkBeam(int x, int y) {
    return !isBeamOutOfRange(x, y) && beams[x][y];
}

bool isPillarOutOfRange(int x, int y) {
    return x < 0 || y < 0 || x > N || y >= N;
}
bool isBeamOutOfRange(int x, int y) {
    return x < 0 || y < 0 || x >= N || y > N;
}


int main() {
    int n = 5;
    vector<vector<int>> build_frame = { {0,0,0,1}, {2,0,0,1}, {4,0,0,1}, {0,1,1,1}, {1,1,1,1}, {2,1,1,1}, {3,1,1,1}, {2,0,0,0}, {1,1,1,0}, {2,2,0,1} };
    vector<vector<int>> sol = solution(n, build_frame);

    for (vector<int> s : sol) {
        for (int n : s) {
            printf("%d ", n);
        }
        printf("\n");
    }
}

