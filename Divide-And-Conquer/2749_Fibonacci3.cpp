#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

const int MOD = 1000000;
long long N;
long long** matrix;

long long** fibo(long long n);
long long** square(long long** m, bool isEven);

//Fibonacci�� ��� ���� �ݺ�, DP�� Ǯ �� ������ ���⼭ �־��� n�� �Ѱ�� 1���� �Ѿ� DP�� �Ұ���
//�׷��Ƿ� �Ǻ���ġ ������ Ȱ���� Divide and Conquer�� ����ؼ� Ǯ���
/*
��ó: https://shoark7.github.io/programming/algorithm/%ED%94%BC%EB%B3%B4%EB%82%98%EC%B9%98-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98%EC%9D%84-%ED%95%B4%EA%B2%B0%ED%95%98%EB%8A%94-5%EA%B0%80%EC%A7%80-%EB%B0%A9%EB%B2%95
���� 3.4�� �Ǻ���ġ ������ ���� ���� ���� ����
�̸� �̿��� divide and conquer�� Ȱ���� ��� logN���� Ǫ�� ���� ���������� ��
*/

int main() {
	long long N;
	scanf("%lld", &N);
	matrix = new long long* [2];//�迭 ���� �� �̷��� �ϴ� ��
	for (int i = 0; i < 2; i++) {
		matrix[i] = new long long[2];
	}
	matrix[0][0] = 1;
	matrix[1][0] = 1;
	matrix[0][1] = 1;
	matrix[1][1] = 0;
 
	long long** ret = fibo(N);
	printf("%lld\n", ret[0][1]);
}

long long** fibo(long long n) {
	if (n == 1) return matrix;
	long long** ret = new long long* [2];
	for (int i = 0; i < 2; i++) {
		ret[i] = new long long[2];
	}

	if (n % 2 == 0) {
		ret = square(fibo(n / 2), true);
	}
	else ret = square(square(fibo(n / 2), true), false);

	return ret;
}

long long** square(long long** m, bool isEven) {
	long long** ret = new long long*[2];
	for (int i = 0; i < 2; i++) {
		ret[i] = new long long[2];
		for (int j = 0; j < 2; j++) {
			ret[i][j] = 0;
			for (int k = 0; k < 2; k++) {
				if(isEven)
					ret[i][j] = (ret[i][j] + (m[i][k] * m[k][j]) % MOD) % MOD;//���� ����� ���ϴ� ��
				else
					ret[i][j] = (ret[i][j] + (m[i][k] * matrix[k][j]) % MOD) % MOD;//�̹� ���� ��Ŀ� �⺻ ����� ���ϴ� ��
			}
		}
	}

	return ret;
}
