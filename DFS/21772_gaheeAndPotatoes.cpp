#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

char map[100][100];
int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, 1, 0, -1 };
typedef pair<int, int> P;
int R, C, T;
int answer = 0;
void dfs(P now, int cnt, int eat);
bool isOutOfRange(P p);

int main() {
	scanf("%d %d %d", &R, &C, &T);

	P start;
	for (int i = 0; i < R; i++) {
		char line[101];
		scanf("%s", line);
		for (int j = 0; j < C; j++) {
			map[i][j] = line[j];
			if (line[j] == 'G') start = P(i, j);
		}
	}

	dfs(start, 0, 0);
	printf("%d\n", answer);
}

void dfs(P now, int cnt, int eat) {
	if (cnt == T) {
		answer = max(answer, eat);
		return;
	}

	for (int d = 0; d < 4; d++) {
		P next = P(now.first + dy[d], now.second + dx[d]);
		if (!isOutOfRange(next) 
			&& map[next.first][next.second] != '#') {
			int nEat = eat;
			if (map[next.first][next.second] == 'S') {
				nEat++;
			}
			dfs(next, cnt + 1, nEat);
			if (nEat != eat) map[next.first][next.second] = 'S';
		}
	}
}

bool isOutOfRange(P p){
	return p.first < 0 || p.second < 0 || p.first >= R || p.second >= C;
}