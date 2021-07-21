#define	_CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <map>
#include <queue>
using namespace std;

map<string, priority_queue<int>> m;

int main() {
	int i;
	int Q;
	scanf("%d", &Q);

	long long infoSum = 0;//100000 * 100000은 int형 넘어감. 이에 대한 사전 숙지가 필요함.
	for (i = 0; i < Q; i++) {
		int idx;
		scanf("%d", &idx);
		if (idx == 1) {//1: 상인이 정보를 얻음
			//string 저장 방법, 숙지해두자!
			char nameChar[16];
			scanf("%s", nameChar);
			string name = nameChar;

			//pq 초기화, 만약 map에 있으면 그 값을 가져옴
			priority_queue<int> pq;
			if (m.find(name) != m.end()) {
				pq = m.find(name)->second;
			}
			int k;
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {//산 정보들을 우선순위 큐에 저장
				int c;
				scanf("%d", &c);
				pq.push(c);
			}
			m[name] = pq;
		}
		else {//2: 호석이 정보를 삼
			//string 저장 방법, 숙지해두자!
			char nameChar[16];
			scanf("%s", nameChar);
			string name = nameChar;

			//여기서 scanf를 continue 이후에 적어서 오류 났었음. 입력은 되도록 모두 앞에 쓰는 걸로!
			int b;
			scanf("%d", &b);

			if (m.find(name) == m.end()) continue;//정보가 없으면 무시
			priority_queue<int> list = m.find(name)->second;
			
			int cnt = 0;
			while (!list.empty() && cnt < b) {//list가 비거나 cnt에 다가갈때 까지 제일 큰 가격의 정보 구매
				infoSum += list.top();
				list.pop();
				cnt++;
			}
			//후처리
			if (list.empty()) m.erase(name);
			else m[name] = list;
		}
	}
	printf("%lld\n", infoSum);//출력
}