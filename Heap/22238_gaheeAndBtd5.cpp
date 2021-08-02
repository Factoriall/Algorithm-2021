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
		ballons.push(hp);//������ �����ϴٰ� �����Ƿ� �׳� pq�� �־ ��
	}
	string answer = "";

	long long total = 0;//������ �� int ���� ���� �� �����Ƿ� long long���� ����
	for (int i = 0; i < M; i++) {
		int x, y, atk;
		scanf("%d %d %d", &x, &y, &atk);
		P angle = getAngle(x, y);

		if (line.first == angle.first && line.second == angle.second) {//���� �����̸� atk �����ְ� ���
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

//������ �����ִ� �Լ�
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

//�ִ����� ���ϴ� ����, ��Ŭ���� ȣ����
int gcd(int a, int b) {
	//����� ����ߵ�
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