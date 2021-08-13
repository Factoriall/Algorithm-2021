#include <iostream>
using namespace std;

int memo[501][501];
int matrix[500][2];
const int INF = INT_MAX;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> matrix[i][0] >> matrix[i][1];
	}

	for (int i = 0; i < N; i++) {
		memo[1][i] = 0;
	}
	
	for (int i = 0; i < N - 1; i++) {
		memo[2][i] = matrix[i][0] * matrix[i][1] * matrix[i + 1][1];
		//cout << memo[2][i] << '\n';
	}

	//i = 묶음 개수
	//j = matrix에서 시작 idx
	for (int i = 3; i <= N; i++) {
		for (int j = 0; j <= N - i; j++) {
			memo[i][j] = INF;
			for (int k = 1; k < i; k++) {
				int sum = memo[k][j] + memo[i - k][j + k];
				int mul = matrix[j][0] * matrix[i + j - 1][1] * matrix[j + k - 1][1];
				//cout << "sum: " << sum << ", mul: " << mul << '\n';
				memo[i][j] = min(memo[i][j], sum + mul);
			}
			//printf("%d, %d: %d\n", i, j, memo[i][j]);
		}
	}

	cout << memo[N][0];
}