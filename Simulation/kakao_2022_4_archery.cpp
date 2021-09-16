#include <iostream>
// 여기에 문제 넣기
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

vector<int> solution(int n, vector<int> info) {
    //vector<int> answer;

    vector<int> idxs;
    for (int i = 0; i < 10; i++) {
        idxs.push_back(i);
    }

    int apeach = 0;
    for (int i = 0; i < 10; i++) {
        if (info[i] != 0) apeach += (10 - i);
    }

    int answer[11] = { 0 };
    int maxScore = -1;
    do {
        int cnt = 0;
        int ls = 0;
        int as = apeach;
        int idx = 0;
        int arr[11] = { 0 };

        while (idx < 10 && cnt + (info[idxs[idx]] + 1) <= n) {
            int ix = idxs[idx];
            ls += 10 - ix;
            if(info[ix] > 0) as -= 10 - ix;
            arr[ix] = info[ix] + 1;
            cnt += (info[ix] + 1);
            idx++;
        }
        arr[10] = n - cnt;
        
        if (ls < as) continue;
        
        if (maxScore < ls - as) {
            for (int i = 0; i <= 10; i++) answer[i] = arr[i];
            maxScore = ls - as;
        }
        else if (maxScore == ls) {
            for (int i = 10; i >= 0; i--) {
                if(answer[i] < arr[i]) {
                    for (int i = 0; i <= 10; i++) answer[i] = arr[i];
                    break;
                }
            }
        }

    } while (next_permutation(idxs.begin(), idxs.end()));
    if (maxScore == -1) return { -1 };
    else {
        vector<int> ret;
        for (int i = 0; i < 11; i++) ret.push_back(answer[i]);
        return ret;
    }
}

//
int main() {
    int n = 5;
    vector<int> info = { 2,1,1,1,0,0,0,0,0,0,0 };

    vector<int> answer = solution(n, info);

    for (int a : answer) cout << a << ' ';
}