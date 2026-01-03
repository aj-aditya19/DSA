#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph
{
    int V;
    list<int> *l;

public:
    Graph(int V)
    {
        this->V = V;
        l = new list<int>[V];
    }
    void addEdge(int u, int v)
    {
        l[u].push_back(v);
        // l[v].push_back(u);
    }
    void printGraph()
    {
        for (int i = 0; i < V; i++)
        {
            cout << i << "- ";
            for (int neigh : l[i])
            {
                cout << neigh << " ";
            }
            cout << endl;
        }
    }
    void bfs()
    {
        queue<int> q;
        vector<bool> vis(V, false);
        q.push(0);
        vis[0] = true;
        while (q.size() > 0)
        {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int v : l[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
    void dfshelper(int u, vector<bool> &vis)
    {
        vis[u] = true;
        cout << u << " ";
        for (int v : l[u])
        {
            if (!vis[v])
            {
                dfshelper(v, vis);
            }
        }
    }
    void dfs()
    {
        vector<bool> vis(V, false);
        dfshelper(0, vis);
        cout << endl;
    }
    void dfsdircyclehelper(int u, vector<bool> &vis, vector<bool> &inStack)
    {
        vis[u] = true;
        inStack[u] = true;
        cout << u << " ";

        for (int v : l[u])
        {
            if (!vis[v])
            {
                dfsdircyclehelper(v, vis, inStack);
            }
            else if (inStack[v])
            {
                cout << "\nCycle Detected\n";
                return;
            }
        }

        inStack[u] = false;
    }
    void dfsdircycle() // count how many cycles also 3 is the proof
    {
        vector<bool> vis(V, false);
        vector<bool> inStack(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                dfsdircyclehelper(i, vis, inStack);
            }
        }
        cout << endl;
    }
    bool bfsundircyclehelper(int src, vector<bool> &vis)
    {
        queue<pair<int, int>> q;
        q.push({src, -1});
        vis[src] = true;
        while (q.size() > 0)
        {
            int u = q.front().first;
            int partU = q.front().second;
            q.pop();
            list<int> neighbour = l[u];
            for (int v : neighbour)
            {
                if (!vis[v])
                {
                    q.push({v, u});
                    vis[v] = true;
                }
                else if (v != partU)
                {
                    return true;
                }
            }
        }
        return false;
    }
    void bfsundircycle()
    {
        int count = 0;
        vector<bool> vis(V, false);
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (bfsundircyclehelper(i, vis))
                {
                    count++;
                }
            }
        }
        cout << count << endl;
    }
    bool dfsundircyclehelper(int u, int parent, vector<bool> &vis)
    {
        vis[u] = true;

        for (int v : l[u])
        {
            if (!vis[v])
            {
                if (dfsundircyclehelper(v, u, vis))
                    return true;
            }
            else if (v != parent)
            {
                return true;
            }
        }
        return false;
    }

    void dfsundircycle()
    {
        vector<bool> vis(V, false);
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (dfsundircyclehelper(i, -1, vis))
                {
                    cout << "Cycle Detected\n";
                    return;
                }
            }
        }
        cout << "No Cycle\n";
    }
    bool bfsdircycle()
    {
        vector<int> indegree(V, 0);
        for (int u = 0; u < V; u++)
        {
            for (int v : l[u])
            {
                indegree[v]++;
            }
        }
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
        int count = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            count++;
            for (int v : l[u])
            {
                indegree[v]--;
                if (indegree[v] == 0)
                {
                    q.push(v);
                }
            }

            return count != V;
        }
    }
};
int main()
{
    Graph g(5);
    g.addEdge(2, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 1);
    g.addEdge(3, 1);
    g.addEdge(1, 4);
    g.addEdge(4, 0);
    g.printGraph();
    g.bfs(); // -> first neigbhour
    g.dfs(); // -> first unvisited
    // Cycle detection
    g.dfsdircycle();   //-> directed graph by dfs
    g.dfsundircycle(); //-> undirected graph by dfs
    g.bfsdircycle();
    g.bfsundircycle(); //-> undirected graph by bfs
    return 0;
}