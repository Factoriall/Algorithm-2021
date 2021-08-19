#include <iostream>
using namespace std;

long long memo[101][10][1 << 10];
const int MOD = 1'000'000'000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	for (int i = 1; i < 10; i++) {
		memo[1][i][1 << i] = 1;
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < (1 << 10); k++) {
				if (j != 9) {
					memo[i + 1][j + 1][k | (1 << (j + 1))] =
						(memo[i + 1][j + 1][k | (1 << (j + 1))] + memo[i][j][k]) % MOD;
				}
				if (j != 0) {
					memo[i + 1][j - 1][k | (1 << (j - 1))] =
						(memo[i + 1][j - 1][k | (1 << (j - 1))] + memo[i][j][k]) % MOD;
				}
			}
		}	
	}

	
	long long answer = 0;
	for (int i = 0; i < 10; i++) {
		answer = (answer + memo[N][i][(1 << 10) - 1]) % MOD;
	}
	

	cout << answer;
}