#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
using namespace std;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int N, M;
int map[2000][2000];
bool isAirOn[2000][2000];

struct Point {
	int y, x;
	Point(int y, int x) {
		this->y = y;
		this->x = x;
	}

	bool isOutOfRange() {
		return y < 0 || x < 0 || y >= N || x >= M;
	}
};

int returnDirection(int objNum, int dir);
void moveByDirection(Point start);

int answer = 0;
int main() {
	scanf("%d %d", &N, &M);
	
	vector<Point> airConditioners;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				airConditioners.push_back(Point(i, j));
				isAirOn[i][j] = true;
				answer++;
			}
		}
	}

	for (Point start : airConditioners) {
		moveByDirection(start);
	}
	
	printf("%d\n", answer);
}

void moveByDirection(Point start) {
	for (int d = 0; d < 4; d++) {
		int dir = d;
		//printf("start: %d\n", dir);
		Point next = start;
		do {
			next = Point(next.y + dy[dir], next.x + dx[dir]);
			if (next.isOutOfRange() || ) break;
			if (!isAirOn[next.y][next.x]) {
				isAirOn[next.y][next.x] = true;
				answer++;
			}
			if (map[next.y][next.x] >= 1 && map[next.y][next.x] <= 4)
				dir = returnDirection(map[next.y][next.x], dir);
			//printf("(%d,%d)\n", next.y, next.x);
		} while (dir != -1);
	}
}

//0: ºÏ, 1: µ¿, 2: ³², 3: ¼­
int returnDirection(int objNum, int dir) {
	switch (objNum) {
	case 1:
		if (dir == 0 || dir == 2) return dir;
		else return -1;
	case 2:
		if (dir == 1 || dir == 3) return dir;
		else return -1;
	case 3:
		switch (dir) {
		case 0: return 1;
		case 1: return 0;
		case 2: return 3;
		case 3: return 2;
		}
	case 4:
		switch (dir) {
		case 0: return 3;
		case 1: return 2;
		case 2: return 1;
		case 3: return 0;
		}
	}
}