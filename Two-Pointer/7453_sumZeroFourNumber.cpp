#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int MAX_CAP = 4000;

priority_queue<int, vector<int>, greater<int>> pqAB;
priority_queue<int> pqCD;

int A[MAX_CAP];
int B[MAX_CAP];
int C[MAX_CAP];
int D[MAX_CAP];

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			pqAB.push(A[i] + B[j]);
			pqCD.push(C[i] + D[j]);
		}
	}

	int ab = pqAB.top();
	int cd = pqCD.top();
	pqAB.pop();//작은 거부터
	pqCD.pop();//큰 거부터

	bool isFinished = false;
	long long answer = 0;
	while (!pqAB.empty() && !pqCD.empty()) {
		printf("%d %d\n", ab, cd);
		if (ab + cd > 0) {
			cd = pqCD.top();
			pqCD.pop();
		}
		else if (ab + cd < 0) {
			ab = pqAB.top();
			pqAB.pop();
		}
		else {
			long long dup1 = 1;
			long long dup2 = 1;
			while (!pqAB.empty() && pqAB.top() == ab) {
				dup1++;
				pqAB.pop();
			}
			while (!pqCD.empty() && pqCD.top() == cd) {
				dup2++;
				pqCD.pop();
			}
			answer += (dup1 * dup2);
			if (pqAB.empty() || pqCD.empty()) {
				isFinished = true;
				break;//여기선 이미 처리 상태
			}

			if (pqAB.top() - ab < cd - pqCD.top()) {
				ab = pqAB.top();
				pqAB.pop();
			}
			else{
				cd = pqCD.top();
				pqCD.pop();
			}
		}
	}

	if (!isFinished && ab + cd == 0) answer++;
	printf("%d %d\n", pqAB.size(), pqCD.size());

	if (pqAB.empty()) {
		while (!pqCD.empty()) {
			cd = pqCD.top();
			pqCD.pop();
			if (ab + cd == 0) answer++;
		}
	}
	else {
		while (!pqAB.empty()) {
			ab = pqAB.top();
			pqAB.pop();
			if (ab + cd == 0) answer++;
		}
	}

	printf("%lld\n", answer);
}