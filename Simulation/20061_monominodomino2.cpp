#include <iostream>
using namespace std;

int N;
bool downMap[6][4];
bool rightMap[4][6];
int answer = 0;

struct Block {
	int t, x, y;
	Block(int t, int x, int y) {
		this->t = t;
		this->x = x;
		this->y = y;
	}
};

void executeRightMove(Block b);
void executeDownMove(Block b);
void printRightMap();
void printDownMap();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		Block block = Block(t, x, y);

		executeRightMove(block);
		executeDownMove(block);

		printRightMap();
		printDownMap();
	}

	cout << answer << '\n';

	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j < 6; j++) {
			if (rightMap[i][j]) cnt++;
		}
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 2; i < 6; i++) {
			if (downMap[i][j]) cnt++;
		}
	}

	cout << cnt << '\n';
}

void printRightMap() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			cout << rightMap[i][j] << " ";
		}
		cout << '\n';
	}
}

void printDownMap() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << downMap[i][j] << " ";
		}
		cout << '\n';
	}
}

void executeRightMove(Block b) {
	//타일 이동, y 기준
	int j = 2;
	switch (b.t) {

	case 1:
		while (j <= 5) {
			if (rightMap[b.x][j]) break;
			j++;
		}
		rightMap[b.x][j - 1] = true;
		break;
	case 2: 
		while (j <= 5) {
			if (rightMap[b.x][j]) break;
			j++;
		}
		rightMap[b.x][j - 1] = true;
		rightMap[b.x][j - 2] = true;
		break;
	case 3:
		while (j <= 5) {
			if (rightMap[b.x][j] || rightMap[b.x + 1][j]) break;
			j++;
		}
		rightMap[b.x][j - 1] = true;
		rightMap[b.x + 1][j - 1] = true;
		break;
	}

	//점수 획득
	for (int j = 2; j < 6; j++) {
		bool isRemove = true;
		for (int i = 0; i < 4; i++) {
			if (!rightMap[i][j]) {
				isRemove = false;
				break;
			}
		}
		if (isRemove) {
			answer++;
			for (int i = 0; i < 4; i++) {
				rightMap[i][j] = false;
			}
			
			for (int k = j; k > 0; k--) {
				for (int i = 0; i < 4; i++) {
					rightMap[i][k] = rightMap[i][k - 1];
					rightMap[i][k - 1] = false;
				}
			}
			j--;
		}
	}
	
	//타일 이동
	int cnt = 0;
	for (int j = 1; j >= 0; j--) {
		for (int i = 0; i < 4; i++) {
			if (rightMap[i][j]) {
				cnt++;
				break;
			}
		}
	}

	if (cnt == 1) {
		for (int j = 5; j >= 2; j--) {
			for (int i = 0; i < 4; i++) {
				rightMap[i][j] = rightMap[i][j - 1];
			}
		}
		for (int i = 0; i < 4; i++) {
			rightMap[i][1] = false;
		}
	}
	else if (cnt == 2) {
		for (int j = 5; j >= 2; j--) {
			for (int i = 0; i < 4; i++) {
				rightMap[i][j] = rightMap[i][j - 2];
			}
		}
		for (int i = 0; i < 4; i++) {
			rightMap[i][0] = false;
			rightMap[i][1] = false;
		}
	}
}

void executeDownMove(Block b) {
	//타일 이동, x 기준
	int i = 2;
	switch (b.t) {
	case 1:
		while (i <= 5) {
			if (downMap[i][b.y]) break;
			i++;
		}
		downMap[i - 1][b.y] = true;
		break;
	case 3:
		while (i <= 5) {
			if (downMap[i][b.y]) break;
			i++;
		}
		downMap[i - 1][b.y] = true;
		downMap[i - 2][b.y] = true;
		break;
	case 2:
		while (i <= 5) {
			if (downMap[i][b.y] || downMap[i][b.y + 1]) break;
			i++;
		}
		downMap[i - 1][b.y] = true;
		downMap[i - 1][b.y + 1] = true;
		break;
	}
	//점수 획득

	for (int i = 2; i < 6; i++) {
		bool isRemove = true;
		for (int j = 0; j < 4; j++) {
			if (!downMap[i][j]) {
				isRemove = false;
				break;
			}
		}
		if (isRemove) {
			answer++;
			for (int j = 0; j < 4; j++) {
				downMap[i][j] = false;
			}

			for (int k = i; k > 0; k--) {
				for (int j = 0; j < 4; j++) {
					downMap[k][j] = downMap[k-1][j];
					downMap[k-1][j] = false;
				}
			}
			i--;
		}
	}

	//타일 이동
	int cnt = 0;
	for (int i = 1; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (downMap[i][j]) {
				cnt++;
				break;
			}
		}
	}
	cout << "cnt fin" << '\n';
	if (cnt == 1) {
		for (int i = 5; i >= 2; i--) {
			for (int j = 0; j < 4; j++) {
				downMap[i][j] = downMap[i - 1][j];
			}
		}
		for (int j = 0; j < 4; j++) {
			downMap[1][j] = false;
		}
	}
	else if (cnt == 2) {
		for (int i = 5; i >= 2; i--) {
			for (int j = 0; j < 4; j++) {
				downMap[i][j] = downMap[i - 2][j];
			}
		}
		for (int j = 0; j < 4; j++) {
			downMap[0][j] = false;
			downMap[1][j] = false;
		}
	}
}