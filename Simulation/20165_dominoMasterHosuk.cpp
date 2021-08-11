#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int N, M, R;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int dominos[100][100];
bool dominoFallen[100][100];

int attack(int y, int x, int d);
bool isOutOfRange(int y, int x);
int getDirIdx(char d);

int main() {
	scanf("%d %d %d", &N, &M, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &dominos[i][j]);
		}
	}

	int score = 0;
	for (int r = 0; r < R; r++) {
		int y, x;
		char d;
		//공격
		scanf("%d %d %c", &y, &x, &d);
		int dIdx = getDirIdx(d);
		score += attack(y - 1, x - 1, dIdx);
		//방어
		scanf("%d %d", &y, &x);
		dominoFallen[y - 1][x - 1] = false;
	}

	printf("%d\n", score);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%c ", dominoFallen[i][j] ? 'F' : 'S');
		}
		printf("\n");
	}
	printf("\n");
}

int attack(int y, int x, int d) {
	if (dominoFallen[y][x]) return 0;//이미 무너졌다면 아무 일도 안 일어남
	int length = dominos[y][x];//현재 무너지는 길이
	int cnt = 0;
	int score = 0;
	while (!isOutOfRange(y,x) && cnt < length) {
		if (!dominoFallen[y][x]) {
			dominoFallen[y][x] = true;
			score++;
			length = max(length, cnt + dominos[y][x]);
		}
		y += dy[d];
		x += dx[d];
		cnt++;
	}
	return score;
}

bool isOutOfRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}

int getDirIdx(char d) {
	switch (d) {
	case 'N':
		return 0;
	case 'E':
		return 1;
	case 'S':
		return 2;
	case 'W':
		return 3;
	}
	return -1;
}