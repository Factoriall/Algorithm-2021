#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int mn = 987654321;
int mx = 0;
void dfs(int N, int odd);

int main() {
	int N;
	scanf("%d", &N);
	dfs(N, 0);
	printf("%d %d\n", mn, mx);
}

void dfs(int N, int odd) {
	int tmp = N;
	int dNum = 0;
	while (tmp != 0) {
		if ((tmp % 10) & 1) {
			odd++;
		}
		dNum++;
		tmp /= 10;
	}
	if (dNum == 1) {
		mx = max(mx, odd);
		mn = min(mn, odd);
		return;
	}
	else if (dNum == 2) {
		dfs(N % 10 + N / 10, odd);
	}
	else {
		int m1 = 1;
		int n1, n2, n3;
		for (int i = 0; i < dNum - 2; i++) {
			m1 *= 10;
			n1 = N % m1;
			int m2 = m1;
			for (int j = i; j < dNum - 2; j++) {
				m2 *= 10;
				n2 = (N % m2) / m1;
				n3 = N / m2;
				dfs(n1 + n2 + n3, odd);
			}
		}
	}
}