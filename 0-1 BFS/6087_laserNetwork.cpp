#include <iostream>
#include <deque>
using namespace std;

typedef pair<int, int> P;
int W, H;

char map[100][100];
bool isVisited[100][100][4];

int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, 1, 0, -1 };

struct Point {
	int y, x;
	int dir;
	int reflect;

	Point(int y, int x, int d, int r) {
		this->y = y;
		this->x = x;
		dir = d;
		reflect = r;
	}
};


bool isOutOfRange(int y, int x);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> W >> H;

	P start = P(-1, -1);
	for (int i = 0; i < H; i++) {
		string str;
		cin >> str;

		for (int j = 0; j < W; j++) {
			map[i][j] = str[j];
			if (map[i][j] == 'C' && start.first == -1) {
				start = P(i, j);
				map[i][j] = 'S';
			}
		}
	}

	deque<Point> dq;
	for (int d = 0; d < 4; d++) {
		isVisited[start.first][start.second][d] = true;
		int ny = start.first + dy[d];
		int nx = start.second + dx[d];
		if (!isOutOfRange(ny, nx) && map[ny][nx] != '*') {
			dq.push_back(Point(ny, nx, d, 0));
			isVisited[ny][nx][d] = true;
		}
	}
	/*
	���⿡ ���� �ٸ� �� �����Ƿ� isVisited�� ���� ���� �߰�
	�ű⿡ ������ �̹� ���� ���·� �����Ͱ� ���Ǹ� 
	isVisited�� dq �ִ� ������ �ϸ� ���� �����Ͱ� �� �� �� �ִ�!
	�׷��Ƿ� dq���� ������ ������ isVisited�� ó���ؾ� �Ѵ�.

	* �տ��� �ְ� �տ��� ���� �� �����̹Ƿ� dfs Ư���� �ִٰ� ������ �� ����.

	����)
	4 4
	C...
	....
	**..
	**.C
	*/
	while (!dq.empty()) {
		Point now = dq.front();
		dq.pop_front();
		isVisited[now.y][now.x][now.dir] = true;
		if (map[now.y][now.x] == 'C') {
			cout << now.reflect;
			return 0;
		}

		//����
		int ny = now.y + dy[now.dir];
		int nx = now.x + dx[now.dir];
		if (!isOutOfRange(ny, nx) && map[ny][nx] != '*' && !isVisited[ny][nx][now.dir]) {
			dq.push_front(Point(ny, nx, now.dir, now.reflect));
		}

		//����
		int nd = now.dir + 1 == 4 ? 0 : now.dir + 1;
		ny = now.y + dy[nd];
		nx = now.x + dx[nd];
		if (!isOutOfRange(ny, nx) && map[ny][nx] != '*' && !isVisited[ny][nx][nd]) {
			dq.push_back(Point(ny, nx, nd, now.reflect + 1));
		}

		nd = now.dir - 1 < 0 ? 3 : now.dir - 1;
		ny = now.y + dy[nd];
		nx = now.x + dx[nd];
		if (!isOutOfRange(ny, nx) && map[ny][nx] != '*' && !isVisited[ny][nx][nd]) {
			dq.push_back(Point(ny, nx, nd, now.reflect + 1));
		}
	}
	cout << -1;
}

bool isOutOfRange(int y, int x) {
	return y < 0 || x < 0 || y >= H || x >= W;
}