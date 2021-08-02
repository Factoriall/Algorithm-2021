#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

long long memo[2002][2002];

int main() {
	int d, m;
	scanf("%d %d", &d, &m);
	memo[0][0] = 1;
	//나머지 정리에 따라 더하기 및 곱하기는 모듈라에 영향 안 미침
	//크기가 4000이므로 충분, dp로 가능
	for (int i = 1; i <= d/2; i++) {
		for (int j = i; j >= 1; j -= 2) {
			memo[i][j] = (memo[i - 1][j - 1] + memo[i - 1][j + 1]) % m;
		}
	}

	long long answer = 0;
	for (int i = 1; i <= d / 2; i++) {
		answer = (answer + ((memo[d / 2][i] * memo[d / 2][i]) % m)) % m;
	}
	printf("%lld\n", answer);
}