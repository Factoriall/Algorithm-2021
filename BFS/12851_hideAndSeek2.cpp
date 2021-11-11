#include <iostream>
#include <queue>
using namespace std;

int N, K;
bool isVisited[200001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;
	
	queue<int> q;
	q.push(N); 
	isVisited[N] = true;
	int sec = 0;
	while (!q.empty()) {
		int qSize = q.size();
		bool isEnd = false;
		int cnt = 0;
		for (int T = 0; T < qSize; T++) {
			int num = q.front();
			isVisited[num] = true;
			q.pop();

			if (num == K) {
				cnt++;
				isEnd = true;
			}
			if (isEnd) continue;
			
			if (num < 200000 && !isVisited[num + 1]) q.push(num + 1);
			if (num > 0 && !isVisited[num - 1]) q.push(num - 1);
			if (2 * num <= 200000 && !isVisited[2 * num]) q.push(2 * num);
		}
		if (isEnd) {
			cout << sec << '\n';
			cout << cnt << '\n';
			break;
		}
		sec++;
	}
}