#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid;
    int at;
    int cput;
    int st;
    int tt;
    int wt;
    int ct;
    int rt;
} p[100];

bool sortByAT(process a, process b)
{
    if (a.at == b.at)
        return a.cput < b.cput;
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

    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival and CPU time for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].cput;
        p[i].pid = i + 1;
    }

    sort(p, p + n, sortByAT);

    int timer = 0;
    float totalWT = 0, totalTT = 0, totalRT = 0;

    if (timer < p[0].at)
        timer = p[0].at;

    for (int i = 0; i < n; i++)
    {
        if (timer < p[i].at)
            timer = p[i].at;

        p[i].st = timer;
        p[i].rt = p[i].st - p[i].at;
        timer += p[i].cput;
        p[i].ct = timer;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].cput;

        totalTT += p[i].tt;
        totalWT += p[i].wt;
        totalRT += p[i].rt;
    }

    cout << "\nGantt Chart:\n ";

    cout << "  P" << p[0].pid;
    for (int i = 1; i < n; i++)
        cout << "    P" << p[i].pid;
    cout << "\n";

    cout << p[0].st;
    for (int i = 0; i < n; i++)
        cout << "-----" << p[i].ct;
    cout << "\n";

    sort(p, p + n, sortByPid);

    cout << "\n\nProcess\tAT\tCPU\tST\tCT\tWT\tTT\tRT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].cput
             << "\t" << p[i].st << "\t" << p[i].ct
             << "\t" << p[i].wt << "\t" << p[i].tt
             << "\t" << p[i].rt << endl;
    }

    cout << "\nAverage Turnaround Time = " << totalTT / n;
    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Response Time = " << totalRT / n << endl;

    return 0;
}

/*  Output:

Enter number of processes: 4
Enter arrival and CPU time for P1:  0  5
Enter arrival and CPU time for P2:  1  3
Enter arrival and CPU time for P3:  2  8
Enter arrival and CPU time for P4:  3  6

Gantt Chart:
    P1      P2      P3       P4
0-----5-----8-----16-----22


Process   AT      CPU     ST      CT      WT      TT
P1            0        5         0        5        0         5
P2            1        3         5        8        4         7
P3            2        8         8       16       6        14
P4            3        6         16     22      13       19

Average Waiting Time = 5.75
Average Turnaround Time = 11.25
*/
