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

//���������� ���� ���
void postTraverse(int s, int e) {
	if (s == e) return;
	int root = preorder[pIdx];
	int rIdx;//inorder �迭 �� root�� �´� Idx
	for (int i = s; i < e; i++) {//Ž��
		if (inorder[i] == root) {
			rIdx = i;
			break;
		}
	}
	pIdx++;//preorder�� �ε��� 1 ����
	postTraverse(s, rIdx);
	postTraverse(rIdx + 1, e);
	//����, ������ ��ȸ �� ���
	printf("%d ", root);
}