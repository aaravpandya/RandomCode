#include <iostream>
#include <vector>
#include <stack>

using namespace std;
vector<int> number;
void dfs(int start, int end, const vector<vector<int>> graph)
{

    typedef pair<int, int> State;
    stack<State> to_do_stack;
    vector<int> path;
    vector<bool> visited(graph.size(), false);

    to_do_stack.push(make_pair(start, 0));
    visited[start] = true;
    path.push_back(start);

    while (!to_do_stack.empty())
    {
        State &current = to_do_stack.top();

        if (current.first == end || current.second == graph[current.first].size())
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
            int next = 0;
            int ctr = 0;

            while (true)
            {

                next = graph[current.first][current.second];
                if (next == 0 && current.second < graph[current.first].size())
                    current.second++;
                else
                {
                    if (next == 1)
                    {
                        next = current.second;
                        current.second++;
                        if (!visited[next])
                        {

                            to_do_stack.push(make_pair(next, 0));
                            visited[next] = true;
                            path.push_back(next);
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                break;
            }
        }
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph;
    graph.resize(N);
    for (register int i = 0; i < (N); i++)
    {
        graph[i].resize(N);
    }
    number.resize(graph.size());
    int temp1, temp2;
    for (int i = 0; i < (N - 1); i++)
    {
        cin >> temp1 >> temp2;
        graph[temp1 - 1][temp2 - 1] = 1;
        graph[temp2 - 1][temp1 - 1] = 1;
    }
    for (int i = 0; i < M; i++)
    {
        cin >> temp1 >> temp2;
        dfs(temp1 - 1, temp2 - 1, graph);
    }
    int max = 0;
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] > max)
        {
            max = number[i];
        }
    }
    cout << max;
}