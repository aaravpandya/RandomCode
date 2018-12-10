
#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

int N, M;
vector<int> pairs;
vector<int> visited_max;
class Graph
{
    int N;
    list<int> *adj;
    void traverseRecursively(int, int, bool[], int[], int &);

  public:
    Graph(int N);
    void insertEdge(int u, int v);
    void traversePaths(int s, int d);
};

Graph::Graph(int N)
{
    this->N = N + 1;
    adj = new list<int>[N + 1];
}

void Graph::insertEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::traversePaths(int s, int d)
{

    bool *visited = new bool[N];

    int *path = new int[N];
    int path_index = 0;

    for (int i = 0; i < N; i++)
        visited[i] = false;

    traverseRecursively(s, d, visited, path, path_index);
}

void Graph::traverseRecursively(int u, int d, bool visited[],
                                int path[], int &path_index)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    if (u == d)
    {
        for (int i = 0; i < path_index; i++)
        {
            visited_max[path[i]]++;
        }
    }
    else
    {
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                traverseRecursively(*i, d, visited, path, path_index);
    }

    path_index--;
    visited[u] = false;
}

void init()
{
    cin >> N >> M;
    Graph houses(N);
    int u, v;
    visited_max.push_back(0);
    for (int i = 0; i < (N - 1); i++)
    {
        cin >> u >> v;
        houses.insertEdge(u, v);
        houses.insertEdge(v, u);
        visited_max.push_back(0);
    }
    visited_max.push_back(0);
    int temp1, temp2;
    for (int i = 0; i < M; i++)
    {
        cin >> temp1 >> temp2;
        houses.traversePaths(temp1, temp2);
    }
}

int main()
{
    init();
    int max = 0;
    for (int i = 0; i < visited_max.size(); i++)
    {
        if (visited_max[i] > max)
        {
            max = visited_max[i];
        }
    }
    cout << max;
    return 0;
}
