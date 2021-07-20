#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
int N, K;
long long dac(long long root, int power);

int main() {
	scanf("%d %d", &N, &K);
	if (K == 0 || K == N) {//이 수일 땐 무조건 1
		printf("1\n");
		return 0;
	}
	else if (K == 1) {//1이면 N
		printf("%d\n", N);
		return 0;
	}

	long long nf = 0;//n!
	long long kf = 0;//k!
	long long nmkf = 0;//(n-k)!

	int cnt = 1;
	long long ft = 1;
	while (cnt <= N) {//반복 통해서 팩토리얼 값 구하기
		if (cnt == N) nf = ft;
		if (cnt == K) kf = ft;
		if (cnt == N - K) nmkf = ft;
		ft = (ft *(++cnt)) % MOD;
	}

	//여기서 분모값을 MOD값이 적용안돼는 문제가 있으므로 페르마의 소정리를 이용해서 분모를 분자로 치환시켜줘야함
	//출처: https://m.blog.naver.com/hongjg3229/221650178981
	long long div = dac((nmkf * kf) % MOD, MOD - 2);//거듭 제곱의 경우 분할 정복을 이용하면 쉽게 풀기 가능
	long long answer = (nf * div) % MOD;
	printf("%lld\n", answer);
}

long long dac(long long root, int power) {
	if (power == 1) return root;
	long long half = dac(root, power / 2) % MOD;
	if (power % 2 == 0) return (half * half) % MOD;
	else return (((half * half) % MOD) * root) % MOD;
}