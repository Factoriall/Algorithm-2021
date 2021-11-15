#include <iostream>
#include <queue>
using namespace std;

int F, S, G, U, D;

bool isVisited[1'000'001];
bool isOutOfRange(int n);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> F >> S >> G >> U >> D;
	queue<int> q;
	q.push(S);
	isVisited[S] = true;
	int cnt = 0;
	while (!q.empty()) {
		int qSize = q.size();
		for (int t = 0; t < qSize; t++) {
			int now = q.front();
			if (now == G) {
				cout << cnt;
				return 0;
			}
			q.pop();
			
			int up = now + U;
			if (!isOutOfRange(up) && !isVisited[up]) {
				isVisited[up] = true;
				q.push(up);
			}
			int down = now - D;
			if (!isOutOfRange(down) && !isVisited[down]) {
				isVisited[down] = true;
				q.push(down);
			}
		}
		cnt++;
	}

	cout << "use the stairs";
}

bool isOutOfRange(int n) {
	return n < 1 || n > F;
}