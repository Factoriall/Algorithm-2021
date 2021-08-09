#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

bool p1[50][50];
bool p2[50][50];
int n2, m2;
void rotateP2();

int main() {
	int n1, m1;
	scanf("%d %d", &n1, &m1);
	for (int i = 0; i < n1; i++) {
		char line[51];
		scanf("%s", line);
		for (int j = 0; j < m1; j++) {
			p1[i][j] = (line[j] == '1');
		}
	}

	scanf("%d %d", &n2, &m2);
	for (int i = 0; i < n2; i++) {
		char line[51];
		scanf("%s", line);
		for (int j = 0; j < m2; j++) {
			p2[i][j] = (line[j] == '1');
		}
	}

	int answer = 987654321;
	answer = min(answer, max(n1, n2) * (m1 + m2));
	answer = min(answer, (n1 + n2) * max(m1, m2));
	for (int d = 0; d < 4; d++) {
		for (int i = 1; i < n1 + n2; i++) {
			for (int j = 1; j < m1 + m2; j++) {
				bool fullMap[150][150] = { false };
				for (int n = n2; n < n2 + n1; n++) {
					for (int m = m2; m < m1 + m2; m++) {
						fullMap[n][m] = p1[n - n2][m - m2];
					}
				}
				bool isNotFit = false;
				for (int si = i; si < i + n2; si++) {
					for (int sj = j; sj < j + m2; sj++) {
						if (fullMap[si][sj] && p2[si - i][sj - j]) {
							isNotFit = true;
							break;
						}
						else if (!fullMap[si][sj] && p2[si - i][sj - j]) {
							fullMap[si][sj] = true;
						}
					}
				}
				if (!isNotFit) {
					int si = 150;
					int sj = 150;
					int ei = 0;
					int ej = 0;
					for (int n = 1; n < 150; n++) {
						for (int m = 1; m < 150; m++) {
							//printf("%d", fullMap[n][m] ? 1 : 0);
							if (fullMap[n][m]) {
								si = min(si, n);
								sj = min(sj, m);
								ei = max(ei, n);
								ej = max(ej, m);
							}
						}
						//printf("\n");
					}
					//printf("h: %d, w: %d\n", (ei - si + 1), (ej - sj + 1));
					answer = min(answer, (ei - si + 1) * (ej - sj + 1));
				}
			}
		}

		rotateP2();//문제 없음
	}

	printf("%d\n", answer);
}

void rotateP2() {
	bool rotate[50][50];

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < m2; j++) {
			rotate[j][n2 - 1 - i] = p2[i][j];
		}
	}


	int n = max(n2, m2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			p2[i][j] = rotate[i][j];
		}
	}

	int tmp = n2;
	n2 = m2;
	m2 = tmp;

	/*
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < m2; j++) {
			printf("%d", p2[i][j] ? 1 : 0);
		}
		printf("\n");
	}
	printf("\n");*/
}