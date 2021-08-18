#include <iostream>
#include <stack>
using namespace std;

string map[30000];
int R, C;

typedef pair<int, int> P;

stack<P> routes[30];//스택으로 각 열의 route 저장
void getRoute(int c);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		cin >> map[i];
	}

	int N;
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		int c;
		cin >> c;
		c--;

		getRoute(c);
	}

	for (int i = 0; i < R; i++) {
		cout << map[i] << '\n';
	}
}

void getRoute(int c) {
	P now;
	stack<P>& route = routes[c];

	if (route.empty()) {//비어있음 처음부터 시작
		now = P(0, c);
		route.push(now);
	}
	else {//이미 있는 루트 참조
		now = route.top();
		/*
		다만 다른 루트에서 현재 루트의 일부를 덮었을 가능성이 
		있으므로 빈 칸이 나타날 때 까지 덜어냄
		*/
		while (map[now.first][now.second] != '.') {
			route.pop();
			now = route.top();
		}
	}
	
	while (true) {
		if (now.first + 1 == R) break;

		//문제 구현 따라 왼쪽, 오른쪽 미끄러지거나 멈춤
		char status = map[now.first + 1][now.second];
		if (status == 'X') break;
		else if (status == 'O') {
			if (now.second != 0 &&
				map[now.first][now.second - 1] == '.' &&
				map[now.first + 1][now.second - 1] == '.') {
				now.second -= 1;
			}
			else if (now.second != C - 1 &&
				map[now.first][now.second + 1] == '.' &&
				map[now.first + 1][now.second + 1] == '.') {
				now.second += 1;
			}
			else break;
		}
		now.first += 1;
		route.push(now);
	}

	//값 저장
	P put = route.top();
	map[put.first][put.second] = 'O';
	route.pop();
}