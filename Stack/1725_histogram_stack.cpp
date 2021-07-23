#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

class Stick {
public:
	int idx;
	int height;
	Stick(int i, int h) {
		idx = i;
		height = h;
	}
};

int histogram[100000];

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &histogram[i]);
	}
	int answer = 0;
	stack<Stick> st;
	for (int i = 0; i < N; i++) {
		while (!st.empty() && st.top().height > histogram[i]) {
			Stick s = st.top();
			st.pop();

			int width;
			if (st.empty()) width = i;
			else width = i - s.idx;
			answer = max(answer, width * s.height);
		}
		st.push(Stick(i, histogram[i]));
	}
	while (!st.empty()) {
		int height = st.top().height;
		st.pop();
		int width;
		if (!st.empty()) width = N - st.top().idx - 1;
		else width = N;
		answer = max(answer, width * height);
	}
	printf("%d\n", answer);
}