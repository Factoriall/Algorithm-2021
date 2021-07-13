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

        if (a == 0) {//���
            if (b == 0) {//����
                pillars[x][y] = returnResultOfDestructPillar(x, y) ? false : true;
            }
            else {//�Ǽ�
                pillars[x][y] = returnResultOfConstructPillar(x, y) ? true : false;
            }
        }
        else {//��
            if (b == 0) {//����
                beams[x][y] = returnResultOfDestructBeam(x, y) ? false : true;
            }
            else {//�Ǽ�
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

// ����� �ٴ� ���� �ְų� ���� ���� �� �κ� ���� �ְų�, �Ǵ� �ٸ� ��� ���� �־�� �մϴ�.
bool returnResultOfConstructPillar(int x, int y) {
    if (y == 0) return true;//�ٴ�
    if (checkPillar(x, y - 1)) return true;//�ٸ� ��� ��
    if (checkBeam(x - 1, y)) return true;//���� �� ��
    if (checkBeam(x, y)) return true;//������ �� ��

    return false;
}

//���� ���� �� �κ��� ��� ���� �ְų�, �Ǵ� ���� �� �κ��� �ٸ� ���� ���ÿ� ����Ǿ� �־�� �մϴ�.
bool returnResultOfConstructBeam(int x, int y) {
    if (checkPillar(x, y - 1) || checkPillar(x + 1, y - 1)) return true;//���
    if (checkBeam(x - 1, y) && checkBeam(x + 1, y)) return true;//��

    return false;
}

bool returnResultOfDestructPillar(int x, int y) {
    pillars[x][y] = false;
    if (checkBeam(x, y + 1) && !returnResultOfConstructBeam(x, y + 1)) return false;//x,y+1 ��
    if (checkBeam(x - 1, y + 1) && !returnResultOfConstructBeam(x - 1, y + 1)) return false;//x-1, y+1��
    if (checkPillar(x, y + 1) && !returnResultOfConstructPillar(x, y + 1)) return false;//x, y+1 ���

    return true;
}

bool returnResultOfDestructBeam(int x, int y) {
    beams[x][y] = false;
    if (checkBeam(x - 1, y) && !returnResultOfConstructBeam(x - 1, y)) return false;//x-1,y ��
    if (checkBeam(x + 1, y) && !returnResultOfConstructBeam(x + 1, y)) return false;//x+1,y ��
    if (checkPillar(x, y) && !returnResultOfConstructPillar(x, y)) return false;//x,y ���
    if (checkPillar(x + 1, y) && !returnResultOfConstructPillar(x + 1, y)) return false;//x+1,y ���

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

