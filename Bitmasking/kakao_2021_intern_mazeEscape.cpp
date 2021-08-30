#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = 987654321;

struct PQ {//PQ�� �� ������ ���
    int room;
    int distance;
    int trapBit;

    PQ(int r, int d, int tb) {
        room = r;
        distance = d;
        trapBit = tb;
    }
};

struct pqComparator {
    bool operator()(PQ p1, PQ  p2) {
        return p1.distance > p2.distance;
    }
};

struct Road {//�� ����
    int to;
    int distance;
    bool isForward;

    Road(int t, int d, bool isf) {
        to = t;
        distance = d;
        isForward = isf;
    }
};

bool isTrap(int now) {
    return (trapMap.find(now) != trapMap.end());
}

bool isTrapActivated(int now, int tb) {
    return (tb & (1 << (trapMap.find(now)->second))) != 0;
}

bool checkIfIsTrapAndActivated(int now, int tb) {
    return isTrap(now) && isTrapActivated(now, tb);
}


vector<Road> adj[1000];
map<int, int> trapMap;
typedef pair<int, int> P;

int dist[1000][1 << 10];
bool isVisited[1000][1 << 10];

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {

    for (vector<int> road: roads) {
        adj[road[0] - 1].push_back(Road(road[1] - 1, road[2], true));
        adj[road[1] - 1].push_back(Road(road[0] - 1, road[2], false));
    }

    int idx = 0;
    for (int trap : traps) {//trapMap�� ��ġ �� ���� Idx ����
        trapMap.insert(P(trap - 1, idx));
        idx++;
    }

    for(int i=0; i<1000; i++) for(int j=0; j< (1 << 10); j++) dist[i][j] = INF;//dist �ʱ�ȭ

    priority_queue<PQ, vector<PQ>, pqComparator> pq;
    start--; end--;
    pq.push(PQ(start, 0, 0));
    dist[start][0] = 0;
    
    //���ͽ�Ʈ�� ���� - ����
    while (!pq.empty()) {
        int now;
        int tb;

        do {
            now = pq.top().room;
            tb = pq.top().trapBit;
            pq.pop();
        } while (!pq.empty() && isVisited[now][tb]);
        if (isVisited[now][tb]) break;
        
        if (now == end) return dist[now][tb];
        isVisited[now][tb] = true;

        bool nowActivated = checkIfIsTrapAndActivated(now, tb); // ���� ��ġ���� Ʈ���� �ְ� �۵��ߴ°�?
        for (Road next : adj[now]) {
            bool nextActivated = checkIfIsTrapAndActivated(next.to, tb); // ���� ��ġ���� Ʈ���� �ְ� �۵��ߴ°�?

            //�� ���� ��ҿ� ������ �ƴ� �ٸ��� üũ
            bool isForward;
            if (!nowActivated && !nextActivated) isForward = true;
            else if (nowActivated && nextActivated) isForward = true;
            else isForward = false;

            if (next.isForward != isForward) continue; // �ݴ� ������ ����

            //���� trapBit ����
            int ntb = tb;
            if (isTrap(next.to)) {
                if (isTrapActivated(next.to, tb)) ntb = (tb & ~(1 << (trapMap.find(next.to)->second)));
                else ntb = (tb | (1 << (trapMap.find(next.to)->second)));
            }
            
            //dist ����
            if (dist[next.to][ntb] > dist[now][tb] + next.distance) {
                dist[next.to][ntb] = dist[now][tb] + next.distance;
                pq.push(PQ(next.to, dist[next.to][ntb], ntb));
            }
        }
    }
    
    return -1;
}

int main() {
    int n = 3;
    int start = 1;
    int end = 3;
    vector <vector<int>> roads = { {1, 2, 2},{3, 2, 3 } };
    vector<int> traps = { 2 };
    cout << solution(n, start, end, roads, traps);

}
