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

	long long infoSum = 0;//100000 * 100000�� int�� �Ѿ. �̿� ���� ���� ������ �ʿ���.
	for (i = 0; i < Q; i++) {
		int idx;
		scanf("%d", &idx);
		if (idx == 1) {//1: ������ ������ ����
			//string ���� ���, �����ص���!
			char nameChar[16];
			scanf("%s", nameChar);
			string name = nameChar;

			//pq �ʱ�ȭ, ���� map�� ������ �� ���� ������
			priority_queue<int> pq;
			if (m.find(name) != m.end()) {
				pq = m.find(name)->second;
			}
			int k;
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {//�� �������� �켱���� ť�� ����
				int c;
				scanf("%d", &c);
				pq.push(c);
			}
			m[name] = pq;
		}
		else {//2: ȣ���� ������ ��
			//string ���� ���, �����ص���!
			char nameChar[16];
			scanf("%s", nameChar);
			string name = nameChar;

			//���⼭ scanf�� continue ���Ŀ� ��� ���� ������. �Է��� �ǵ��� ��� �տ� ���� �ɷ�!
			int b;
			scanf("%d", &b);

			if (m.find(name) == m.end()) continue;//������ ������ ����
			priority_queue<int> list = m.find(name)->second;
			
			int cnt = 0;
			while (!list.empty() && cnt < b) {//list�� ��ų� cnt�� �ٰ����� ���� ���� ū ������ ���� ����
				infoSum += list.top();
				list.pop();
				cnt++;
			}
			//��ó��
			if (list.empty()) m.erase(name);
			else m[name] = list;
		}
	}
	printf("%lld\n", infoSum);//���
}