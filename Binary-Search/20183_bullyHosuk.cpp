#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, long long> P;

int N, M, S, E;
long long C;
const long long INF = 123456789012345;
const int MAX = 100001;
vector<P> adj[MAX];

bool isReachable(int mx);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//�Է°� ����
	cin >> N >> M >> S >> E >> C;

	int hiMax = 0;
	for (int i = 0; i < M; i++) {
		int c1, c2, w;
		cin >> c1 >> c2 >> w;
		adj[c1].push_back(P(w, c2));
		adj[c2].push_back(P(w, c1));
		hiMax = max(hiMax, w + 1);
	}

	//�̺� Ž���� ����ؼ� ��� �ִ��� �ּҰ� Ž��
	//�̺� Ž��-O(logN) * ���ͽ�Ʈ�� O(nlogn) ���� ����� Ž�� ����
	int lo = 0;
	int hi = hiMax;
	while (lo + 1 < hi) {
		int mid = (hi + lo) / 2;
		if (isReachable(mid)) hi = mid;
		else lo = mid;
	}
	if (hi == hiMax) cout << -1;
	else cout << hi;
}

//���ͽ�Ʈ�� �˰���, dist[E]�� C ���Ϸ� ������ Ȯ��
bool isReachable(int mx) {
	long long dist[MAX];
	bool isVisited[MAX] = { false };
	fill(dist, dist + MAX, INF);
	dist[S] = 0;

	priority_queue<P, vector<P>, greater<P>> pq;
	pq.push(P(0, S));
	while (!pq.empty()) {
		int now;
		do {
			now = pq.top().second;
			pq.pop();
		} while (!pq.empty() && isVisited[now]);
		if (isVisited[now]) break;
		isVisited[now] = true;

		if (now == E) return dist[E] <= C;//����, �� �� ��� ��ȯ

		for (P next : adj[now]) {
			if (next.first > mx) continue; //�̺� Ž�� ���� ������ ����ġ��
			if (dist[now] + next.first > C) continue;
			if (dist[next.second] > dist[now] + next.first) {
				dist[next.second] = dist[now] + next.first;
				pq.push(next);
			}
		}
	}

	return false; // E�� ���� �������Ƿ� false
}