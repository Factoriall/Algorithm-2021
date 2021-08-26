#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> P;

const int MAX = 17;

int depth[40000];
int parent[40000][MAX];
int parentDist[40000][MAX];
vector<P> adj[40000];
int N;

void makeTreeByDfs(P now, int dep, P prev) {
	parent[now.first][0] = prev.first;
	parentDist[now.first][0] = now.second;

	depth[now.first] = dep;
	for (P next : adj[now.first]) {
		if (next.first == prev.first) continue;
		makeTreeByDfs(next, dep + 1, now);
	}
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int n1, n2, d;
		cin >> n1 >> n2 >> d;
		n1--; n2--;
		adj[n1].push_back(P(n2, d));
		adj[n2].push_back(P(n1, d));
	}

	memset(parent, -1, sizeof(parent));
	memset(parentDist, -1, sizeof(parentDist));
	makeTreeByDfs(P(0, 0), 0, P(-1, -1));

	//parent 생성
	for (int j = 1; j < MAX; j++) {
		for (int i = 0; i < N; i++) {
			if (parent[i][j - 1] == -1) continue;
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
			if (parent[i][j] == -1) parentDist[i][j] = -1;
			else parentDist[i][j] = parentDist[i][j-1] + parentDist[parent[i][j - 1]][j - 1];
		}
	}

	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;

		//1. 깊이 맞추기
		int dist = 0;
		int du = depth[u]; int dv = depth[v];
		if (du != dv) {
			int diff;
			if (du > dv) {
				diff = du - dv;
				int cnt = 0;
				while (diff > 0) {
					if (diff & 1) {
						dist += parentDist[u][cnt];
						u = parent[u][cnt];
					}
					cnt++;
					diff >>= 1;
				}
			}
			else {
				diff = dv - du;
				int cnt = 0;
				while (diff > 0) {
					if (diff & 1) {
						dist += parentDist[v][cnt];
						v = parent[v][cnt];
					}
					cnt++;
					diff >>= 1;
				}
			}
		}

		//2. 깊이 토대로 최소공통조상 찾기
		if (u != v) {
			for (int d = MAX - 1; d >= 0; d--) {
				if (parent[u][d] == -1) continue;
				if (parent[u][d] != parent[v][d]) {
					dist += parentDist[u][d] + parentDist[v][d];
					u = parent[u][d];
					v = parent[v][d];
				}
			}
			dist += parentDist[u][0] + parentDist[v][0];
			u = parent[u][0];
		}
		cout << dist << '\n';
	}

}