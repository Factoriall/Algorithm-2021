#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

long long memo[2002][2002];

int main() {
	int d, m;
	scanf("%d %d", &d, &m);
	memo[0][0] = 1;
	//������ ������ ���� ���ϱ� �� ���ϱ�� ���� ���� �� ��ħ
	//ũ�Ⱑ 4000�̹Ƿ� ���, dp�� ����
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