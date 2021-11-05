#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, C;
int houses[200000];

bool isPossibleToInstall(int num);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> C;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		houses[i] = n;
	}

	sort(houses, houses + N);

	int lo = -1;
	int hi = 1'000'000'001;
	while (lo+1 < hi) {
		int mid = (hi + lo) / 2;
		if (isPossibleToInstall(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo;
}

bool isPossibleToInstall(int pvt) {
	int now = 0;
	int cnt = 1;
	int next = 1;
	while (cnt < C && next < N) {
		int dist = houses[next] - houses[now];
		if (dist >= pvt) {
			now = next;
			cnt += 1;
		}
		next++;
	}
	if (cnt == C) return true;
	return false;
}