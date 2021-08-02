#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

struct Customer {
	int visitTime;
	int id;
	int remain;

	Customer(int i, int r, int v) {
		id = i;
		remain = r;
		visitTime = v;
	}
};

struct CustomerComparator {
	bool operator()(Customer c1, Customer c2) {
		return c1.visitTime > c2.visitTime;
	}
};

typedef pair<int, int> P;

int main() {
	int N, T, W, M;
	scanf("%d %d %d", &N, &T, &W);

	//�̹� ����ϴ� �մ��� ����
	queue<P> waiting;
	for (int i = 0; i < N; i++) {
		int p, t;
		scanf("%d %d", &p, &t);
		waiting.push(P(p, t));
	}

	scanf("%d", &M);

	//1�� ���Ŀ� ������ �մ��� �ð� ������ ����
	priority_queue<Customer, vector<Customer>, CustomerComparator> pq;
	for (int i = 0; i < M; i++) {
		int p, t, c;
		scanf("%d %d %d", &p, &t, &c);

		pq.push(Customer(p, t, c));
	}

	int time = 0;
	string answer = "";
	int work = 0;
	while (time < W) {
		//���Ŀ� ���� �մ԰� �ð��� ������ �ٿ� �־���
		if (!pq.empty() && pq.top().visitTime == time) {
			waiting.push(P(pq.top().id, pq.top().remain));
			pq.pop();
		}

		//�� ���� �մ� Ȯ��
		P front = waiting.front();
		//�̹� �� �մԿ��� �� �ð��� �� ������ �ڷ� ������ work ����
		if (work == T) {
			work = 0;
			waiting.pop();
			waiting.push(front);
		}

		P exe = waiting.front();
		//���� ����Ǵ� �۾� ����
		answer.append(to_string(exe.first));
		answer.append("\n");

		//work ����
		work++;

		//���� �մ��� �� �� ���� �������� work ����
		waiting.front().second--;
		if (waiting.front().second == 0) {
			waiting.pop();
			work = 0;
		}
		time++;
	}

	cout << answer << '\n';
}