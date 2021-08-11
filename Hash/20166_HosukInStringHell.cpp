#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
using namespace std;

int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
char miro[10][10];
map<string, int> godLike[5];
vector<string> gStr;

typedef pair<string, int> P;

struct QInfo {
	int y, x;
	string str;
	QInfo(int y, int x, string s) {
		this->y = y;
		this->x = x;
		str = s;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, K;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		string line;
		cin >> line;
		for (int j = 0; j < M; j++) {
			miro[i][j] = line[j];
		}
	}

	for (int i = 0; i < K; i++) {
		string str;
		cin >> str;
		godLike[str.length() - 1].insert(P(str, 0));
		gStr.push_back(str);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			queue<QInfo> q;
			string s = string() + miro[i][j];
			q.push(QInfo(i, j, s));
			int cnt = 1;
			if (godLike[0].find(s) != godLike[0].end()) {
				godLike[0].find(s)->second += 1;
			}
			while (!q.empty() && cnt < 5) {
				int qSize = q.size();
				for (int t = 0; t < qSize; t++) {
					QInfo now = q.front();
					q.pop();
					for (int d = 0; d < 8; d++) {
						int ny = now.y + dy[d];
						if (ny < 0) ny = N - 1;
						else if (ny == N) ny = 0;
						int nx = now.x + dx[d];
						if (nx < 0) nx = M - 1;
						else if (nx == M) nx = 0;

						string ns = now.str + miro[ny][nx];

						if (godLike[cnt].find(ns) != godLike[cnt].end()) {
							godLike[cnt].find(ns)->second += 1;
						}
						q.push(QInfo(ny, nx, ns));
					}
				}
				cnt++;
			}
		}
	}

	for (string str : gStr) {
		printf("%d\n", godLike[str.length() - 1].find(str) -> second);
	}
}