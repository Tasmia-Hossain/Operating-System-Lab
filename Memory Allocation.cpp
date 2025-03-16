#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void displayResult(const vector<int> &allocation)
{
    cout << "\nProcess No.\tBlock No.\n";
    for (int i = 0; i < allocation.size(); i++)
    {
        cout << i + 1 << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

int calculateExternalFragmentation(vector<int> &blockSize, const vector<int> &processSize)
{
    int totalFreeMemory = 0;
    for (int size : blockSize)
    {
        totalFreeMemory += size;
    }

    // Check if any process can fit into the free memory
    for (int size : processSize)
    {
        if (size <= totalFreeMemory)
        {
            return totalFreeMemory;
        }
    }
    return totalFreeMemory;
}

// First Fit
void firstFit(vector<int> blockSize, vector<int> processSize)
{
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++)
    {
        for (int j = 0; j < blockSize.size(); j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nFirst Fit:";
    displayResult(allocation);

    // Calculate external fragmentation
    int extFrag = calculateExternalFragmentation(blockSize, processSize);
    cout << "External Fragmentation: " << extFrag << endl; // Added line
}

// Best Fit
void bestFit(vector<int> blockSize, vector<int> processSize)
{
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < blockSize.size(); j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nBest Fit:";
    displayResult(allocation);

    // Calculate external fragmentation
    int extFrag = calculateExternalFragmentation(blockSize, processSize);
    cout << "External Fragmentation: " << extFrag << endl; // Added line
}

// Worst Fit
void worstFit(vector<int> blockSize, vector<int> processSize)
{
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < blockSize.size(); j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\nWorst Fit:";
    displayResult(allocation);


    int extFrag = calculateExternalFragmentation(blockSize, processSize);
    cout << "External Fragmentation: " << extFrag << endl;
}
/*
//Next Fit
void nextFit(vector<int> blockSize, vector<int> processSize)
{
    vector<int> allocation(processSize.size(), -1);
    int lastAllocated = 0;

    for (int i = 0; i < processSize.size(); i++)
    {
        int j = lastAllocated;
        int count = 0;

        while (count < blockSize.size())
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                break;
            }

            j = (j + 1) % blockSize.size();
            count++;
        }
    }

    cout << "\nNext Fit:";
    displayResult(allocation);

    int extFrag = calculateExternalFragmentation(blockSize, processSize);
    cout << "External Fragmentation: " << extFrag << endl;
}
*/

int main()
{
    int numBlocks, numProcesses;

    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;
    vector<int> blockSize(numBlocks);
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < numBlocks; i++)
    {
        cin >> blockSize[i];
    }

    cout << "\nEnter number of processes: ";
    cin >> numProcesses;
    vector<int> processSize(numProcesses);
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < numProcesses; i++)
    {
        cin >> processSize[i];
    }

    firstFit(blockSize, processSize);
    bestFit(blockSize, processSize);
    worstFit(blockSize, processSize);

    return 0;
}

/*
Enter number of memory blocks: 5
Enter sizes of memory blocks:
50 200 70 115 15

Enter number of processes: 10
Enter sizes of processes:
100 10 35 15 23 6 25 55 88 40

First Fit:
Process No.     Block No.
1               2
2               1
3               1
4               2
5               2
6               2
7               2
8               3
9               4
10              Not Allocated
External Fragmentation: 93

Best Fit:
Process No.     Block No.
1               4
2               4
3               1
4               1
5               3
6               5
7               3
8               2
9               2
10              2
External Fragmentation: 53

Worst Fit:
Process No.     Block No.
1               2
2               4
3               4
4               2
5               2
6               3
7               4
8               3
9               Not Allocated
10              2
External Fragmentation: 141
*/
