#include <iostream>
using namespace std;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int N, M, K;
int map[20][20];

bool isOutOfRange(int y, int x);
int getScore(int y, int x);
int dfs(int y, int x, int num, bool isVisited[20][20]);

class Dice {
public:
	int top, bottom, left, right, front, back;
	int dir;
	int y, x;
	Dice(int t, int bo, int l, int r, int f, int ba, int d, int y, int x) {
		top = t;
		bottom = bo;
		left = l;
		right = r;
		front = f;
		back = ba;
		dir = d;
		this->y = y;
		this->x = x;
	}

	void roll() {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (isOutOfRange(ny, nx)) {
			ny = y - dy[dir];
			nx = x - dx[dir];
			dir = dir >= 2 ? dir - 2 : dir + 2;
		}
		y = ny;
		x = nx;
		int tmp = top;
		switch (dir) {
			
		case 0://ºÏ
			top = front;
			front = bottom;
			bottom = back;
			back = tmp;
			break;
		case 1://µ¿
			top = left;
			left = bottom;
			bottom = right;
			right = tmp;
			break;
		case 2://³²
			top = back;
			back = bottom;
			bottom = front;
			front = tmp;
			break;
		case 3://¼­
			top = right;
			right = bottom;
			bottom = left;
			left = tmp;
			break;
		}
	}

	void changeDir() {
		if (bottom > map[y][x]) dir = dir != 3 ? dir + 1 : 0;
		else if (bottom < map[y][x]) dir = dir != 0 ? dir - 1 : 3;
	}

	void printStatus() {
		cout << "top: " << top << '\n';
		cout << "bottom: " << bottom << '\n';
		cout << "left: " << left << '\n';
		cout << "right: " << right << '\n';
		cout << "front: " << front << '\n';
		cout << "back: " << back << '\n';
		cout << "dir: " << dir << '\n';
		cout << "location: (" << y << "," << x << ")\n";
		cout << "isOn: " << map[y][x] << '\n';
		cout << '\n';
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	Dice dice = Dice(1, 6, 4, 3, 5, 2, 1, 0, 0);
	int sum = 0;
	for (int T = 0; T < K; T++) {
		dice.roll();
		//dice.printStatus();
		sum += getScore(dice.y, dice.x);
		dice.changeDir();
		//dice.printStatus();
	}
	cout << sum;
}

int getScore(int y, int x) {
	bool isVisited[20][20];
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) isVisited[i][j] = false;

	isVisited[y][x] = true;
	int related = (1 + dfs(y, x, map[y][x], isVisited));
	//cout << "same: " << related << '\n';
	return map[y][x] * related;
}

int dfs(int y, int x, int num, bool isVisited[20][20]) {
	int ret = 0;
	for (int d = 0; d < 4; d++) {
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (!isOutOfRange(ny, nx) && !isVisited[ny][nx] 
			&& num == map[ny][nx]) {
			isVisited[ny][nx] = true;
			ret += 1 + dfs(ny, nx, num, isVisited);
		}
	}
	return ret;
}

bool isOutOfRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}