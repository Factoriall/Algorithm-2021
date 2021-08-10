#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
using namespace std;

const int N = 100003, MOD = 1000000007;
int n, val[N];
vector<int> adj[N];

long long dfs(vector<long long> v, int s, int e);

int main() {

	scanf("%d", &n);
	//val 함수에 값 저장
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
	}

	//근접 수 adj에 저장
	for (int i = 0; i < n - 1; i++) {
		int s, e;
		scanf("%d %d", &s, &e);
		adj[s].push_back(e);
		adj[e].push_back(s);
	}
	printf("%lld\n", dfs({0,0,0,0,0,0,0,0,0,0}, 1, 0));
	
}


long long dfs(vector<long long> v, int s, int e) {
	long long cnt = 1;
	for (int i : v) {
		printf("%d ", i);
	}
	printf("\n");
	for(int i = 0; i <= val[s]; i++)
		cnt = (cnt + v[i]) % MOD;
	v[val[s]] = (v[val[s]] + cnt) % MOD;
	for (auto u : adj[s]) {
		if (u == e) continue;
		cnt = (cnt + dfs(v, u, s)) % MOD;
	}
	return cnt;
}