#include <bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int at;
    int cput;
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

    for(int i=0;i<n;i++)
    {
        cout<<"Enter arrival time and cpu time for P"<<i + 1<< ": ";
        cin>>p[i].at >>p[i].cput;
        p[i].pid=i+1;
    }

    sort(p.begin(),p.end(),sortByAT);

    int timer=0;
    float totalWT=0, totalTT=0,totalRT = 0;
    vector<bool>completed(n,false);
    int completedCount=0;
    vector<int>ganttOrder;
    vector<int>ganttTime;

    while(completedCount < n)
    {
        int idx=-1;
        int minCPUT=INT_MAX;

        for(int i=0;i<n;i++)
        {
            if (!completed[i] && p[i].at<=timer && p[i].cput<minCPUT)
            {
                minCPUT=p[i].cput;
                idx=i;
            }
        }

        if (idx==-1)
        {
            timer++;
        }
        else
        {
            p[idx].st=timer;
            p[idx].rt=p[idx].st-p[idx].at;
            timer+=p[idx].cput;
            p[idx].ct=timer;
            p[idx].tt=p[idx].ct - p[idx].at;
            p[idx].wt=p[idx].tt - p[idx].cput;

            totalTT+=p[idx].tt;
            totalWT+=p[idx].wt;
            totalRT+=p[idx].rt;

            completed[idx]=true;
            completedCount++;
            ganttOrder.push_back(p[idx].pid);
            ganttTime.push_back(p[idx].st);
        }
    }
    ganttTime.push_back(timer);

    cout<<"\nGantt Chart:\n";

    for(int i=0;i<ganttOrder.size();i++)
    {
        if (i!=0) cout<<"     ";
        cout<<"P"<<ganttOrder[i];
    }
    cout<<"\n";

    for(int i=0;i<ganttTime.size();i++)
    {
        if (i !=0) cout<<"-----";
        cout<<ganttTime[i];
    }
    cout<<"\n";

    sort(p.begin(),p.end(),sortByPID);

    cout<<"\nProcess\tAT\tCPUT\tST\tCT\tWT\tTT\tRT\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].cput<<"\t"
             <<p[i].st<<"\t"<<p[i].ct<<"\t"<<p[i].wt<<"\t"<<p[i].tt<<"\t"<<p[i].rt<<endl;
    }

    cout<<"\nAverage Turnaround Time = "<<totalTT / n;
    cout<<"\nAverage Waiting Time = " <<totalWT / n;
    cout <<"\nAverage Response Time = "<< totalRT / n<<endl;

    return 0;
}

/* Output:
Enter number of processes: 5
Enter arrival time and cpu time for P1: 0 5
Enter arrival time and cpu time for P2: 1 3
Enter arrival time and cpu time for P3: 2 8
Enter arrival time and cpu time for P4: 3 6
Enter arrival time and cpu time for P5: 6 1

Gantt Chart:
P1          P2      P5     P4       P3
0-----5-----8-----9-----15-----23

Process  AT      CPUT    ST      CT      WT      TT      RT
P1          0           5         0       5        0         5        0
P2          1           3        5        8        4         7        4
P3          2           8        15      23      13       21      13
P4          3           6        9        15      6        12       6
P5          6           1        8         9       2         3        2

Average Waiting Time = 5
Average Turnaround Time = 9.6
Average Response Time = 5
*/
