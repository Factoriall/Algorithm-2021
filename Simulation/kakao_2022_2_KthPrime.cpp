#include <iostream>
// 여기에 문제 넣기
#include <string>
#include <vector>
#include <stack>

using namespace std;
string convertIntoK(int n, int k);

bool isPrime(long long num);

int solution(int n, int k) {
    string cvt = convertIntoK(n, k);
    cout << cvt << '\n';

    int start = -1;

    int answer = 0;
    for (int i = 0; i < cvt.size(); i++) {
        if (start == -1) {
            if(cvt[i] != '0') start = i;
            continue;
        }

        if (cvt[i] == '0') {
            long long num = stoll(cvt.substr(start, i - start));
            cout << num << '\n';
            if (isPrime(num)) answer++;
            start = -1;
        }
    }
    if (start != -1) {
        long long num = stoll(cvt.substr(start, cvt.size() - start));
        cout << num << '\n';
        if (isPrime(num)) answer++;
    }
    
    return answer;
}

bool isPrime(long long num) {
    if (num == 1) return false;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

string convertIntoK(int n, int k) {
    stack<int> s;
    while (n != 0) {
        s.push(n % k);
        n /= k;
    }

    string ret = "";
    while (!s.empty()) {
        ret = ret + to_string(s.top());
        s.pop();
    }
    return ret;
}


//
int main() {
    int n = 437674;
    int k = 3;
    cout << solution(n, k);
}