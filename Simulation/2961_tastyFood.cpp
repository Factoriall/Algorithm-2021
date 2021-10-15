#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1'234'567'890;
int N;
int bitter[10];
int sour[10];
int answer = INF;

void dfs(int n, int s, int b);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> sour[i] >> bitter[i];
	}
	dfs(0, 1, 0);

	cout << answer;
}

void dfs(int n, int s, int b) {
	if (n != 0) answer = min(answer, abs(s - b));
	
	for (int i = n; i < N; i++) {
		dfs(i + 1, s * sour[i], b + bitter[i]);
	}
}