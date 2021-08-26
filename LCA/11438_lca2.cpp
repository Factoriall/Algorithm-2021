#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100000;
vector<int> adj[MAX];

int parent[MAX][18];
int depth[MAX];

int N, M;

void makeTreeByDFS(int now, int dep, int prev) {
	parent[now][0] = prev;
	depth[now] = dep;

	for (int next : adj[now]) {
		if (next != prev) {
			makeTreeByDFS(next, dep + 1, now);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int s, e;
		cin >> s >> e;
		adj[s - 1].push_back(e - 1);
		adj[e - 1].push_back(s - 1);
	}

	memset(parent, -1, sizeof(parent));
	makeTreeByDFS(0, 0, -1);

	for (int j = 1; j < 18; j++) {
		for (int i = 0; i < N; i++) {
			if(parent[i][j-1] != -1) 
				parent[i][j] = parent[parent[i][j - 1]][j - 1];
		}
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		
		//1. 높이 맞추는 작업
		int d1 = depth[v1];
		int d2 = depth[v2];
		if (d1 > d2) {
			int diff = d1 - d2;
			int num = 0; 
			while (diff > 0) {
				if ((diff & 1) == 1) {
					v1 = parent[v1][num];
				}
				num++;
				diff >>= 1;
			}
		}
		else if (d1 < d2) {
			int diff = d2 - d1;
			int num = 0;
			while (diff > 0) {
				if ((diff & 1) == 1) {
					v2 = parent[v2][num];
				}
				num++;
				diff >>= 1;
			}
		}
		

		//2. 둘의 lca 맞추는 과정
		if (v1 != v2) {
			for (int t = 17; t >= 0; t--) {
				if (parent[v1][t] != -1 && parent[v1][t] != parent[v2][t]) {
					v1 = parent[v1][t];
					v2 = parent[v2][t];
				}
			}

			v1 = parent[v1][0];
		}

		cout << v1 + 1 << '\n';
	}
}