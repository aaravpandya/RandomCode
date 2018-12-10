
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int N, M;
vector<int> pairs;
vector<int> visited_max;
class Graph
{
    int N;
    vector<vector<int>> adj_matrix;
    void traverseRecursively(int, int, bool[], int[], int &);

  public:
    Graph(int N);
    void insertEdge(int u, int v);
    void traversePaths(int s, int d);
};

Graph::Graph(int N)
{
    this->N = N;
    adj_matrix.resize(N + 1);
    for (int i = 0; i < (N + 1); i++)
    {
        adj_matrix[i].resize(N + 1);
    }
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            if (i == j)
                adj_matrix[i][j] = 0;
            else
                adj_matrix[i][j] = 0;
        }
    }
}

void Graph::insertEdge(int u, int v)
{
    adj_matrix[u][v] = 1;
}

void Graph::traversePaths(int s, int d)
{
    // cout<<endl;
    // for(int i = 0 ; i<(N+1); i++)
    // {
    //     for(int j = 0; j<(N+1);j++)
    //     {
    //         cout<<adj_matrix[i][j]<<"\t\t";

    //     }
    //     cout<<endl;
    // }

    // cout << endl
    //      << "Beginning s = " << s << " and d = " << d;
    bool *visited = new bool[N+1];

    int *path = new int[N+1];
    int path_index = 0;

    for (int i = 0; i < (N + 1); i++)
        visited[i] = false;

    traverseRecursively(s, d, visited, path, path_index);
}

void Graph::traverseRecursively(int u, int d, bool visited[],
                                int path[], int &path_index)
{
    // cout << endl
    //      << "traverseRecursively beg u = " << u;
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    if (u == d)
    {
        // cout << endl
        //      << "here in if(u==d)";
        for (int i = 0; i < path_index; i++)
        {
            visited_max[path[i]]++;
        }
    }
    else
    {
        for (int j = 1; j < (N + 1); j++)
        {
            // cout << endl
            //      << "here in for    "<<j;
            if (!visited[j])
            {
                // cout << endl
                //      << "in if u and f: " << u << "  " << j;
                if(adj_matrix[u][j] == 1)
                {
                    // cout<<endl<<"xyz";
                traverseRecursively(j, d, visited, path, path_index);
                }
                // cout<<endl<<"after if IN IF";
            }
    // cout<<endl<<"AFTER IF";
        }
    }
    // cout<<endl<<"AFTER ELSE";
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
