#include <iostream>
#include <string>
#include <vector>

using namespace std;

int timeSum[360000];

int parseIntoSec(string time);
string parseSecToStr(int second);

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    int playSecond = parseIntoSec(play_time);
    int advSecond = parseIntoSec(adv_time);
    //cout << playSecond << ", " << advSecond << '\n';

    for (string log : logs) {
        int startSec = parseIntoSec(log.substr(0, 8));
        int endSec = parseIntoSec(log.substr(9, 17));
        //cout << startSec << "~" << endSec << '\n';
        for (int t = startSec; t < endSec; t++) {
            timeSum[t] += 1;
        }
    }

    int maxSec = 0;
    long accum = 0;
    for (int i = 0; i < advSecond; i++) {
        accum += timeSum[i];
    }

    //단위 생각해야됨, 300000*360000은 int형 한참 넘어감!
    long maxAccum = accum;
    for (int i = advSecond; i < playSecond; i++) {
        accum -= timeSum[i - advSecond];
        accum += timeSum[i];

        if (accum > maxAccum) {
            maxSec = i - advSecond + 1;
            maxAccum = accum;
        }
    }

    return parseSecToStr(maxSec);
}

int parseIntoSec(string time) {
    return stoi(time.substr(0, 2)) * 3600
        + stoi(time.substr(3, 5)) * 60
        + stoi(time.substr(6, 8));
}

string parseSecToStr(int second) {
    //cout << "second: " << second << '\n';
    int hour = second / 3600;
    string hourStr = (hour >= 10 ? "" : "0") + to_string(hour);
    //cout << "hourStr: " << hourStr << '\n';
    int min = (second % 3600) / 60;
    string minStr = (min >= 10 ? "" : "0") + to_string(min);
    //cout << "minStr: " << minStr << '\n';
    int sec = second % 60;
    string secStr = (sec >= 10 ? "" : "0") + to_string(sec);
    //cout << "secStr: " << secStr << '\n';

    return hourStr + ":" + minStr + ":" + secStr;
}

int main() {
    string play_time = "01:00:01";
    string adv_time = "00:59:59";
    vector<string> logs = { "00:00:01-00:20:00", "00:30:01-01:00:01" };

    cout << solution(play_time, adv_time, logs);

}