#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int dy[4] = { 1, -1, 0, 0 };
int dx[4] = { 0, 0, 1, -1 };
int N, M;
int map[100][100];
const int INF = 987654321;

class Point {
public:
	int y, x;
	Point(){}
	Point(int y, int x) {
		this->y = y;
		this->x = x;
	}

	bool isMoveable() {
		if (y < 0 || x < 0 || y >= N || x >= M) return false;
		if (map[y][x] == -1) return false;
		return true;
	}
};

class PQInfo {
public:
	Point now;
	int moveCnt;
	int impulseSum;
	PQInfo() {};

	PQInfo(Point p, int cnt, int sum) {
		now = p;
		moveCnt = cnt;
		impulseSum = sum;
	}
};

//comparator 사용, 숙지 중요
class comparator_pq {
public:
	bool operator()(PQInfo i1, PQInfo i2) {
		return i1.impulseSum > i2.impulseSum;//왼쪽 것이 더 큰게 오름차순 방향
	}
};

int main() {
	scanf("%d %d", & N, &M);
	int sy, sx, ey, ex;

	scanf("%d %d %d %d", &sy, &sx, &ey, &ex);
	sy--; sx--; ey--; ex--;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	priority_queue<PQInfo, vector<PQInfo>, comparator_pq> pq;
	//3배수따라 달라지는 방향 및 상황을 모두 고려해야 씹는 경우를 방지할 수 있음 -> [3]이 붙은 이유
  	int dist[100][100][3];
	bool isVisited[100][100][3];

	//2차원 이상의 배열을 초기화할 때 사용, 기억해두는 것이 좋을 듯!
	fill(&dist[0][0][0], &dist[0][0][0] + sizeof(dist) / sizeof(dist[0][0][0]), INF);
	fill(&isVisited[0][0][0], &isVisited[0][0][0] + sizeof(isVisited), false);

	//다익스트라 활용
	dist[sy][sx][0] = 0;
	pq.push(PQInfo(Point(sy, sx), 0, 0));
	while (!pq.empty()) {
		Point cur;
		int mcnt;
		do {
			cur = pq.top().now;
			mcnt = pq.top().moveCnt;
			pq.pop();
		} while (!pq.empty() && isVisited[cur.y][cur.x][mcnt]);
		if (isVisited[cur.y][cur.x][mcnt]) break;

		isVisited[cur.y][cur.x][mcnt] = true;
		/*
		int dy[4] = { 1, -1, 0, 0 };
		int dx[4] = { 0, 0, 1, -1 };
		0, 1: 위아래 -> 3k+1
		2, 3: 옆 -> 3k+2
		*/
		int nextMCnt = (mcnt + 1) % 3;
		for (int d = 0; d < 4; d++) {
			//3으로 나눌 때의 값 만큼 이동 방향 제한
			if (nextMCnt == 1 && (d == 2 || d == 3)) continue;
			if (nextMCnt == 2 && (d == 0 || d == 1)) continue;

			Point next = Point(cur.y + dy[d], cur.x + dx[d]);
			if (next.isMoveable() && dist[next.y][next.x][nextMCnt] > dist[cur.y][cur.x][mcnt] + map[next.y][next.x]) {
				//printf("pq insert: (%d, %d), %d\n", next.y, next.x, dist[cur.y][cur.x][mcnt] + map[next.y][next.x]);
				pq.push(PQInfo(next, nextMCnt, dist[cur.y][cur.x][mcnt] + map[next.y][next.x]));
				dist[next.y][next.x][nextMCnt] = dist[cur.y][cur.x][mcnt] + map[next.y][next.x];
			}
		}
	}
	int answer = INF;
	for (int i = 0; i < 3; i++) {
		answer = min(answer, dist[ey][ex][i]);
	}
	if (answer == INF) printf("-1\n");
	else printf("%d\n", answer);
}