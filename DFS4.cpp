// An Iterative C++ program to do DFS traversal from 
// a given source vertex. DFS(int s) traverses vertices 
// reachable from s. 
#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std; 
vector<int> number;
// This class represents a directed graph using adjacency 
// list representation 
class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // adjacency lists 
public: 
	Graph(int V); // Constructor 
	void addEdge(int v, int w); // to add an edge to graph 
	void DFS(int start, int end); // prints all vertices in DFS manner 
	// from a given source. 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

// prints all not yet visited vertices reachable from s 
// DFS(int s) 
// { 
// 	// Initially mark all verices as not visited 
// 	vector<bool> visited(V, false); 

// 	// Create a stack for DFS 
// 	stack<int> stack; 

// 	// Push the current source node. 
// 	stack.push(s); 
//     auto i;
// 	while (!stack.empty()) 
// 	{ 
// 		// Pop a vertex from stack and print it 
// 		s = stack.top(); 
// 		// stack.pop(); needs to be popped only when backtracked and has no neighbours

// 		// Stack may contain same vertex twice. So 
// 		// we need to print the popped item only 
// 		// if it is not visited. 
// 		if (!visited[s]) 
// 		{ 
// 			cout << s << " "; 
// 			visited[s] = true; 
// 		} 

// 		// Get all adjacent vertices of the popped vertex s 
// 		// If a adjacent has not been visited, then puah it 
// 		// to the stack. 
// 		for (i = adj[s].begin(); i != adj[s].end(); ++i) 
// 			if (!visited[*i]) 
// 				stack.push(*i); 
// 	} 
// } 
void Graph::DFS(int start, int end)
{
    // for(int i =0; i<V; i++)
    // {   
    //     cout<<i<<" -> ";
    //     for (auto j = adj[i].begin(); j != adj[i].end(); ++j) 
    //     {
    //         cout<<*j<<" -> ";
    //     }
    //     cout<<endl;
    // }

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
        // cout<<endl<<"Current is: "<<current.first<<"  "<<*current.second;
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
            while(true)
            {
                int ctr = 0;
                int next = *current.second;
                if(!(current.second == adj[current.first].end()))
                    current.second++;
                else
                    ctr++;
                if(!visited[next])
                {
                    // cout<<endl<<"Next is "<<next;
                    to_do_stack.push(make_pair(next,adj[next].begin()));
                    visited[next] = true;
                    path.push_back(next);
                    break;
                }
                else if(ctr)
                {
                    break;
                }

            }
        }
    }
}
// Driver program to test methods of graph class 
int main() 
{ 
    int N,M;
    cin>>N>>M;

	Graph g(N); 
    number.resize(N);
    int temp1, temp2;
    for(int i =0 ; i<(N-1); i++)
    {
        cin>>temp1>>temp2;
        g.addEdge(temp1-1, temp2-1);
        g.addEdge(temp2-1, temp1-1);
    }
    for(int i = 0; i < M; i++)
    {
        cin>>temp1>>temp2;
        g.DFS(temp1-1,temp2-1);
    }
	int max = 0;
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] > max)
        {
            max = number[i];
        }
    }
    cout<<endl<<max;
	return 0; 
} 
