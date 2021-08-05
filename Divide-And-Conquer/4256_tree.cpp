#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 1000;
int preorder[MAX];
int inorder[MAX];
int n;
int pIdx;
void postTraverse(int s, int e);

int main() {
	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d", &preorder[i]);
		}

		for (int i = 0; i < n; i++) {
			scanf("%d", &inorder[i]);
		}

		pIdx = 0;
		postTraverse(0, n);
		printf("\n");
	}
}

//분할정복을 통한 재귀
void postTraverse(int s, int e) {
	if (s == e) return;
	int root = preorder[pIdx];
	int rIdx;//inorder 배열 중 root와 맞는 Idx
	for (int i = s; i < e; i++) {//탐색
		if (inorder[i] == root) {
			rIdx = i;
			break;
		}
	}
	pIdx++;//preorder의 인덱스 1 증갗
	postTraverse(s, rIdx);
	postTraverse(rIdx + 1, e);
	//왼쪽, 오른쪽 순회 후 출력
	printf("%d ", root);
}