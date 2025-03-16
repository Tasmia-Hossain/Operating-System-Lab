#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, rt, ct, tt, wt, pr;
};

bool sortByAT(Process a, Process b) {
    if (a.at == b.at)
        return a.pr < b.pr;
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time, and priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
    }

    sort(p.begin(), p.end(), sortByAT);
    int timer = 0, completed = 0;
    float totalTT = 0, totalWT = 0, totalRT = 0;
    vector<int> ganttChart, timeStamps;
    vector<bool> isFirstResponse(n, true);

    while (completed < n) {
        int idx = -1, minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= timer && p[i].rt > 0 && p[i].pr < minPriority) {
                minPriority = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            timer++;
            continue;
        }

        if (isFirstResponse[idx]) {
            p[idx].wt = timer - p[idx].at;
            totalRT += p[idx].wt;
            isFirstResponse[idx] = false;
        }

        ganttChart.push_back(p[idx].pid);
        timeStamps.push_back(timer);

        p[idx].rt--;
        timer++;

        if (p[idx].rt == 0) {
            p[idx].ct = timer;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            totalTT += p[idx].tt;
            totalWT += p[idx].wt;
            completed++;
        }
    }

    timeStamps.push_back(timer);

    cout << "\nGantt Chart:\n";
    for (int i = 0; i < ganttChart.size(); i++)
        cout << "  P" << ganttChart[i] << "  ";
    cout << "\n0";
    for (int i = 0; i < timeStamps.size(); i++)
        cout << "---" << timeStamps[i];
    cout << "\n";

    cout << "\nProcess\tAT\tBT\tPR\tCT\tTT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].pr
             << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\t" << p[i].wt << "\n";
    }

    cout << "\nAverage Turnaround Time: " << totalTT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Response Time: " << totalRT / n << endl;

    return 0;
}
