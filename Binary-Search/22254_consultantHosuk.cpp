#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

const int MAX = 100000;
int presentTime[MAX];
int N, X;
bool isPossibleToMake(int cNum);

int main() {
	scanf("%d %d", &N, &X);
	for (int i = 0; i < N; i++) {
		scanf("%d", &presentTime[i]);
	}

	//�̺� Ž���� �̿��ؼ� ������ ������ �ּ� ���� ������ ����
	int lo = 0;
	int hi = N + 1;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (isPossibleToMake(mid)) hi = mid;
		else lo = mid;
	}
	printf("%d\n", hi);
}

bool isPossibleToMake(int cNum) {
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < cNum; i++) pq.push(0);//������ŭ pq�� �ֱ�
	
	int pIdx = 0;
	while (pIdx < N) {
		int least = pq.top();
		pq.pop();
		int added = least + presentTime[pIdx++];
		if (added > X) return false;//���� ���� ���� �Ϳ� ���� �� �Ѿ�� cut
		pq.push(added);
	}
	return true;

}
