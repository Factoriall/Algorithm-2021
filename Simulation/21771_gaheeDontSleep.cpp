#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
using namespace std;

int main() {
	int R, C;
	scanf("%d %d", &R, &C);
	int gr, gc, pr, pc;
	scanf("%d %d %d %d", &gr, &gc, &pr, &pc);

	int pillowSize = pr * pc;
	int pCnt = 0;
	for (int i = 0; i < R; i++) {
		char line[101];
		scanf("%s", line);
		for (int j = 0; j < C; j++) {
			if (line[j] == 'P') pCnt++;
		}
	}

	printf("%d\n", pCnt == pillowSize ? 0 : 1);
}