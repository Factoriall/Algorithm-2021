#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;
bool isVisited[100001][1<<5];
vector<int> order;

struct PI {
	int weight;
	int cnt;
	int visited;
	PI(){}
	PI(int w, int c, int v) {
		weight = w;
		cnt = c;
		visited = v;
	}
};

struct pqComparator {
	bool operator()(PI a1, PI a2) {
		return a1.weight > a2.weight;
	}
};

typedef pair<int, int> P;

int getSide1(int n) {
	switch (n) {
	case 1: return 2;
	case 2: return 3;
	case 3: return 4;
	case 4: return 1;
	}
	return 5;
}

int getSide2(int n) {
	switch (n) {
	case 1: return 4;
	case 2: return 1;
	case 3: return 2;
	case 4: return 3;
	}
	return 5;
}

int getOpposite(int n) {
	switch (n) {
	case 1: return 3;
	case 2: return 4;
	case 3: return 1;
	case 4: return 2;
	}
	return 5;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	while (N != 0) {
		order.push_back(N);
		cin >> N;
	}

	priority_queue<PI, vector<PI>, pqComparator> pq;
	pq.push(PI(0, 0, 1));
	while (!pq.empty()) {
		PI now;
		do {
			now = pq.top();
			pq.pop();
		} while (!pq.empty() && isVisited[now.cnt][now.visited]);
		if (isVisited[now.cnt][now.visited]) break;
		isVisited[now.cnt][now.visited] = true;
		if (now.cnt == order.size()) {
			cout << now.weight;
			return 0;
		}

		int next = order[now.cnt];
		
		if ((now.visited & (1 << next)) != 0) pq.push(PI(now.weight + 1, now.cnt + 1, now.visited));//°°Àº Ä­ ¹â±â
		else {
			if ((now.visited & 1) == 1) {
				if (now.visited == 1) {
					pq.push(PI(now.weight + 2, now.cnt + 1, now.visited | (1 << next)));
					//cout << "put: " << now.weight + 2 << "," << now.cnt+1 << "," << 
				}
				else pq.push(PI(now.weight + 2, now.cnt + 1, (now.visited & ~(1 << 0)) | (1 << next)));
			}//Áß¾Ó Ä­ ¿Å±â±â
			int op = getOpposite(next);
			if ((now.visited & (1 << op)) != 0) {
				pq.push(PI(now.weight + 4, now.cnt + 1, (now.visited & ~(1 << op)) | (1 << next)));
			}
			int s1 = getSide1(next);
			if ((now.visited & (1 << s1)) != 0) {
				pq.push(PI(now.weight + 3, now.cnt + 1, (now.visited & ~(1 << s1)) | (1 << next)));
			}
			int s2 = getSide2(next);
			if ((now.visited & (1 << s2)) != 0) {
				pq.push(PI(now.weight + 3, now.cnt + 1, (now.visited & ~(1 << s2)) | (1 << next)));
			}
		}
	}
}

