#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

priority_queue<int> fromBottom;
priority_queue<int, vector<int>, greater<int>> fromTop;

string solution(int n, int k, vector<string> cmd) {
    stack<int> garbage;
    for (int i = 0; i < k; i++) fromBottom.push(i);//밑에서 담는 pq
    for (int i = k + 1; i < n; i++) fromTop.push(i);//위부터 담는 pq
    int now = k;

    for (string cd : cmd) {
        char c = cd[0];
        if (c == 'U') {//위로 옮기기
            int move = stoi(cd.substr(2));
            while (move > 0) {
                fromTop.push(now);
                now = fromBottom.top();
                fromBottom.pop();
                move--;
            }
        }
        else if (c == 'D') {//아래로 옮기기
            int move = stoi(cd.substr(2));
            while (move > 0) {
                fromBottom.push(now);
                now = fromTop.top();
                fromTop.pop();
                move--;
            }
        }
        else if (c == 'C') {
            garbage.push(now);
            if (fromTop.empty()) {//위가 비어있음 아래로 내려감
                now = fromBottom.top();
                fromBottom.pop();
            }
            else {//그대로
                now = fromTop.top();
                fromTop.pop();
            }
        }
        else if (c == 'Z') {
            int recover = garbage.top();
            garbage.pop();
            if (recover < now) {//현재 위치보다 아래면 아래에 넣기
                fromBottom.push(recover);
            }
            else {//위에 넣기
                fromTop.push(recover);
            }
        }
    }
    string answer = "";

    for (int i = 0; i < n; i++) answer.push_back('O');
    while (!garbage.empty()) {
        int top = garbage.top();
        answer[top] = 'X';
        garbage.pop();
    }
    return answer;
}

int main() {
    int n = 8;
    int k = 2;
    vector<string> cmd = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C" };
    cout << solution(n, k, cmd);
}