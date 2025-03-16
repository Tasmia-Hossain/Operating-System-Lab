#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid;
    int at;
    int cput;
    int remainingTime;
    int st;
    int ct;
    int wt;
    int tt;
    int rt;
};

bool sortByAT(process a,process b)
{
    return a.at<b.at;
}

bool sortByPID(process a,process b)
{
    return a.pid<b.pid;
}

int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<process>p(n);

    for(int i=0; i<n;i++)
    {
        cout<<"Enter arrival time and cpu time for P"<<i + 1<<": ";
        cin>>p[i].at>>p[i].cput;
        p[i].pid=i+1;
        p[i].remainingTime=p[i].cput;
    }

    sort(p.begin(),p.end(),sortByAT);

    int timer=0;
    float totalWT=0,totalTT=0,totalRT=0;
    vector<bool>completed(n,false);
    int completedCount=0;
    vector<int>ganttOrder;
    vector<int>ganttTime;

    while(completedCount<n) {
        int idx=-1;
        int minRemainingTime=INT_MAX;

        for(int i=0; i<n;i++)
        {
            if (!completed[i]&&p[i].at<=timer&&p[i].remainingTime<minRemainingTime)
            {
                minRemainingTime=p[i].remainingTime;
                idx=i;
            }
        }

        if (idx==-1)
        {
            timer++;
        }
        else
        {
            if(p[idx].remainingTime==p[idx].cput)
            {
                p[idx].st=timer;
                p[idx].rt=p[idx].st-p[idx].at;
            }

            if (ganttOrder.empty() || ganttOrder.back() != p[idx].pid)
            {
                ganttOrder.push_back(p[idx].pid);
                ganttTime.push_back(timer);
            }

            p[idx].remainingTime--;

            if(p[idx].remainingTime==0)
            {
                p[idx].ct =timer+1;
                p[idx].tt = p[idx].ct-p[idx].at;
                p[idx].wt = p[idx].tt-p[idx].cput;

                totalTT+=p[idx].tt;
                totalWT+=p[idx].wt;
                totalRT+=p[idx].rt;

                completed[idx]=true;
                completedCount++;
            }
            timer++;
        }
    }

    ganttTime.push_back(timer);

    cout<<"\nGantt Chart:\n";
    for(int i=0;i<ganttOrder.size();i++)
    {
        if(i != 0)
            cout<<"     ";
        cout<<"P"<<ganttOrder[i];
    }
    cout<<"\n";

    for(int i=0; i<ganttTime.size();i++)
    {
        if (i !=0)
            cout<<"-----";
        cout<<ganttTime[i];
    }
    cout<<"\n";

    sort(p.begin(),p.end(),sortByPID);

    cout<<"\nProcess\tAT\tCPUT\tST\tCT\tWT\tTT\tRT\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].cput<<"\t"
             <<p[i].st<<"\t"<<p[i].ct<<"\t"<<p[i].wt<<"\t"<<p[i].tt
             <<"\t"<<p[i].rt<<endl;
    }

    cout<<"\nAverage Turnaround Time = "<<totalTT / n;
    cout<<"\nAverage Waiting Time = "<<totalWT / n;
    cout<<"\nAverage Response Time = "<<totalRT / n<<endl;

    return 0;
}

/* Output:
Enter number of processes: 7
Enter arrival time and cpu time for P1: 0 15
Enter arrival time and cpu time for P2: 4 10
Enter arrival time and cpu time for P3: 6 2
Enter arrival time and cpu time for P4: 7 1
Enter arrival time and cpu time for P5: 12 4
Enter arrival time and cpu time for P6: 15 1
Enter arrival time and cpu time for P7: 22 2

Gantt Chart:
   P1       P2     P3     P4      P2       P5        P6       P2        P7       P1
0-----4-----6-----8-----9-----12-----16-----17-----22-----24-----35

Process AT      CPUT    ST      CT      WT      TT      RT
P1          0       15          0       35      20      35      0
P2          4       10          4       22      8        18      0
P3          6       2           6        8        0        2        0
P4          7       1           8        9        1        2        1
P5          12      4         12       16      0        4        0
P6          15      1         16       17      1        2        1
P7          22      2         22       24      0        2        0

Average Turnaround Time = 9.28571
Average Waiting Time = 4.28571
Average Response Time = 0.285714
*/
