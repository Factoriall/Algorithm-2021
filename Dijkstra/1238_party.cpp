#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

class Edge {
public:
	int to;
	int weight;
	Edge(int t, int w) {
		to = t;
		weight = w;
	}
};

class PQInfo {
public:
	int now;
	int total;
	PQInfo() {}
	PQInfo(int n, int t) {
		now = n;
		total = t;
	}
};

class comparator {
public:
	bool operator()(const PQInfo& a, const PQInfo& b) {
		if (a.total < b.total) return false;
		return true;
	}
};

vector<Edge> graph[1000];
const int INF = 987654321;
int getDistance(int s, int e);

int main() {
	int N, M, X;
	scanf("%d %d %d", &N, &M, &X);

	for (int i = 0; i < M; i++) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		graph[s-1].push_back(Edge(e-1, w));
	}
	
	int answer = 0;
	for (int i = 0; i < N; i++) {
		int total = getDistance(i, X - 1) + getDistance(X - 1, i);
		answer = max(answer, total);
	}

	printf("%d\n", answer);
}

int getDistance(int s, int e) {
	priority_queue<PQInfo, vector<PQInfo>, comparator> pq;

	bool visited[1000];
	int dist[1000];
	fill(visited, visited + 1000, false);
	fill(dist, dist+1000, INF);

	dist[s] = 0;
	pq.push(PQInfo(s, 0));
	
	while (!pq.empty()) {
		int cur;
		do {
			cur = pq.top().now;
			pq.pop();
		} while (!pq.empty() && visited[cur]);
		if (visited[cur]) break;

		visited[cur] = true;
		for (Edge next : graph[cur]) {
			if (dist[next.to] > dist[cur] + next.weight) {
				pq.push(PQInfo(next.to, dist[cur] + next.weight));
				dist[next.to] = dist[cur] + next.weight;
			}
		}
	}

	return dist[e];
}