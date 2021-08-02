#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef pair<int, int> P;

int gcd(int a, int b);
P getAngle(int x, int y);

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	
	priority_queue<int, vector<int>, greater<int>> ballons;
	P line;
	for (int i = 0; i < N; i++) {
		int x, y, hp;
		scanf("%d %d %d", &x, &y, &hp);
		if (i == 0) {
			P angle = getAngle(x, y);
			line = angle;
		}
		ballons.push(hp);//각도가 일정하다고 했으므로 그냥 pq에 넣어도 됨
	}
	string answer = "";

	long long total = 0;//더해질 시 int 범위 넘을 수 있으므로 long long으로 지정
	for (int i = 0; i < M; i++) {
		int x, y, atk;
		scanf("%d %d %d", &x, &y, &atk);
		P angle = getAngle(x, y);

		if (line.first == angle.first && line.second == angle.second) {//같은 각도이면 atk 더해주고 계산
			total += atk;
			while (!ballons.empty() && ballons.top() <= total) {
				ballons.pop();
			}
		}
		answer.append(to_string(ballons.size()));
		answer.append("\n");
	}
	cout << answer;
}

//각도를 구해주는 함수
P getAngle(int x, int y) {
	if (x == 0 && y != 0) y = y > 0 ? 1 : -1;
	else if (x != 0 && y == 0) x = x > 0 ? 1 : -1;
	else if (x != 0 && y != 0) {
		int gd = gcd(x, y);
		x /= gd;
		y /= gd;
	}

	return P(x, y);
}

//최대공약수 구하는 공식, 유클리드 호제법
int gcd(int a, int b) {
	//양수로 해줘야됨
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	int tmp, n;

	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}

	while (b != 0) {
		n = a % b;
		a = b;
		b = n;
	}

	return a;
}