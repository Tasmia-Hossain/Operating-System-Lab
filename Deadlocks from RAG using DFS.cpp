//Write a code to detect and print deadlock(s) from RAG using DFS.
#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void addEdge(unordered_map<string, vector<string>>& graph, const string& from, const string& to)
{
    graph[from].push_back(to);
}

bool detectCycle(const string& node, unordered_map<string, vector<string>>& graph, unordered_set<string>& visited, unordered_set<string>& stack)
{
    if (stack.count(node))
        return true;
    if (visited.count(node))
        return false;

    visited.insert(node);
    stack.insert(node);

    for (const string& neighbor : graph[node])
    {
        if (detectCycle(neighbor, graph, visited, stack))
            return true;
    }

    stack.erase(node);
    return false;
}

void detectDeadlock(unordered_map<string, vector<string>>& graph)
{
    unordered_set<string> visited;
    unordered_set<string> stack;

    for (const auto& pair : graph)
    {
        if (!visited.count(pair.first) && detectCycle(pair.first, graph, visited, stack))
        {
            cout << "Deadlock detected!" << endl;
            return;
        }
    }
    cout << "No deadlock detected." << endl;
}

int main()
{
    unordered_map<string, vector<string>> graph;
    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter edges (from to):" << endl;
    for (int i = 0; i < edges; i++) {
        string from, to;
        cin >> from >> to;
        addEdge(graph, from, to);
    }

    detectDeadlock(graph);
    return 0;
}

/*
Enter the number of edges: 4
Enter edges (from to):
P1 R1
R1 P2
P2 R2
R2 P1
Deadlock detected!
*/
