#include <iostream>
// 여기에 문제 넣기
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool isVisited[1 << 16];

struct QInfo {
    int bit;
    vector<int> parents;
    int sheepNum;
    int wolfNum;
    QInfo(int b, vector<int> p, int s, int w) {
        bit = b;
        parents = p;
        sheepNum = s;
        wolfNum = w;
    }
};

vector<int> childs[17];

int solution(vector<int> info, vector<vector<int>> edges) {
    for (vector<int> edge : edges) {
        childs[edge[0]].push_back(edge[1]);
    }

    queue<QInfo> q;
    q.push(QInfo(0, { 0 }, 1, 0));
    
    int answer = 1;
    while (!q.empty()) {
        QInfo inf = q.front();
        q.pop();

        if (answer < inf.sheepNum) answer = inf.sheepNum;
        /*
        for (int i = 0; i < inf.parents.size(); i++) {
            cout << inf.parents[i] << " ";
        }
        cout << '\n';
        cout << "sheepNum: " << inf.sheepNum << ", wolfNum: " << inf.wolfNum << ", bit:" << inf.bit << '\n';
        */
        for (int i = inf.parents.size() - 1; i >= 0; i--) {
            bool fin = true;
            int p = inf.parents[i];
            for (int c : childs[p]) {
                //cout << "child: " << c << '\n';
                if ((inf.bit & (1 << (c - 1))) == 0) {
                    fin = false;
                    break;
                }
            }
            if (fin) inf.parents.erase(inf.parents.begin() + i);
        }
        /*
        cout << "after: ";
        for (int i = 0; i < inf.parents.size(); i++) {
            cout << inf.parents[i] << " ";
        }
        cout << '\n';*/
       
        for (int p : inf.parents) {
            for (int c : childs[p]) {
                if ((inf.bit & (1 << (c - 1))) == 0) {//가지 않은 곳
                    bool isWolf = info[c] == 1;
                    if (isWolf && inf.sheepNum - inf.wolfNum == 1)//못 가는 곳
                        continue;
                    int nextBit = inf.bit | (1 << (c - 1));
                    if (isVisited[nextBit]) continue;
                    isVisited[nextBit] = true;
                    vector<int> nextParent = inf.parents;
                    nextParent.push_back(c);
                    q.push(QInfo(
                         nextBit,
                         nextParent,
                         inf.sheepNum + ((!isWolf) ? 1 : 0),
                         inf.wolfNum + ((isWolf) ? 1 : 0))
                    );
                }
            }
        }
    }
    
    return answer;
}

//
int main() {
    vector<int> info = { 0,0,1,1,1,0,1,0,1,0,1,1 };
    vector<vector<int>> edges = { {0,1} ,{1,2},{1,4},{0,8},{8,7},{9,10},
        {9,11},{4,3},{6,5},{4,6},{8,9} };

    cout << solution(info, edges);
}