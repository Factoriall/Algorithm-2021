#include <iostream>
#include <stack>
using namespace std;

string map[30000];
int R, C;

typedef pair<int, int> P;

stack<P> routes[30];//�������� �� ���� route ����
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

	if (route.empty()) {//������� ó������ ����
		now = P(0, c);
		route.push(now);
	}
	else {//�̹� �ִ� ��Ʈ ����
		now = route.top();
		/*
		�ٸ� �ٸ� ��Ʈ���� ���� ��Ʈ�� �Ϻθ� ������ ���ɼ��� 
		�����Ƿ� �� ĭ�� ��Ÿ�� �� ���� ���
		*/
		while (map[now.first][now.second] != '.') {
			route.pop();
			now = route.top();
		}
	}
	
	while (true) {
		if (now.first + 1 == R) break;

		//���� ���� ���� ����, ������ �̲������ų� ����
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

	//�� ����
	P put = route.top();
	map[put.first][put.second] = 'O';
	route.pop();
}