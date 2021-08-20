#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 987654321;
int dp[5][5];

int getPower(int now, int next) {
	if (now == 0) return 2;
	if (abs(now - next) == 2) return 4;
	return 3;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;

	int N;
	cin >> N;

	
	while (N != 0) {
		int next[5][5];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				next[i][j] = INF;
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (dp[i][j] == INF) continue;
				if (i == N || j == N) next[i][j] = min(dp[i][j] + 1, next[i][j]);
				else {
					next[N][j] = min(next[N][j], dp[i][j] + getPower(i, N));
					next[i][N] = min(next[i][N], dp[i][j] + getPower(j, N));
				}
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				dp[i][j] = next[i][j];
			}
		}
		cin >> N;
	}

	int answer = INF;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			answer = min(answer, dp[i][j]);
		}
	}
	cout << answer;

}