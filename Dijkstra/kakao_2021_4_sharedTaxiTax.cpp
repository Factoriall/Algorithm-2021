#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 987654321;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int dist[201][201];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = i == j ? 0 : INF;
        
    for (vector<int> fare : fares) {
        int c1 = fare[0];
        int c2 = fare[1];
        int w = fare[2];
        dist[c1][c2] = min(dist[c1][c2], w);
        dist[c2][c1] = min(dist[c2][c1], w);
    }

   

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int minDist = INF;
    for (int i = 1; i <= n; i++) {
        if (dist[s][i] == INF || dist[i][a] == INF || dist[i][b] == INF) continue;
        minDist = min(minDist, dist[s][i] + dist[i][a] + dist[i][b]);
    }

    return minDist;
}

int main() {
    int n = 6;
    int s = 4;
    int a = 6;
    int b = 2;
    vector<vector<int>> fares = { {4, 1, 10},{3, 5, 24},{5, 6, 2 }, { 3, 1, 41 }, { 5, 1, 24 }, { 4, 6, 50 }, { 2, 4, 66 }, { 2, 3, 22 }, { 1, 6, 25 } };
    
    cout << solution(n, s, a, b, fares);

}