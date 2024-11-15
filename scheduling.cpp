#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, burst_time, arrival_time, priority, remaining_time, finish_time, turnaround_time, waiting_time;
};

void calculate_times(vector<Process>& p) {
    for (auto& proc : p) {
        proc.turnaround_time = proc.finish_time - proc.arrival_time;
        proc.waiting_time = proc.turnaround_time - proc.burst_time;
    }
}

void print_times(const vector<Process>& p) {
    cout << "PID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n";
    for (const auto& proc : p) {
        cout << proc.pid << "\t" << proc.arrival_time << "\t" << proc.burst_time << "\t"
             << proc.finish_time << "\t" << proc.turnaround_time << "\t\t" << proc.waiting_time << endl;
    }
}

// First Come First Serve (FCFS)
void fcfs(vector<Process>& p) {
    cout << "\nFCFS Scheduling: ";
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });
    int time = 0;
    for (auto& proc : p) {
        proc.finish_time = max(time, proc.arrival_time) + proc.burst_time;
        time = proc.finish_time;
        cout << "P" << proc.pid << " ";
    }
    cout << endl;
    calculate_times(p);
}

// Shortest Job First (Non-Preemptive)
void sjf_non_preemptive(vector<Process>& p) {
    cout << "\nSJF (Non-Preemptive) Scheduling: ";
    int time = 0;
    vector<bool> finished(p.size(), false);
    while (true) {
        int min_index = -1;
        for (size_t i = 0; i < p.size(); ++i) {
            if (!finished[i] && p[i].arrival_time <= time) {
                if (min_index == -1 || p[i].burst_time < p[min_index].burst_time) {
                    min_index = i;
                }
            }
        }
        if (min_index == -1) break;

        time += p[min_index].burst_time;
        p[min_index].finish_time = time;
        finished[min_index] = true;
        cout << "P" << p[min_index].pid << " ";
    }
    cout << endl;
    calculate_times(p);
}

// Shortest Job First (Preemptive)
void sjf_preemptive(vector<Process>& p) {
    cout << "\nSJF (Preemptive) Scheduling: ";
    int time = 0;
    vector<bool> finished(p.size(), false);
    while (true) {
        int min_index = -1;
        for (size_t i = 0; i < p.size(); ++i) {
            if (!finished[i] && p[i].arrival_time <= time && p[i].remaining_time > 0) {
                if (min_index == -1 || p[i].remaining_time < p[min_index].remaining_time) {
                    min_index = i;
                }
            }
        }
        if (min_index == -1) break;

        cout << "P" << p[min_index].pid << " ";
        p[min_index].remaining_time--;
        time++;
        if (p[min_index].remaining_time == 0) {
            p[min_index].finish_time = time;
            finished[min_index] = true;
        }
    }
    cout << endl;
    calculate_times(p);
}

// Priority Scheduling (Non-Preemptive)
void priority_non_preemptive(vector<Process>& p) {
    cout << "\nPriority Scheduling (Non-Preemptive): ";
    int time = 0;
    vector<bool> finished(p.size(), false);
    while (true) {
        int min_index = -1;
        for (size_t i = 0; i < p.size(); ++i) {
            if (!finished[i] && p[i].arrival_time <= time) {
                if (min_index == -1 || p[i].priority < p[min_index].priority) {
                    min_index = i;
                }
            }
        }
        if (min_index == -1) break;

        time += p[min_index].burst_time;
        p[min_index].finish_time = time;
        finished[min_index] = true;
        cout << "P" << p[min_index].pid << " ";
    }
    cout << endl;
    calculate_times(p);
}

// Round Robin Scheduling
void round_robin(vector<Process>& p, int quantum) {
    cout << "\nRound Robin Scheduling: ";
    int time = 0, completed = 0;
    vector<int> remaining_time(p.size());
    for (size_t i = 0; i < p.size(); ++i) remaining_time[i] = p[i].burst_time;

    while (completed < p.size()) {
        for (size_t i = 0; i < p.size(); ++i) {
            if (remaining_time[i] > 0 && p[i].arrival_time <= time) {
                cout << "P" << p[i].pid << " ";
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    p[i].finish_time = time;
                    completed++;
                }
            }
        }
    }
    cout << endl;
    calculate_times(p);
}

// Priority Scheduling (Preemptive)
void priority_preemptive(vector<Process>& p) {
    cout << "\nPriority Scheduling (Preemptive): ";
    int time = 0;
    vector<bool> finished(p.size(), false);
    while (true) {
        int min_index = -1;
        for (size_t i = 0; i < p.size(); ++i) {
            if (!finished[i] && p[i].arrival_time <= time && p[i].remaining_time > 0) {
                if (min_index == -1 || p[i].priority < p[min_index].priority) {
                    min_index = i;
                }
            }
        }
        if (min_index == -1) break;

        cout << "P" << p[min_index].pid << " ";
        p[min_index].remaining_time--;
        time++;
        if (p[min_index].remaining_time == 0) {
            p[min_index].finish_time = time;
            finished[min_index] = true;
        }
    }
    cout << endl;
    calculate_times(p);
}

int main() {
    vector<Process> p = {
        {1, 6, 0, 1, 6, 0, 0, 0},
        {2, 8, 1, 3, 8, 0, 0, 0},
        {3, 7, 2, 2, 7, 0, 0, 0},
        {4, 3, 3, 4, 3, 0, 0, 0},
    };

    // Call each scheduling algorithm
    fcfs(p);
    print_times(p);

    sjf_non_preemptive(p);
    print_times(p);

    sjf_preemptive(p);
    print_times(p);

    priority_non_preemptive(p);
    print_times(p);

    priority_preemptive(p);
    print_times(p);

    round_robin(p, 2);  // Quantum of 2
    print_times(p);

    return 0;
}
