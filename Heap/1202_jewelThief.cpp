#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> P;

struct weightAsending {
	bool operator()(P a1, P a2) {
		return a1.first > a2.first;
	}
};

struct valueDescending {
	bool operator()(P a1, P a2) {
		if(a1.second != a2.second)
			return a1.second < a2.second;
		return a1.first > a2.first;//value가 같을 시 용량이 작은 것 먼저
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	priority_queue<P, vector<P>, weightAsending> smallBag;
	priority_queue<P, vector<P>, valueDescending> highValue;

	for (int i = 0; i < N; i++) {
		int w, v;
		cin >> w >> v;
		smallBag.push(P(w, v));
	}

	vector<int> bags;
	for (int i = 0; i < K; i++) {
		int b;
		cin >> b;
		bags.push_back(b);
	}
	sort(bags.begin(), bags.end());

	long long answer = 0;
	for (int i = 0; i < K; i++) {
		//cout << bags[i] << " ";
		while (!smallBag.empty() && bags[i] >= smallBag.top().first) {
			highValue.push(smallBag.top());
			cout << "smallBag pop: " << smallBag.top().first << "," << smallBag.top().second << '\n';
			smallBag.pop();
		}

		if (highValue.empty()) continue;

		answer += highValue.top().second;
		highValue.pop();
	}

	cout << answer;
}