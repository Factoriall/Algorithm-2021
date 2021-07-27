#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <string>
#include <set>
using namespace std;
const int MAX = 500000;
int turn[MAX];
set<int> isAquired;

class Card {
public:
	int id;
	string cmd;
	int num = -1;

	Card(){
		id = -1;
	}

	Card(int i, string c) {
		id = i;
		cmd = c;
	}

	Card(int i, string c, int n) {
		id = i;
		cmd = c;
		num = n;
	}
};

class Player {
public:
	Card holding = Card();
	set<int> resources;

	void printInfo() {
		printf("holding: %d\n", holding.id);
		printf("resources\n");
		for (auto j = resources.begin(); j != resources.end(); j++)
			printf("%d ", *j);
		printf("\n");
	}
};

int main() {
	int N, T;
	scanf("%d %d", &N, &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &turn[i]);
	}

	queue<Card> deck;
	for (int i = 0; i < T; i++) {
		int id;
		char cmd[10];
		scanf("%d", &id);
		scanf("%s", cmd);
		string cmdStr = cmd;
		if (cmdStr != "next") {
			int num;
			scanf("%d", &num);
			deck.push(Card(id, cmdStr, num));
		}
		else {
			deck.push(Card(id, cmdStr));
		}
	}

	vector<Player> players;
	for (int i = 0; i < N; i++) players.push_back(Player());
	
	for (int i = 0; i < T; i++) {
		int pNum = turn[i] - 1;
		if (players[pNum].holding.id == -1) {//ī�� �̱�
			//printf("draw\n");
			Card draw = deck.front();
			deck.pop();
			printf("%d\n", draw.id);

			if (draw.cmd == "next") continue;
			else if (draw.cmd == "acquire") {//�ڿ� ��� �õ�
				if (isAquired.find(draw.num) == isAquired.end()) {//�ڿ� ����
					isAquired.insert(draw.num);
					players[pNum].resources.insert(draw.num);
				}
				else {//ī�� ��� �ֱ�
					players[pNum].holding = draw;
				}
			}
			else {//�տ� ��� �ִ� �ڿ� �ǵ�������
				isAquired.erase(draw.num);
				players[pNum].resources.erase(draw.num);
			}
		}
		else {//���� ī�� ��� �ִ� ����
			//printf("use holding\n");
			Card holding = players[pNum].holding;
			printf("%d\n", holding.id);

			if (isAquired.find(holding.num) == isAquired.end()) {//�ڿ� ����, ī�� ����
				isAquired.insert(holding.num);
				players[pNum].resources.insert(holding.num);
				players[pNum].holding = Card();// ī�� ����
			}
		}
		/*
		for (Player player : players) {
			player.printInfo();
		}
		printf("========================\n");*/
	}


}