#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int l1, l2;
typedef pair<int, int> P;
vector<P> adj[10000];

bool isReachable(int weight);

int main() {
	scanf("%d %d", &N, &M);

	int hi = 0;
	for (int i = 0; i < M; i++) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		adj[s - 1].push_back(P(e - 1, w));
		adj[e - 1].push_back(P(s - 1, w));
		hi = max(hi, w);
	}
	hi++;

	scanf("%d %d", &l1, &l2);
	l1--;
	l2--;

	int lo = 0;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		//printf("mid: %d\n", mid);
		//printf("%d\n", isReachable(mid) ? 1 : 0);
		if (isReachable(mid)) lo = mid;
		else hi = mid;
	}

	printf("%d\n", lo);
}

bool visited[10000];
bool isReachable(int weight) {
	queue<int> q; 
	q.push(l1);
	fill(visited, visited + 10000, false);
	visited[l1] = true;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		if (now == l2) return true;
		for (P next : adj[now]) {
			int n = next.first;
			int limit = next.second;
			if (!visited[n] && weight <= limit) {
				visited[n] = true;
				q.push(n);
			}
		}
	}

	return false;
}