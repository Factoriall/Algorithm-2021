#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef pair<string, int> P;
map<string, int> m[11];

void dfs(int s, int maxLen, string order, string str);

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    for (int c : course) {
        for (string o : orders) {
            dfs(0, c, o, "");
        }

        int maxNum = 2;
        vector<string> ans;
        for (auto const& imap : m[c]) {
            if (imap.second > maxNum) {
                ans.clear();
                ans.push_back(imap.first);
                maxNum = imap.second;
            }
            else if (imap.second == maxNum) {
                ans.push_back(imap.first);
            }
        }
        for (string a : ans) answer.push_back(a);
    }
    sort(answer.begin(), answer.end());
    return answer;
}

int main() {
    vector<string> orders = { "XYZ", "XWY", "WXA" };
    vector<int> course = { 2,3,4 };
    vector<string> answer = solution(orders, course);
    for (string ans : answer) {
        cout << ans << '\n';
    }
}

void dfs(int s, int maxLen, string order, string str) {
    if (str.length() == maxLen) {
        if (m[maxLen].find(str) == m[maxLen].end()) {
            sort(str.begin(), str.end());
            m[maxLen].insert(P(str, 1));
        }
        else m[maxLen].find(str)->second += 1;
    }
    int len = order.length();
    for (int i = s; i < len; i++) {
        str += order[i];
        dfs(i + 1, maxLen, order, str);
        str = str.substr(0, str.length() - 1);
    }
}