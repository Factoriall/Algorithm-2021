#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 300'000;
int memo[MAX][2];
vector<int> sale;
vector<int> adj[MAX];

int dp(int now, int isTopUsed) {
    if (memo[now][isTopUsed] != -1) return memo[now][isTopUsed];

    int minSalary = sale[now];
    int ret = 0;
    for (int down : adj[now]) {
        minSalary = min(minSalary, sale[down]);
        if (adj[down].size() != 0) {
            ret += dp(down, 0); 
        }
    }
    if(isTopUsed) memo[now][isTopUsed] = ret + sale[now];
    else {
        memo[now][isTopUsed] = ret + minSalary;
        for (int down : adj[now]) {
            if (adj[down].size() != 0) {
                memo[now][isTopUsed] = min(memo[now][isTopUsed], ret - dp(down, 0) + dp(down, 1));
            }
        }
    }
    cout << now << "," << isTopUsed << ": " << memo[now][isTopUsed] << '\n';

    return memo[now][isTopUsed];
}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    sale = sales;
    for (vector<int> link : links) {
        int up = link[0] - 1;
        int down = link[1] - 1;
        adj[up].push_back(down);
    }

    memset(memo, -1, sizeof(memo));
    answer = min(dp(0, 0), dp(0, 1));

    return answer;
}

int main() {
    vector<int> sales = { 14, 17, 15, 18, 19, 14, 13, 16, 28, 17 };
    vector<vector<int>> links = { {10, 8},{1, 9},{9, 7},{5, 4},{1, 5},{5, 10},{10, 6},{1, 3},{10, 2} };
    cout << solution(sales, links);
}