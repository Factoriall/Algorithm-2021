#include <iostream>
#include <algorithm>
using namespace std;

int memo[101][10001];
const int INF = 987654321;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	int memory[101];
	int cost[101];
	for (int i = 1; i <= N; i++) {
		cin >> memory[i];
	}
	for (int i = 1; i <= N; i++) {
		cin >> cost[i];
	}
	// i: �޸� �� cost���� ����� ���� ��
	// j: cost
	// memo[i][j]: i������ ���� �������� �� cost j���� ���� �� �ִ� �ִ� �޸�
	for (int i = 1; i <= N; i++) {
		int mSize = memory[i];
		int c = cost[i];
		for (int j = 1; j <= 10000; j++) {
			memo[i][j] = memo[i - 1][j];
			if (c <= j) memo[i][j] = max(memo[i][j], memo[i - 1][j - c] + mSize);
		}
	}

	//i������ ���� ��� �������� �� cost i ������ �ִ밪�� M�� ó�� �Ѵ� ������ ����
	for (int i = 1; i <= 10000; i++) {
		if (memo[N][i] >= M) {
			cout << i;
			break;
		}
	}
}