#include <iostream>
// 여기에 문제 넣기
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef pair<string, int> P;

map<string, int> inParking;
map<string, int> total;

int convertStrIntoInt(string time);

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;

    for (string record : records) {
        string time = record.substr(0, 5);
        int min = convertStrIntoInt(time);
        string carNum = record.substr(6, 4);
        string inOut = record.substr(11);

        bool isIn;
        if (inOut == "IN") isIn = true;
        else isIn = false;

        if (isIn) inParking.insert(P(carNum, min));
        else {
            int sum = min - inParking.find(carNum)->second;
            if (total.find(carNum) != total.end()) {
                total.find(carNum)->second += sum;
            }
            else total.insert(P(carNum, sum));

            inParking.erase(carNum);
        }
        //cout << min << "/" << carNum << "/" << isIn << '\n';
    }

    while (!inParking.empty()) {
        string carNum = inParking.begin()->first;
        int sum = 1439 - inParking.find(carNum)->second;
        if(total.find(carNum) != total.end()) {
            total.find(carNum)->second += sum;
        }
        else total.insert(P(carNum, sum));

        inParking.erase(carNum);
    }

    for (const auto& car : total) {
        //cout << car.first << " " << car.second << "\n";
        int time = car.second;
        int fee = fees[1];
        if (time > fees[0]) {
            int rem = time - fees[0];
            int div = rem / fees[2] + (rem % fees[2] != 0 ? 1 : 0);
            fee += (div * fees[3]);
        }
        answer.push_back(fee);
    }
    return answer;
}

int convertStrIntoInt(string time) {
    int hour = stoi(time.substr(0, 2));
    int min = stoi(time.substr(3, 2));
    return hour * 60 + min;
}


//
int main() {
    vector<int> fees = { 180, 5000, 10, 600 };
    vector<string> records = { "05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT", "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN", "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT" };
    vector<int> answer = solution(fees, records);
    for (int ans : answer) cout << ans << " ";
}