#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;
vector<int> number;

class Graph
{
    int V;
    list<int> *adj;

  public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int start, int end);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFS(int start, int end)
{

    typedef pair<int, list<int>::iterator> State;
    stack<State> to_do_stack;
    vector<int> path;
    vector<bool> visited(V, false);

    to_do_stack.push(make_pair(start, adj[start].begin()));
    visited[start] = true;
    path.push_back(start);

    while (!to_do_stack.empty())
    {

        State &current = to_do_stack.top();

        if (current.first == end || current.second == adj[current.first].end())
        {

            if (current.first == end)
            {

                for (int i = 0; i < path.size(); i++)
                {
                    number[path[i]]++;
                }

                break;
            }

            visited[current.first] = false;
            path.pop_back();
            to_do_stack.pop();
        }
        else
        {
            while (true)
            {
                if (current.second == adj[current.first].end())
                {
                    break;
                }

                int next = *current.second;

                current.second++;

                if (!visited[next])
                {

                    to_do_stack.push(make_pair(next, adj[next].begin()));
                    visited[next] = true;
                    path.push_back(next);
                    break;
                }
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;

    Graph g(N);
    number.resize(N);
    int temp1, temp2;
    for (int i = 0; i < (N - 1); i++)
    {
        cin >> temp1 >> temp2;
        g.addEdge(temp1 - 1, temp2 - 1);
        g.addEdge(temp2 - 1, temp1 - 1);
    }
    for (int i = 0; i < M; i++)
    {
        cin >> temp1 >> temp2;
        g.DFS(temp1 - 1, temp2 - 1);
    }
    int max = 0;
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] > max)
        {
            max = number[i];
        }
    }
    cout<< max;
    return 0;
}
