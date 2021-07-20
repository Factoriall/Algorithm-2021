#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
int N, K;
long long dac(long long root, int power);

int main() {
	scanf("%d %d", &N, &K);
	if (K == 0 || K == N) {//�� ���� �� ������ 1
		printf("1\n");
		return 0;
	}
	else if (K == 1) {//1�̸� N
		printf("%d\n", N);
		return 0;
	}

	long long nf = 0;//n!
	long long kf = 0;//k!
	long long nmkf = 0;//(n-k)!

	int cnt = 1;
	long long ft = 1;
	while (cnt <= N) {//�ݺ� ���ؼ� ���丮�� �� ���ϱ�
		if (cnt == N) nf = ft;
		if (cnt == K) kf = ft;
		if (cnt == N - K) nmkf = ft;
		ft = (ft *(++cnt)) % MOD;
	}

	//���⼭ �и��� MOD���� ����ȵŴ� ������ �����Ƿ� �丣���� �������� �̿��ؼ� �и� ���ڷ� ġȯ���������
	//��ó: https://m.blog.naver.com/hongjg3229/221650178981
	long long div = dac((nmkf * kf) % MOD, MOD - 2);//�ŵ� ������ ��� ���� ������ �̿��ϸ� ���� Ǯ�� ����
	long long answer = (nf * div) % MOD;
	printf("%lld\n", answer);
}

long long dac(long long root, int power) {
	if (power == 1) return root;
	long long half = dac(root, power / 2) % MOD;
	if (power % 2 == 0) return (half * half) % MOD;
	else return (((half * half) % MOD) * root) % MOD;
}