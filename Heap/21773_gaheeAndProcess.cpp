#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Process {
public:
	int pid;
	int remain;
	int prior;

	Process(int p, int r, int pr) {
		pid = p;
		remain = r;
		prior = pr;
	}
};

struct myComparator{
	bool operator()(Process p1, Process p2) {
		if (p1.prior != p2.prior)
			return p1.prior < p2.prior;
		return p1.pid > p2.pid;
	}
};



int main() {
	int T, n;
	scanf("%d %d", &T, &n);

	priority_queue<Process, vector<Process>, myComparator> pq;
	for (int i = 0; i < n; i++) {
		int pid, rem, pri;
		scanf("%d %d %d", &pid, &rem, &pri);
		pq.push(Process(pid, rem, pri));
	}

	int cnt = 0;
	while (!pq.empty() && cnt < T) {
		Process top = pq.top();
		printf("%d\n", top.pid);
		pq.pop();
		top.remain--;
		top.prior--;
		if (top.remain != 0)
			pq.push(top);
		
		cnt++;
	}
}
