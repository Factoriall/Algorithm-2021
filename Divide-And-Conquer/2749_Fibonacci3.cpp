#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

const int MOD = 1000000;
long long N;
long long** matrix;

long long** fibo(long long n);
long long** square(long long** m, bool isEven);

//Fibonacci의 경우 보통 반복, DP로 풀 수 있지만 여기서 주어진 n의 한계는 1조가 넘어 DP가 불가능
//그러므로 피보나치 공식을 활용한 Divide and Conquer를 사용해서 풀어본다
/*
출처: https://shoark7.github.io/programming/algorithm/%ED%94%BC%EB%B3%B4%EB%82%98%EC%B9%98-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98%EC%9D%84-%ED%95%B4%EA%B2%B0%ED%95%98%EB%8A%94-5%EA%B0%80%EC%A7%80-%EB%B0%A9%EB%B2%95
목차 3.4에 피보나치 수열에 관한 식이 나와 있음
이를 이용해 divide and conquer를 활용할 경우 logN만에 푸는 것이 가능해지는 것
*/

int main() {
	long long N;
	scanf("%lld", &N);
	matrix = new long long* [2];//배열 생성 시 이렇게 하는 것
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
					ret[i][j] = (ret[i][j] + (m[i][k] * m[k][j]) % MOD) % MOD;//같은 행렬을 곱하는 식
				else
					ret[i][j] = (ret[i][j] + (m[i][k] * matrix[k][j]) % MOD) % MOD;//이미 구한 행렬에 기본 행렬을 곱하는 식
			}
		}
	}

	return ret;
}
