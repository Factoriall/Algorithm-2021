#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> adj[20001];
bool isVisited[20001];

int solution(int n, vector<vector<int>> edge) {
    for (vector<int> e : edge) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    queue<int> q;
    q.push(1);
    isVisited[1] = true;
    //간단한 BFS 사용해서 제일 깊은 깊이의 qSize return
    while (!q.empty()) {
        int qSize = q.size();
        bool isFinished = true;
        for (int T = 0; T < qSize; T++) {
            int now = q.front();
            q.pop();
            for (int next : adj[now]) {
                if (!isVisited[next]) {
                    isFinished = false;
                    isVisited[next] = true;
                    q.push(next);
                }
            }
        }
        if (isFinished) return qSize;
    }

    return -1;
}

int main() {
    int n = 6;
    vector<vector<int>> vertex = { {3, 6} ,{4, 3},{3, 2},{1, 3},{1, 2},{2, 4},{5, 2} };
    cout << solution(n, vertex);
}