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

	//이미 대기하는 손님을 저장
	queue<P> waiting;
	for (int i = 0; i < N; i++) {
		int p, t;
		scanf("%d %d", &p, &t);
		waiting.push(P(p, t));
	}

	scanf("%d", &M);

	//1초 이후에 들어오는 손님을 시간 순으로 저장
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
		//이후에 들어온 손님과 시간이 맞으면 줄에 넣어줌
		if (!pq.empty() && pq.top().visitTime == time) {
			waiting.push(P(pq.top().id, pq.top().remain));
			pq.pop();
		}

		//맨 앞의 손님 확인
		P front = waiting.front();
		//이미 이 손님에게 쓸 시간을 다 썼으면 뒤로 보내고 work 리셋
		if (work == T) {
			work = 0;
			waiting.pop();
			waiting.push(front);
		}

		P exe = waiting.front();
		//현재 시행되는 작업 저장
		answer.append(to_string(exe.first));
		answer.append("\n");

		//work 조정
		work++;

		//만약 손님이 일 다 봤음 내보내고 work 리셋
		waiting.front().second--;
		if (waiting.front().second == 0) {
			waiting.pop();
			work = 0;
		}
		time++;
	}

	cout << answer << '\n';
}