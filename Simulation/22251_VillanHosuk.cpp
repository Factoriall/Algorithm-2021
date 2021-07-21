#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int displayOn[10][7] = { // 켜져있는 부분 표시
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

	//displayOn의 차이를 조사해서 반전되는 총 개수를 저장
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
	getArrayOfDigits(X, elevatorNum);//elevatorNum에 자리 수 저장

	int answer = 0;
	for (i = 1; i <= N; i++) {
		if (i == X) continue;//같으면 할 필요 없음
		int villanNum[6];
		fill(villanNum, villanNum + 6, 0);
		getArrayOfDigits(i, villanNum);//배열에 자리수 저장

		int inverseCnt = 0;
		for (int i = 0; i < K; i++) {
			inverseCnt += inverseNum[elevatorNum[i]][villanNum[i]];//반전에 필요한 수 더하기
		}

		if (inverseCnt <= P) answer++;//실제보다 적으면 카운트
	}

	printf("%d\n", answer);
}

void getArrayOfDigits(int n, int arr[6]) {//배열에 숫자 한자리씩 넣는 함수
	int num = n;
	int idx = 0;
	while (num > 0) {
		arr[idx++] = num % 10;
		num /= 10;
	}
}