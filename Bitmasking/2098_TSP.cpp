#include <iostream>
#include <queue>
using namespace std;

const int INF = 987654321;
int memo[16][1 << 16];
int N;
int dist[16][16];
vector<int> bitCnts[17];

int getBitCount(int num);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> dist[i][j];
		}
	}

	for (int i = 0; i < (1 << N); i++) {
		bitCnts[getBitCount(i)].push_back(i);
		//cout << bitCnt[i] << '\n';
	}
	/*
	for (int i = 0; i <= N; i++) {
		cout << i << ": ";
		for (int idx : bitCnts[i]) cout << idx << " ";
		cout << '\n';
	}*/

	for (int i = 0; i < N; i++) {
		fill(memo[i], memo[i] + (1 << 16), INF);
	}

	for (int i = 1; i < N; i++) {
		if (dist[0][i] == 0) continue;
		memo[i][1 << i] = dist[0][i];
	}
	
	//memo - i: 현위치, j: visited 정보
	int cnt = 1;
	while (cnt < N) {
		for (int idx : bitCnts[cnt]) {
			//cout << "idx:" << idx << '\n';
			
			for (int i = 1; i < N; i++) {//i:현재 위치
				if ((idx & (1 << i)) == 0) continue;
				if (cnt == N - 1) {
					if (dist[i][0] == 0) continue;
					//cout << "memo: " << memo[i][idx] << '\n';
					memo[0][(1 << N) - 1] = min(memo[0][(1 << N) - 1], memo[i][idx] + dist[i][0]);
					//cout << i << "~0: " << memo[0][(1 << N) - 1] << '\n';
					continue;
				}


				for (int j = 1; j < N; j++) {//j:다음 위치
					if ((idx & (1 << j)) != 0) continue;
					if (dist[i][j] == 0) continue;
					
					memo[j][idx | (1 << j)] = min(memo[j][idx | (1 << j)], memo[i][idx] + dist[i][j]);
					//cout << i << "~" << j << ": " << (idx | (1 << j)) << ", weight: " << memo[j][idx | (1 << j)] << '\n';
				}
			}
		}
		cnt++;
	}
	cout << memo[0][(1 << N) - 1];
}

int getBitCount(int num){
	int ret = 0;
	while (num != 0) {
		if (num & 1) ret++;
		num = num >> 1;
	}
	return ret;
}