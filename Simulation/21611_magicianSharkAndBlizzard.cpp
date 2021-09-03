#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int dy[4] = { -1, 1, 0, 0 };
const int dx[4] = { 0, 0, -1, 1 };

int N, M;
int map[49][49];
typedef pair<int, int> P;

vector<P> syncIndex;

void syncMapWithIndex();
void moveAfterRemoved();
void printMap();
int popOrb();
void changeMap();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	syncMapWithIndex();
	/*for (P s : syncIndex) {
		cout << s.first << "," << s.second << '\n';
	}*/

	int answer = 0;
	for (int i = 0; i < M; i++) {
		int D, S;
		cin >> D >> S;
		D--;

		//제거
		int y = N / 2; int x = N / 2;
		for (int s = 0; s < S; s++) {
			y += dy[D]; x += dx[D];
			map[y][x] = 0;
		}
		//이동
		int pop;
		do{
			moveAfterRemoved();
			//cout << "After move\n";
			//printMap();
			pop = popOrb();
			answer += pop;
			//cout << "After pop\n";
			//printMap();
		} while (pop != 0);
		//cout << "Finish move\n";
		changeMap();
		//cout << "change map\n";
		//printMap();
	}
	cout << answer;
}

void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

void changeMap() {
	int popNum = 0;
	
	queue<P> change;
	int clusterNum = 0;
	for (P now : syncIndex) {
		int orbNum = map[now.first][now.second];
		if (orbNum == 0) break;

		if (popNum != orbNum) {
			if (clusterNum != 0) {
				change.push(P(clusterNum, popNum));
				clusterNum = 0;
			}
			popNum = orbNum;
		}
		clusterNum += 1;
	}
	change.push(P(clusterNum, popNum));

	int idx = 0;
	while (!change.empty() && idx < syncIndex.size()) {
		P now = change.front();
		map[syncIndex[idx].first][syncIndex[idx].second] = now.first;
		idx++;
		map[syncIndex[idx].first][syncIndex[idx].second] = now.second;
		idx++;
		change.pop();
	}
	for (int i = idx; i < syncIndex.size(); i++) {
		map[syncIndex[i].first][syncIndex[i].second] = 0;
	}
}

void syncMapWithIndex() {
	int y = N / 2; int x = N / 2;
	int lineNum = 1;
	bool upTiming = false;
	const int dirY[4] = { 0, 1, 0, -1 };
	const int dirX[4] = { -1, 0, 1, 0 };

	int dir = 0;
	bool finFlag = false;
	while (!finFlag) {
		for (int i = 0; i < lineNum; i++) {
			y += dirY[dir];
			x += dirX[dir];
			if (y < 0 || x < 0) {
				finFlag = true;
				break;
			}
			syncIndex.push_back(P(y, x));
		}
		dir = (dir + 1) % 4;
		if (upTiming) lineNum += 1;
		upTiming = !upTiming;
	}
}

void moveAfterRemoved() {
	int y = N / 2; int x = N / 2;
	int lineNum = 1;
	bool upTiming = false;
	queue<P> blanks;

	int dir = 0;
	int lastIdx = -1;

	for (int i = 0; i < syncIndex.size(); i++) {
		P now = syncIndex[i];
		int y = now.first; int x = now.second;
		if (map[y][x] == 0) {//이미 터진 것
			blanks.push(now);
			if (lastIdx == -1) lastIdx = i;
			else lastIdx++;
		}
		else if (!blanks.empty()) {
			P front = blanks.front();
			map[front.first][front.second] = map[y][x];
			map[y][x] = 0;
			blanks.pop();
			if (lastIdx != syncIndex.size() - 1) {
				blanks.push(syncIndex[++lastIdx]);
			}
		}
	}
}

int popOrb() {
	int popNum = 0;
	queue<P> clusters;
	int ret = 0;

	for (P now : syncIndex) {
		int orbNum = map[now.first][now.second];
		if (popNum != orbNum) {
			bool isPop = false;
			if (clusters.size() >= 4) {
				ret += clusters.size() * popNum;
				isPop = true;
			}
			popNum = orbNum;
			while (!clusters.empty()) {
				if(isPop) map[clusters.front().first][clusters.front().second] = 0;
				clusters.pop();
			}
		}
		clusters.push(now);
	}
	
	return ret;
}


