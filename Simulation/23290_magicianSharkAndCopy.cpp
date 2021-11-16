#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> P;

const int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int sy[4] = { -1, 0, 1, 0 };
const int sx[4] = { 0, -1, 0, 1 };
int M, S;

vector<int> fishMap[4][4];
vector<int> spells[4][4];
P shark;
P smells[4][4];

void createSpell();
void fishMove();
void sharkMove(int year);
void removeSmell(int year);
void completeSpell();
bool isOutOfRange(int y, int x);
void printStatus();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		x--; y--; d--;
		fishMap[x][y].push_back(d);
	}
	int x, y;
	cin >> x >> y;
	x--; y--;
	shark = P(x, y);

	for (int T = 0; T < S; T++) {
		//cout << "year:" << T << '\n';
		//1. ¾Ë »ý¼º
		createSpell();
		//printStatus();
		fishMove();
		//printStatus();
		sharkMove(T);
		//printStatus();
		removeSmell(T);
		//printStatus();
		completeSpell();
		//printStatus();
	}

	int answer = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer += fishMap[i][j].size();
		}
	}
	cout << answer;
}

void createSpell() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for(int f : fishMap[i][j]) spells[i][j].push_back(f);
		}
	}
}

void fishMove() {
	vector<int> nextMap[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int f : fishMap[i][j]) {
				int cnt = 0;
				int dir = f;
				while(cnt < 8) {
					
					int ny = i + dy[dir];
					int nx = j + dx[dir];

					if (isOutOfRange(ny, nx) || (ny == shark.first && nx == shark.second) || smells[ny][nx].first != 0) {
						cnt++;
						dir--;
						if (dir < 0) dir = 7;
						continue;
					}

					nextMap[ny][nx].push_back(dir);
					break;
				}
				if(cnt == 8) nextMap[i][j].push_back(f);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fishMap[i][j].clear();
			for (int f : nextMap[i][j]) fishMap[i][j].push_back(f);
		}
	}
}

void sharkMove(int year) {
	int y = shark.first;
	int x = shark.second;
	vector<P> finRoute;

	int maxNum = -1;
	int sum = 0;
	int fishNum[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fishNum[i][j] = fishMap[i][j].size();
		}
	}

	for(int d1 = 0; d1 < 4; d1++){
		int ny1 = y + sy[d1];
		int nx1 = x + sx[d1];
		if (isOutOfRange(ny1, nx1)) continue;
		int tmp1 = fishNum[ny1][nx1];
		sum += tmp1;
		fishNum[ny1][nx1] = 0;

		for (int d2 = 0; d2 < 4; d2++) {
			int ny2 = ny1 + sy[d2];
			int nx2 = nx1 + sx[d2];
			if (isOutOfRange(ny2, nx2)) continue;
			int tmp2 = fishNum[ny2][nx2];
			sum += tmp2;
			fishNum[ny2][nx2] = 0;

			for (int d3 = 0; d3 < 4; d3++) {
				int ny3 = ny2 + sy[d3];
				int nx3 = nx2 + sx[d3];
				if (isOutOfRange(ny3, nx3)) continue;
				int tmp3 = fishNum[ny3][nx3];
				sum += tmp3;
				fishNum[ny3][nx3] = 0;

				if (maxNum < sum) {
					maxNum = sum;
					finRoute.clear();
					finRoute.push_back(P(ny1, nx1));
					finRoute.push_back(P(ny2, nx2));
					finRoute.push_back(P(ny3, nx3));
				}
				fishNum[ny3][nx3] = tmp3;
				sum -= fishNum[ny3][nx3];
			}
			fishNum[ny2][nx2] = tmp2;
			sum -= fishNum[ny2][nx2];
		}
		fishNum[ny1][nx1] = tmp1;
		sum -= tmp1;
	}

	for (P die : finRoute) {
		if (fishMap[die.first][die.second].size() > 0) {
			smells[die.first][die.second] = P(1, year);
			fishMap[die.first][die.second].clear();
		}
	}
	shark = finRoute[2];
}

void removeSmell(int year) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (smells[i][j].first == 1 && smells[i][j].second + 2 <= year) {
				smells[i][j] = P(0, 0);
			}
		}
	}
}

void completeSpell() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int t : spells[i][j]) {
				fishMap[i][j].push_back(t);
			}
			spells[i][j].clear();
		}
	}
}

void printStatus() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << i << "," << j << ": ";
			for (int f : fishMap[i][j]) {
				string c;
				switch (f) {
				case 0:
					c = "¡ç";
					break;
				case 1:
					c = "¢Ø";
					break;
				case 2:
					c = "¡è";
					break;
				case 3:
					c = "¢Ö";
					break;
				case 4:
					c = "¡æ";
					break;
				case 5:
					c = "¢Ù";
					break;
				case 6:
					c = "¡é";
					break;
				case 7:
					c = "¢×";
					break;
				}
				cout << c << " ";

			}
			cout << '\n';
		}
		cout << '\n';
	}
	
	cout << "shark: (" << shark.first << "," << shark.second << ")\n";
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "(" << smells[i][j].first << ", "
				<< smells[i][j].second << ") ";
		}
		cout << '\n';
	}
	cout << '\n';
}

bool isOutOfRange(int y, int x) {
	return y < 0 || x < 0 || y >= 4 || x >= 4;
}