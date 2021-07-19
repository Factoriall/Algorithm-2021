#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int** matrix;
int N;
long long B;

int** dac(long long b);
int** square(int** m, bool isEven);//isEven: ���� ��� ����ϴ��� �ƴ� matrix�� ����ϴ��� Ȯ�� ����

int main() {
	scanf("%d %lld", &N, &B);

	matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++) {
			int num;
			scanf("%d", &num);
			if (num == 1000) matrix[i][j] = 0;//1000�� ��� 0���� �ٲ��༭ ���� ���� ��ġ��
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

int** dac(long long b) {//divide and conquer ��� �Լ�
	if (b == 1) return matrix;
	int** ret;
	if (b % 2 == 0) ret = square(dac(b / 2), true);
	else ret =  square(square(dac(b / 2), true), false);
	
	return ret;
}

int** square(int** m, bool isEven) {//��� �� �Լ�
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