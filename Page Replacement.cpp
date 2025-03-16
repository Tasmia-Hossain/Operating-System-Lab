#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to check if a page is present in the frame
bool isPagePresent(vector<int> &frames, int page)
{
    for (int f : frames)
        if (f == page)
            return true;
    return false;
}

// FIFO
void fifo(vector<int> pages, int capacity)
{
    vector<int> frames;
    int pageFaults = 0;

    for (int page : pages)
    {
        if (!isPagePresent(frames, page))
        {
            if (frames.size() < capacity)
            {
                frames.push_back(page);
            }
            else
            {
                frames.erase(frames.begin());
                frames.push_back(page);
            }
            pageFaults++;
        }
    }

    cout << "\nFIFO Page Faults: " << pageFaults << endl;
}

// Optimal
void optimal(vector<int> pages, int capacity)
{
    vector<int> frames;
    //unordered_map<int, int> lastUsed;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        if (!isPagePresent(frames, pages[i]))
        {
            if (frames.size() < capacity)
            {
                frames.push_back(pages[i]);
            }
            else
            {
                int farthest = -1, index = -1;
                //bool futureUseExists = false;
                for (int j = 0; j < frames.size(); j++)
                {
                    int nextUse = -1;
                    for (int k = i + 1; k < pages.size(); k++)
                    {
                        if (pages[k] == frames[j])
                        {
                            nextUse = k;
                            //futureUseExists = true;
                            break;
                        }
                    }
                    if (nextUse == -1)
                    {
                        index = j;
                        //futureUseExists = false;
                        break;
                    }
                    if (nextUse > farthest)
                    {
                        farthest = nextUse;
                        index = j;
                    }
                }
                /*
                if (!futureUseExists)
                {
                    int mruIndex = 0;
                    for (int j = 1; j < frames.size(); j++)
                    {
                        if (lastUsed[frames[j]] > lastUsed[frames[mruIndex]])
                        {
                            mruIndex = j;
                        }
                    }
                    index = mruIndex;
                }
                */
                frames[index] = pages[i];
            }
            pageFaults++;
        }
        //lastUsed[pages[i]] = i;
    }

    cout << "\nOptimal Page Faults: " << pageFaults << endl;
}

// LRU
void lru(vector<int> pages, int capacity)
{
    vector<int> frames;
    unordered_map<int, int> lastUsed;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        if (!isPagePresent(frames, pages[i]))
        {
            if (frames.size() < capacity)
            {
                frames.push_back(pages[i]);
            }
            else
            {
                int lruIndex = 0;
                for (int j = 1; j < frames.size(); j++)
                {
                    if (lastUsed[frames[j]] < lastUsed[frames[lruIndex]])
                    {
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = pages[i];
            }
            pageFaults++;
        }
        lastUsed[pages[i]] = i;
    }

    cout << "\nLRU Page Faults: " << pageFaults << endl;
}

int main()
{
    int numPages, capacity;

    cout << "Enter number of pages: ";
    cin >> numPages;
    vector<int> pages(numPages);
    cout << "Enter the reference string:\n";
    for (int i = 0; i < numPages; i++)
    {
        cin >> pages[i];
    }

    cout << "Enter the number of frames: ";
    cin >> capacity;

    fifo(pages, capacity);
    optimal(pages, capacity);
    lru(pages, capacity);

    return 0;
}

/*
Enter number of pages: 20
Enter the reference string:
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Enter the number of frames: 3

FIFO Page Faults: 15

Optimal Page Faults: 9

LRU Page Faults: 12
*/
