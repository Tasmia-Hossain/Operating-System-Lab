#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid;
    int at;         // Arrival Time
    int cput;       // CPU Burst Time
    int remaining;  // Remaining CPU Time
    int wt;         // Waiting Time
    int tt;         // Turnaround Time
    int ct;         // Completion Time
    int st;         // Start Time
    int rt;         // Response Time (For Round Robin)
    bool is_completed;
};

bool sortByAT(process a, process b) {
    return a.at < b.at;
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter time quantum: ";
    cin >> tq;

    vector<process> p(n);

    // Input processes
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and CPU burst time for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].cput;
        p[i].pid = i + 1;
        p[i].remaining = p[i].cput;
        p[i].is_completed = false;
        p[i].st = -1;  // -1 to indicate uninitialized start time
    }

    sort(p.begin(), p.end(), sortByAT);

    int timer = 0;        // Keeps track of current time
    float totalWT = 0, totalTT = 0, totalRT = 0;
    queue<int> readyQueue; // Ready Queue for processes
    set<int> inQueue; // Set to track processes already in the ready queue

    vector<int> ganttChart;
    vector<int> timeStamps;

    // Add the first process to the ready queue
    readyQueue.push(0);
    inQueue.insert(0);

    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();
        inQueue.erase(idx);

        // If the process is executing for the first time, set its start time
        if (p[idx].st == -1) {
            p[idx].st = timer;
        }

        if (p[idx].remaining > tq) {
            // Process executes for time quantum (tq)
            p[idx].remaining -= tq;
            timer += tq;
            ganttChart.push_back(p[idx].pid);
            timeStamps.push_back(timer);

            // Add the process back to the ready queue
            readyQueue.push(idx);
            inQueue.insert(idx);
        } else {
            // Process finishes execution
            timer += p[idx].remaining;
            p[idx].ct = timer;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].cput;
            p[idx].rt = p[idx].st - p[idx].at;
            p[idx].remaining = 0;
            p[idx].is_completed = true;

            ganttChart.push_back(p[idx].pid);
            timeStamps.push_back(timer);
        }

        // Add new processes to the ready queue if they have arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].is_completed && p[i].at <= timer && inQueue.find(i) == inQueue.end()) {
                readyQueue.push(i);
                inQueue.insert(i);
            }
        }
    }

    sort(p.begin(), p.end(), [](process a, process b) { return a.pid < b.pid; });

    // Displaying the Gantt Chart
    cout << "\nGantt Chart:\n ";
    for (size_t i = 0; i < ganttChart.size(); i++) {
        cout << "  P" << ganttChart[i];
    }
    cout << "\n";

    cout << "0";
    for (size_t i = 0; i < timeStamps.size(); i++) {
        cout << "-----" << timeStamps[i];
    }
    cout << "\n";

    // Displaying Process Table
    cout << "\nProcess\tAT\tCPU\tST\tCT\tTT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].cput << "\t" << p[i].st
             << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\t" << p[i].rt << endl;

        totalTT += p[i].tt;
        totalWT += p[i].wt;
        totalRT += p[i].rt;
    }

    // Displaying Averages
    cout << "\nAverage Turnaround Time: " << totalTT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Response Time: " << totalRT / n << endl;

    return 0;
}
