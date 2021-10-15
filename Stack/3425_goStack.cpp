#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 1'000'000'000;

bool calculate(string cd);
stack<long long> st;

int main() {
	string answer = "";
	string cmd;
	getline(cin, cmd);
	while (cmd != "QUIT") {
		vector<string> cmds;
		if (cmd != "END") {
			cmds.push_back(cmd);
			getline(cin, cmd);
			while (cmd != "END") {
				cmds.push_back(cmd);
				getline(cin, cmd);
			}
		}
		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			int input;
			cin >> input;
			st.push(input);
			bool isError = false;
			for (string cd : cmds) {
				if (!calculate(cd)) {
					isError = true;
					break;
				}
			}
			if (isError || st.size() != 1) answer += "ERROR\n";
			else answer += to_string(st.top()) + "\n";
			while (!st.empty()) st.pop();
		}
		
		getline(cin, cmd);
		getline(cin, cmd);
		getline(cin, cmd);
		if (cmd != "QUIT") answer += "\n";
	}
	cout << answer;
}

bool calculate(string cd) {
	//cout << "command: " << cd << '\n';
	if (cd.substr(0, 3) == "NUM") {
		long long num = stoi(cd.substr(4));
		st.push(num);
		//cout << "num: " << num << '\n';
	}
	else if (cd == "POP") {
		if (st.empty()) return false;
		st.pop();
	}
	else if (cd == "INV") {
		if (st.empty()) return false;
		long long num = st.top();
		st.pop();
		st.push(-num);
	}
	else if (cd == "DUP") {
		if (st.empty()) return false;
		st.push(st.top());
	}
	else if (cd == "SWP") {
		if (st.size() < 2) return false;
		long long n1 = st.top();
		st.pop();
		long long n2 = st.top();
		st.pop();
		st.push(n1);
		st.push(n2);
	}
	else if (cd == "ADD") {
		if (st.size() < 2) return false;
		long long n1 = st.top();
		st.pop();
		long long n2 = st.top();
		st.pop();
		long long ret = n1 + n2;
		if (ret > MAX || ret < -MAX) return false;
		st.push(ret);
	}
	else if (cd == "SUB") {
		if (st.size() < 2) return false;
		long long n1 = st.top();
		st.pop();
		long long n2 = st.top();
		st.pop();
		long long ret = n2 - n1;
		if (ret > MAX || ret < -MAX) return false;
		st.push(ret);
	}
	else if (cd == "MUL") {
		//cout << st.size() << '\n';
		if (st.size() < 2) return false;
		long long n1 = st.top();
		st.pop();
		long long n2 = st.top();
		st.pop();
		//cout << n1 << " " << n2 << '\n';
		long long ret = n2 * n1;
		if (ret > MAX || ret < -MAX) return false;
		st.push(ret);
	}
	else if (cd == "DIV") {
		if (st.size() < 2) return false;
		long long n1 = st.top();
		st.pop();
		long long n2 = st.top();
		st.pop();
		if (n1 == 0) return false;
		long long ret = abs(n2) / abs(n1);
		if (n2 * n1 >= 0) st.push(ret);
		else st.push(-ret);
	}
	else if (cd == "MOD") {
		if (st.size() < 2) return false;
		long long n1 = st.top();
		st.pop();
		long long n2 = st.top();
		st.pop();
		if (n1 == 0) return false;
		long long ret = abs(n2) % abs(n1);
		if (n2 > 0) st.push(ret);
		else st.push(-ret);
	}
	return true;
}