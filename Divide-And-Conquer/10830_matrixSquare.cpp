#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int** matrix;
int N;
long long B;

int** dac(long long b);
int** square(int** m, bool isEven);//isEven: 같은 행렬 사용하는지 아님 matrix를 사용하는지 확인 여부

int main() {
	scanf("%d %lld", &N, &B);

	matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++) {
			int num;
			scanf("%d", &num);
			if (num == 1000) matrix[i][j] = 0;//1000일 경우 0으로 바꿔줘서 예외 사항 고치기
			else matrix[i][j] = num;
		}
	}

	int** result = dac(B);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
}

int** dac(long long b) {//divide and conquer 담당 함수
	if (b == 1) return matrix;
	int** ret;
	if (b % 2 == 0) ret = square(dac(b / 2), true);
	else ret =  square(square(dac(b / 2), true), false);
	
	return ret;
}

int** square(int** m, bool isEven) {//행렬 곱 함수
	int** ret = new int* [N];

	for (int i = 0; i < N; i++) {
		ret[i] = new int[N];
		for (int j = 0; j < N; j++) {
			ret[i][j] = 0;
			for (int k = 0; k < N; k++) {
				if(isEven)ret[i][j] = (ret[i][j] + (m[i][k] * m[k][j]) % 1000) % 1000;
				else ret[i][j] = (ret[i][j] + (m[i][k] * matrix[k][j]) % 1000) % 1000;
			}
		}
	}
	
	return ret;
}