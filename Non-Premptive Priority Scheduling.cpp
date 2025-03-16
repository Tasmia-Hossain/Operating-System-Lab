#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int at;
    int cput;
    int tt;
    int wt;
    int ct;
    int rt;
    int pr;
    int status;
};

bool sortByAT(process a, process b)
{
    if (a.at == b.at)
        return a.pr < b.pr;
    return a.at < b.at;
}

bool sortByPid(process a, process b)
{
    return a.pid < b.pid;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<process> p(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival, CPU time and priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].cput >> p[i].pr;
        p[i].pid = i + 1;
        p[i].status = 0;
    }

    sort(p.begin(), p.end(), sortByAT);

    int timer = 0, completed = 0;
    float totalWT = 0, totalTT = 0, totalRT = 0;
    vector<int> ganttChart;
    vector<int> timeStamps;

    while (completed < n)
    {
        int minm = INT_MAX, idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= timer && p[i].pr < minm && p[i].status == 0)
            {
                minm = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1)
        {
            timer++;
            continue;
        }

        p[idx].rt = timer - p[idx].at;
        timer += p[idx].cput;
        p[idx].ct = timer;
        p[idx].tt = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tt - p[idx].cput;
        p[idx].status = 1;
        completed++;

        totalTT += p[idx].tt;
        totalWT += p[idx].wt;
        totalRT += p[idx].rt;

        ganttChart.push_back(p[idx].pid);
        timeStamps.push_back(timer);
    }

    sort(p.begin(), p.end(), sortByPid);

    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < ganttChart.size(); i++)
        cout << "  P" << ganttChart[i]<<"   " ;
    cout << "\n";

    cout << "0";
    for (int i = 0; i < timeStamps.size(); i++)
        cout << "-----" << timeStamps[i];
    cout << "\n";

    cout << "\nProcess\tAT\tCPU\tPR\tCT\tTT\tWT\tRT\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].cput << "\t" << p[i].pr
             << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\t" << p[i].rt << endl;
    }

    cout << "\nAverage Turnaround Time: " << totalTT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Response Time: " << totalRT / n << endl;

    return 0;
}


/* Output:
Enter number of processes: 7
Enter arrival, CPU time and priority for P1: 0 6 5
Enter arrival, CPU time and priority for P2: 2 6 4
Enter arrival, CPU time and priority for P3: 5 7 3
Enter arrival, CPU time and priority for P4: 6 6 1
Enter arrival, CPU time and priority for P5: 8 7 5
Enter arrival, CPU time and priority for P6: 18 3 1
Enter arrival, CPU time and priority for P7: 25 3 1

Gantt Chart:
   P1      P4       P3        P6       P2        P7       P5
0-----6-----12-----19-----22-----28-----31-----38

Process AT      CPU     PR      CT      TT      WT      RT
P1          0         6         5        6        6        0        0
P2          2         6         4        28      26      20      20
P3          5         7         3        19      14      7        7
P4          6         6         1        12      6        0        0
P5          8         7         5        38      30      23      23
P6          18       3         1        22      4        1        1
P7          25       3         1        31      6        3        3

Average Turnaround Time: 13.1429
Average Waiting Time: 7.71429
Average Response Time: 7.71429
*/
