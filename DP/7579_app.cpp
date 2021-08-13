#include <iostream>
#include <algorithm>
using namespace std;

int memo[101][10001];
const int INF = 987654321;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	int memory[101];
	int cost[101];
	for (int i = 1; i <= N; i++) {
		cin >> memory[i];
	}
	for (int i = 1; i <= N; i++) {
		cin >> cost[i];
	}
	// i: 메모리 및 cost에서 사용한 묶음 수
	// j: cost
	// memo[i][j]: i까지의 앱을 포함했을 때 cost j에서 얻을 수 있는 최대 메모리
	for (int i = 1; i <= N; i++) {
		int mSize = memory[i];
		int c = cost[i];
		for (int j = 1; j <= 10000; j++) {
			memo[i][j] = memo[i - 1][j];
			if (c <= j) memo[i][j] = max(memo[i][j], memo[i - 1][j - c] + mSize);
		}
	}

	//i까지의 앱을 모두 포함했을 때 cost i 에서의 최대값이 M을 처음 넘는 지점이 정답
	for (int i = 1; i <= 10000; i++) {
		if (memo[N][i] >= M) {
			cout << i;
			break;
		}
	}
}