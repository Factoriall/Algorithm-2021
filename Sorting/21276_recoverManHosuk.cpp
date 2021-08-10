#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> names;
vector<int> descendants[1000];
vector<int> jikgye[1000];
map<string, int> nameIdxs;

typedef pair<string, int> P;

int main() {
	int N, M;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		string name;
		cin >> name;
		names.push_back(name);
	}
	sort(names.begin(), names.end());
	int idx = 0;
	for (string name : names) {
		nameIdxs.insert(P(name, idx++));
	}

	int indegree[1000];
	fill(indegree, indegree + 1000, 0);

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		string desc;
		string anc;
		cin >> desc >> anc;
		int dIdx = nameIdxs.find(desc)->second;
		int aIdx = nameIdxs.find(anc)->second;

		descendants[aIdx].push_back(dIdx);
		indegree[dIdx]++;
	}

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (indegree[i] == 0) {
			cnt++;
		}
	}
	printf("%d\n", cnt);
	queue<int> q;
	for (int i = 0; i < N; i++) {
		if (indegree[i] == 0) {
			q.push(i);
			cout << names[i] << " ";
		}
	}
	printf("\n");

	while (!q.empty()) {
		int nIdx = q.front();
		q.pop();
		for (int dIdx : descendants[nIdx]) {
			indegree[dIdx]--;
			if (indegree[dIdx] == 0) {
				jikgye[nIdx].push_back(dIdx);
				q.push(dIdx);
			}
		}
	}

	idx = 0;
	for (string name : names) {
		cout << name << " " << jikgye[idx].size() << " ";
		sort(jikgye[idx].begin(), jikgye[idx].end());
		for (int n : jikgye[idx]) {
			cout << names[n] << " ";
		}
		printf("\n");
		idx++;
	}
}
