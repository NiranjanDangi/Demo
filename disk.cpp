#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int FCFS(const vector<int>& requests, int head) {
    int seek_time = 0;
    cout << "FCFS\nSequence of requests: ";
    for (int r : requests) {
        cout << r << " ";
        seek_time += abs(r - head);
        head = r;
    }
    cout << "\nTotal Seek Time: " << seek_time << "\n\n";
    return seek_time;
}

int SSTF(vector<int>& requests, int head) {
    int seek_time = 0;
    vector<bool> visited(requests.size(), false);
    cout << "SSTF\nSequence of requests: ";

    for (int count = 0; count < requests.size(); ++count) {
        int closest = -1, min_dist = INT_MAX;
        for (int i = 0; i < requests.size(); ++i) {
            if (!visited[i] && abs(requests[i] - head) < min_dist) {
                min_dist = abs(requests[i] - head);
                closest = i;
            }
        }
        visited[closest] = true;
        cout << requests[closest] << " ";
        seek_time += min_dist;
        head = requests[closest];
    }
    cout << "\nTotal Seek Time: " << seek_time << "\n\n";
    return seek_time;
}

int SCAN(vector<int>& requests, int head) {
    int seek_time = 0;
    sort(requests.begin(), requests.end());
    cout << "SCAN\nSequence of requests: ";
    
    auto it = lower_bound(requests.begin(), requests.end(), head);
    for (auto i = it; i != requests.end(); ++i) {
        cout << *i << " ";
        seek_time += abs(*i - head);
        head = *i;
    }
    for (auto i = it - 1; i >= requests.begin(); --i) {
        cout << *i << " ";
        seek_time += abs(*i - head);
        head = *i;
    }
    cout << "\nTotal Seek Time: " << seek_time << "\n\n";
    return seek_time;
}

int CSCAN(vector<int>& requests, int head) {
    int seek_time = 0;
    sort(requests.begin(), requests.end());
    cout << "C-SCAN\nSequence of requests: ";

    auto it = lower_bound(requests.begin(), requests.end(), head);
    for (auto i = it; i != requests.end(); ++i) {
        cout << *i << " ";
        seek_time += abs(*i - head);
        head = *i;
    }
    for (auto i = requests.begin(); i != it; ++i) {
        cout << *i << " ";
        seek_time += abs(*i - head);
        head = *i;
    }
    cout << "\nTotal Seek Time: " << seek_time << "\n\n";
    return seek_time;
}

int main() {
    int disk_size = 200;
    int head = 50;
    vector<int> requests = {95, 180, 34, 119, 11, 123, 62, 64};

    FCFS(requests, head);
    SSTF(requests, head);
    SCAN(requests, head);
    CSCAN(requests, head);

    return 0;
}
