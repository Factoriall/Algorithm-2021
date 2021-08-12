#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

vector<int> foods;
long long memo[100001];

struct Cluster {
	int s, e, p;
	Cluster(int s, int e, int p) {
		this->s = s;
		this->e = e;
		this->p = p;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		foods.push_back(num);
	}

	queue<int> fq;
	int sum = 0;

	vector<Cluster> clusters;
	//�� �����͸� �̿��ؼ� clusters�� ���̴� �� ����
	for (int i = 0; i < N; i++) {
		sum += foods[i];
		fq.push(foods[i]);
		if (sum >= K) {
			clusters.push_back(Cluster(i + 1 - fq.size(), i + 1, sum - K));
		}
		while (!fq.empty() && sum>= K) {
			sum -= fq.front();
			fq.pop();
		}

	}

	int idx = 0;
	//���̳��� ���α׷��� �̿�, bottom-up���� �ö󰡱�
	//memo[k]: k������ ���̸� �Ծ��� �� ���� �� �ִ� �ִ� ������
	for (int i = 1; i <= N; i++) {
		//���� Ŭ�������� ���� ���޸��ߴٸ� �� �� ���� ���
		if (idx == clusters.size() || clusters[idx].e != i) {
			memo[i] = memo[i - 1];
			continue;
		}

		//���� ��Ҵٸ� 
		//[���� ��]�� [���� Ŭ������ + Ŭ������ ���� ������ ��]
		//���ؼ� �� ū ���� ����
		memo[i] = max(memo[i - 1], memo[clusters[idx].s] + clusters[idx].p);
		idx++;
	}
	cout << memo[N] << '\n';
}