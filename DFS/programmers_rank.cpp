#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef pair<int, bool> P;
vector<P> matchResult[100];
int dfs(int now, bool isWinning, bool isVisited[]);

int solution(int n, vector<vector<int>> results) {
    for (vector<int> result : results) {
        int wIdx = result[0] - 1;
        int lIdx = result[1] - 1;

        matchResult[wIdx].push_back(P(lIdx, true));
        matchResult[lIdx].push_back(P(wIdx, false));
    }

    int answer = 0;
    for (int i = 0; i < n; i++) {
        bool isVisited[100] = { false };

        int win = 0;
        int lose = 0;
        for (P vs : matchResult[i]) {
            if (vs.second) win += dfs(vs.first, true, isVisited);//이긴 팀의 수 확인
            else lose += dfs(vs.first, false, isVisited);//진 팀의 수 확인
        }
        if (win + lose == n - 1) answer++;//다 합해서 자신을 제외한 사람 수라면 순위 특정 가능
    }

    return answer;
}

//dfs 접근, 대신 isWinning으로 순위 방향 확인해서 맞는 방향만 접근
int dfs(int now, bool isWinning, bool isVisited[]) {
    if (isVisited[now]) return 0;
    isVisited[now] = true;
    int ret = 1;
    for (P vs : matchResult[now]) {
        if (vs.second == isWinning) {
            ret += dfs(vs.first, isWinning, isVisited);
        }
    }
    return ret;
}

int main() {
    int n = 5;
    vector<vector<int>> results = { {4, 3},{4, 2},{3, 2},{1, 2},{2, 5 } };   
    cout << solution(n, results);
}