#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool dp[32001];
vector<int> combination[9];

bool isOutOfRange(int n) {
    return n < 1 || n > 32000;
}

int getConcat(int cnt, int N) {
    int ret = 0;
    int mul = 1;
    while (cnt > 0) {
        ret += (N * mul);
        mul *= 10;
        cnt--;
    }
    return ret;
}

int solution(int N, int number) {
    if (number == N) return 1;

    dp[N] = true;
    combination[1].push_back(N);


    int cnt = 2;
    while (cnt <= 8) {
        for (int i = 1; i < cnt; i++) {
            for (int j = cnt - i; j >= 1; j--) {
                vector<int> com1 = combination[i];
                vector<int> com2 = combination[j];

                for (int c1 : com1) {
                    for (int c2 : com2) {
                        int num = c1 + c2;

                        if (!isOutOfRange(num) && !dp[num]) {
                            if (num == number) return cnt;
                            combination[cnt].push_back(num);
                            dp[num] = true;
                        }

                        num = c1 - c2;
                        if (!isOutOfRange(num) && !dp[num]) {
                            if (num == number) return cnt;
                            combination[cnt].push_back(num);
                            dp[num] = true;
                        }

                        num = c1 * c2;
                        if (!isOutOfRange(num) && !dp[num]) {
                            if (num == number) return cnt;
                            combination[cnt].push_back(num);
                            dp[num] = true;
                        }

                        num = c1 / c2;
                        if (!isOutOfRange(num) && !dp[num]) {
                            if (num == number) return cnt;
                            combination[cnt].push_back(num);
                            dp[num] = true;
                        }
                    }
                }

            }
        }
        int num = getConcat(cnt, N);
        if (num == number) return cnt;
        if (!isOutOfRange(num) && !dp[num]) {
            combination[cnt].push_back(num);
            dp[num] = true;
        }
        cnt++;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N = 5;
    int number = 12;
    cout << solution(N, number);
}