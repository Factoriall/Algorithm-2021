#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

struct Jewel {
	int x, y, v;
	Jewel(int x, int y, int v) {
		this->x = x;
		this->y = y;
		this->v = v;
	}
};

struct comparatorX {
	bool operator()(Jewel a, Jewel b) {
		return a.x > b.x;
	}
};

struct comparatorY {
	bool operator()(Jewel a, Jewel b) {
		return a.y < b.y;
	}
};

int main() {
	int N, C;
	scanf("%d %d", &N, &C);
	priority_queue<Jewel, vector<Jewel>, comparatorX> xpq;
	priority_queue<Jewel, vector<Jewel>, comparatorY> ypq;

	for (int i = 0; i < N; i++) {
		int x, y, v;
		scanf("%d %d %d", &x, &y, &v);
		xpq.push(Jewel(x, y, v));
	}

	long long answer = 0;
	long long sum = 0;
	while (!xpq.empty()) {
		Jewel top = xpq.top();
		//printf("in: %d %d %d\n", top.x, top.y, top.v);
		xpq.pop();
		sum += top.v;
		ypq.push(top);
		while (!xpq.empty() && top.x == xpq.top().x) {
			Jewel same = xpq.top();
			//printf("in: %d %d %d\n", same.x, same.y, same.v);
			xpq.pop();
			sum += same.v;
			ypq.push(same);
		}

		while (ypq.size() > C) {
			Jewel topY = ypq.top();
			//printf("out: %d %d %d\n", topY.x, topY.y, topY.v);
			ypq.pop();
			sum -= topY.v;
			while (!ypq.empty() && topY.y == ypq.top().y) {
				Jewel same = ypq.top();
				//printf("out: %d %d %d\n", same.x, same.y, same.v);
				sum -= same.v;
				ypq.pop();
			}
		}
		//printf("sum: %lld\n", sum);
		
		answer = max(answer, sum);
	}

	printf("%lld\n", answer);
}