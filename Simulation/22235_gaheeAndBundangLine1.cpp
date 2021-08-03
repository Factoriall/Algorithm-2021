#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

int bundangLine[62];
int fromToTime[6];

void saveTimeInArray();
int getTimeDiff(int s, int e);
int minus210(int n);
int plus210(int n);
int getTrackIdx(int s);
int getNumFromIdx(int s);

typedef pair<int, int> P;

int main() {

	//분당선의 시간 저장
	saveTimeInArray();

	//fromToTime은 20초 쉬고 시작했을 시의 걸리는 시간을 의미
	int T = 0;
	int idx = 0;
	for (int i = 1; i < 6; i++) {
			
		while (idx < minus210(getNumFromIdx(i))) {
			T += 20;
			T += bundangLine[idx] * 60;
			idx++;
		}
		fromToTime[i] = T;
	}
	
	//입력 저장
	char start[9];
	scanf("%s", start);
	string sStr = start;
	int nowTime = stoi(sStr.substr(0, 2)) * 3600 +
		stoi(sStr.substr(3, 5)) * 60 +
		stoi(sStr.substr(6, 8));
	
	int N;
	scanf("%d", &N);

	//tracks에 시간 저장
	priority_queue<P, vector<P>, greater<P>> tracks[6];
	for (int i = 0; i < N; i++) {
		char from[5];
		char to[5];
		char time[6];

		//입력 저장
		scanf("%s %s %s", from, to, time);
		string fromStr = from;
		int s = getTrackIdx(stoi(fromStr.substr(1, 4)));
		string toStr = to;
		int e = getTrackIdx(stoi(toStr.substr(1, 4)));
		string timeStr = time;
		int t = stoi(timeStr.substr(0, 2)) * 3600 + stoi(timeStr.substr(3, 5)) * 60;

		//fromToTime은 20초 쉬고 시작했을 시의 걸리는 시간을 의미, 여기서 time은 바로 출발하는 시간이므로 처음 쉬는 시간 20초를 빼줘야 함
		for (int n = s; n < e; n++) {
			tracks[n].push(P(t + getTimeDiff(s, n) - 20, e));
		}
	}

	int now = 1;//모란역의 idx
	while (now != 5) {//도착할 때 까지
		int tmp = now;
		while (!tracks[now].empty()) {
			P fastest = tracks[now].top();
			tracks[now].pop();
			if (fastest.first + 20 < nowTime) continue;//fastest의 정보는 도착 시간, 출발 시간과 맞춰야 하므로 20초 추가
			
			//여기서 sec를 출발시간으로 고정
			nowTime = fastest.first;
			//시간 더하기
			nowTime += getTimeDiff(now, fastest.second);
			now = fastest.second;//끝 역
		}
		if (tmp == now) {//움직이지 않았으면 갈 방법이 없다는 얘기, 탈출
			printf("-1\n");
			return 0;
		}
	}
	if (nowTime >= 24 * 60 * 60) {//24시 넘어가면 실패, 탈출
		printf("-1\n");
		return 0;
	}

	printf("%02d:%02d:%02d\n", nowTime / 3600, (nowTime / 60) % 60, nowTime % 60);//결과값 출력
}

void saveTimeInArray() {
	for (int i = 0; i < 62; i++) {
		int min;
		switch (plus210(i)) {
		case 210:
			min = 3;
			break;
		case 220:
			min = 4;
			break;
		case 221:
			min = 4;
			break;
		case 222:
			min = 3;
			break;
		case 225:
			min = 3;
			break;
		case 238:
			min = 3;
			break;
		case 245:
			min = 4;
			break;
		case 247:
			min = 5;
			break;
		case 249:
			min = 4;
			break;
		case 250:
			min = 3;
			break;
		case 256:
			min = 3;
			break;
		case 266:
			min = 3;
			break;
		default:
			min = 2;
		}
		bundangLine[i] = min;
	}
}

int getTimeDiff(int s, int e) {
	return fromToTime[e] - fromToTime[s];
}

int getTrackIdx(int s) {
	if (s == 210) return 0;
	if (s == 225) return 1;
	else if (s == 233) return 2;
	else if (s == 246) return 3;
	else if (s == 258) return 4;
	else return 5;
}

int getNumFromIdx(int s) {
	if (s == 0) return 210;
	if (s == 1) return 225;
	else if (s == 2) return 233;
	else if (s == 3) return 246;
	else if (s == 4) return 258;
	else return 272;
}

int plus210(int n) {
	return n + 210;
}

int minus210(int n) {
	return n - 210;
}