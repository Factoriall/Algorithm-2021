#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

vector<int> adj[100];
void bfs(int dist[][100], int s);

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int c1, c2;
		scanf("%d %d", &c1, &c2);
		adj[c1 - 1].push_back(c2 - 1);
		adj[c2 - 1].push_back(c1 - 1);
	}

	int dist[100][100];
	for (int T = 0; T < N; T++) {
		bfs(dist, T);
	}

	int a, b, d;
	d = 987654321;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int sum = 0;
			for (int t = 0; t < N; t++) {
				sum += min(dist[i][t], dist[j][t]);
			}
			if (d > sum) {
				d = sum;
				a = i + 1;
				b = j + 1;
			}
		}
	}

	printf("%d %d %d", a, b, d);
}

void bfs(int dist[][100], int s) {
	bool isVisited[100] = { false };
	queue<int> q;
	q.push(s);
	isVisited[s] = true;

	int cnt = 0;
	while (!q.empty()) {
		int qSize = q.size();
		for (int T = 0; T < qSize; T++) {
			int now = q.front();
			q.pop();
			dist[s][now] = cnt * 2;
			for (int next : adj[now]) {
				if (!isVisited[next]) {
					isVisited[next] = true;
					q.push(next);
				}
			}
		}
		cnt++;
	}
}