#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

vector<int> foods;
long long memo[100001];

struct Cluster {
	int s, e, p;
	Cluster(int s, int e, int p) {
		this->s = s;
		this->e = e;
		this->p = p;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		foods.push_back(num);
	}

	queue<int> fq;
	int sum = 0;

	vector<Cluster> clusters;
	//투 포인터를 이용해서 clusters에 묶이는 값 저장
	for (int i = 0; i < N; i++) {
		sum += foods[i];
		fq.push(foods[i]);
		if (sum >= K) {
			clusters.push_back(Cluster(i + 1 - fq.size(), i + 1, sum - K));
		}
		while (!fq.empty() && sum>= K) {
			sum -= fq.front();
			fq.pop();
		}

	}

	int idx = 0;
	//다이나믹 프로그래밍 이용, bottom-up으로 올라가기
	//memo[k]: k까지의 먹이를 먹었을 때 얻을 수 있는 최대 에너지
	for (int i = 1; i <= N; i++) {
		//현재 클러스터의 끝에 도달못했다면 걍 전 것을 계승
		if (idx == clusters.size() || clusters[idx].e != i) {
			memo[i] = memo[i - 1];
			continue;
		}

		//끝에 닿았다면 
		//[이전 것]과 [현재 클러스터 + 클러스터 이전 묶음의 합]
		//비교해서 더 큰 것을 저장
		memo[i] = max(memo[i - 1], memo[clusters[idx].s] + clusters[idx].p);
		idx++;
	}
	cout << memo[N] << '\n';
}