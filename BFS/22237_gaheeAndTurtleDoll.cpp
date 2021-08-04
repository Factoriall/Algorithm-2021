#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>	
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int R, C;
int dy[4] = { 1,0,-1,0 };
int dx[4] = { 0,1,0,-1 };

struct Point {
	int y, x;
	Point(){}
	Point(int y, int x) {
		this->y = y;
		this->x = x;
	}

	bool isOutOfRange(int h, int w) {
		return y < 0 || x < 0 || y + h > R || x + w > C;
	}
};

struct DollInfo {
	vector<Point> points;
	Point leftUp;
	int width;
	int height;

	DollInfo(){}
	DollInfo(vector<Point> pnts) {
		Point rd = Point(0, 0);
		Point lu = Point(R-1, C-1);
		for (Point p : pnts) {
			lu.y = min(lu.y, p.y);
			lu.x = min(lu.x, p.x);
			rd.y = max(rd.y, p.y);
			rd.x = max(rd.x, p.x);
		}
		leftUp = lu;
		height = rd.y - lu.y + 1;
		width = rd.x - lu.x + 1;

		for (int i = 0; i < pnts.size(); i++) {//point를 leftup에 상대적이게 변화
			pnts[i].y -= leftUp.y;
			pnts[i].x -= leftUp.x;
		}
		
		points = pnts;
	}

	void printInfo() {
		printf("leftUp: (%d, %d), width: %d, height: %d\n", 
			leftUp.y, leftUp.x,
			width, height);
		printf("Point\n");
		for (Point p : points) {
			printf("(%d,%d)\n", p.y, p.x);
		}
	}
};

struct QueueInfo {
	Point lu;
	vector<char> routes;

	QueueInfo(Point p, vector<char> r) {
		lu = p;
		routes = r;
	}
};

typedef QueueInfo QI;
char getAlp(int d);

bool isVisited[1000][1000];
bool isFinished[1000][1000];
int main() {
	scanf("%d %d", &R, &C);

	//입력 받아서 저장
	vector<Point> doll;
	vector<Point> obstacles;
	Point home;
	for(int i=0; i<R; i++){
		char line[1001];
		scanf("%s", line);
		for (int j = 0; j < C; j++) {
			if (line[j] == 'T') {
				doll.push_back(Point(i, j));
			}
			else if (line[j] == '#')
				obstacles.push_back(Point(i, j));
			else if (line[j] == 'H')
				home = Point(i, j);
		}
	}
	DollInfo di = DollInfo(doll);

	//obstacle 정보 따라 isVisited 정보 저장
	for (Point o : obstacles) {
		for (Point p : di.points) {
			Point lu = Point(o.y - p.y, o.x - p.x);
			if(!lu.isOutOfRange(di.height, di.width))
				isVisited[lu.y][lu.x] = true;
		}
	}

	//여기에 닿을 시 끝내는 isFinished 정보 저장
	for (Point p : di.points) {
		Point lu = Point(home.y - p.y, home.x - p.x);
		if (!lu.isOutOfRange(di.height, di.width))
			isFinished[lu.y][lu.x] = true;
	}

	//bfs로 저장, 이동정보를 계속 저장해야함
	//D-R-U-L 순서
	queue<QI> q;
	vector<char> route;
	isVisited[di.leftUp.y][di.leftUp.x] = true;
	q.push(QI(di.leftUp, route));

	while (!q.empty()) {
		int qSize = q.size();
		for (int t = 0; t < qSize; t++) {
			QI now = q.front();
			q.pop();

			if (isFinished[now.lu.y][now.lu.x]){
				for (char c : now.routes) printf("%c", c);
				return 0;
			}

			for (int d = 0; d < 4; d++) {
				Point next = Point(now.lu.y + dy[d], now.lu.x + dx[d]);
				if (next.isOutOfRange(di.height, di.width)) continue;
				if (isVisited[next.y][next.x]) continue;
				isVisited[next.y][next.x] = true;

				vector<char> nr = now.routes;
				nr.push_back(getAlp(d));
				q.push(QI(next, nr));
			}
		}
	}

	printf("-1");
}

//D-R-U-L 순서
char getAlp(int d) {//알파벳 얻는 함수
	if (d == 0) return 'D';
	else if (d == 1) return 'R';
	else if (d == 2) return 'U';
	else if (d == 3) return 'L';
	return 'X';
}