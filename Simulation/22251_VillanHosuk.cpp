#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int displayOn[10][7] = { // �����ִ� �κ� ǥ��
	{0, 0, 0, 1, 0, 0, 0},
	{1, 1, 0, 1, 1, 0, 1},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 0, 0},
	{1, 0, 0, 0, 1, 0, 1},
	{0, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 0, 1},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0}
};

int inverseNum[10][10];
void getArrayOfDigits(int n, int arr[6]);

int main() {
	int i, j;

	//displayOn�� ���̸� �����ؼ� �����Ǵ� �� ������ ����
	for (i = 0; i < 10; i++) {
		for (j = i; j < 10; j++) {
			int& inverse = inverseNum[i][j];
			if (i == j) inverse = 0;
			else {
				int cnt = 0;
				for (int t = 0; t < 7; t++) {
					if (displayOn[i][t] != displayOn[j][t]) cnt++;
				}
				inverse = cnt;
				inverseNum[j][i] = cnt;
			}
		}
	}

	int N, K, P, X;
	scanf("%d %d %d %d", &N, &K, &P, &X);
	
	int elevatorNum[6];
	fill(elevatorNum, elevatorNum + 6, 0);
	getArrayOfDigits(X, elevatorNum);//elevatorNum�� �ڸ� �� ����

	int answer = 0;
	for (i = 1; i <= N; i++) {
		if (i == X) continue;//������ �� �ʿ� ����
		int villanNum[6];
		fill(villanNum, villanNum + 6, 0);
		getArrayOfDigits(i, villanNum);//�迭�� �ڸ��� ����

		int inverseCnt = 0;
		for (int i = 0; i < K; i++) {
			inverseCnt += inverseNum[elevatorNum[i]][villanNum[i]];//������ �ʿ��� �� ���ϱ�
		}

		if (inverseCnt <= P) answer++;//�������� ������ ī��Ʈ
	}

	printf("%d\n", answer);
}

void getArrayOfDigits(int n, int arr[6]) {//�迭�� ���� ���ڸ��� �ִ� �Լ�
	int num = n;
	int idx = 0;
	while (num > 0) {
		arr[idx++] = num % 10;
		num /= 10;
	}
}