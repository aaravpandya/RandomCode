// Sparse Matrix DP approach to find LCA of two nodes
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAXN 100000
#define level 18

vector<int> tree[MAXN];
int depth[MAXN];
int parent[MAXN][level];
vector<int> number;
// pre-compute the depth for each node and their
// first parent(2^0th parent)
// time complexity : O(n)
void dfs(int cur, int prev)
{
    depth[cur] = depth[prev] + 1;
    parent[cur][0] = prev;
    for (int i = 0; i < tree[cur].size(); i++)
    {
        if (tree[cur][i] != prev)
            dfs(tree[cur][i], cur);
    }
}

// Dynamic Programming Sparse Matrix Approach
// populating 2^i parent for each node
// Time complexity : O(nlogn)
void precomputeSparseMatrix(int n)
{
    for (int i = 1; i < level; i++)
    {
        for (int node = 1; node <= n; node++)
        {
            if (parent[node][i - 1] != -1)
                parent[node][i] =
                    parent[parent[node][i - 1]][i - 1];
        }
    }
}

// Returning the LCA of u and v
// Time complexity : O(log n)
void DistributeGifts(int u, int v)
{
    int x = u, y = v;
    int lca = -1;
    if (depth[v] < depth[u])
        swap(u, v);

    int diff = depth[v] - depth[u];

    // Step 1 of the pseudocode
    for (int i = 0; i < level; i++)
        if ((diff >> i) & 1)
            v = parent[v][i];

    // now depth[u] == depth[v]
    if (u == v)
        lca = u;

    else
    {
        for (int i = level - 1; i >= 0; i--)
            if (parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }

        lca = parent[u][0];
    }
    // Step 2 of the pseudocode

    if (lca != x && lca != y)
    {
        int par = -1;
        int start = x;
        while (par != lca)
        {
            number[start]++;
            par = parent[start][0];
            start = par;
        }
        par = -1;
        start = y;
        while (par != lca)
        {
            number[start]++;
            par = parent[start][0];
            start = par;
        }
        number[lca]++;
    }
    else if (lca == x && lca != y)
    {
        int par = -1;
        int start = y;
        while (par != lca)
        {
            number[start]++;
            par = parent[start][0];
            start = par;
        }
        number[lca]++;
    }
    else if (lca == y && lca != x)
    {
        int par = -1;
        int start = x;
        while (par != lca)
        {
            number[start]++;
            par = parent[start][0];
            start = par;
        }
        number[lca]++;
    }
    else if (lca == x && lca == y)
    {
        number[lca]++;
    }
}

void addEdge(int u, int v)
{
    tree[u].push_back(v);
    tree[v].push_back(u);
}

// driver function
int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    number.resize(N + 1);
    memset(parent, -1, sizeof(parent));
    int temp1, temp2;
    for (int i = 0; i < (N - 1); i++)
    {
        cin >> temp1 >> temp2;
        addEdge(temp1, temp2);
    }

    depth[0] = 0;

    // running dfs and precalculating depth
    // of each node.
    dfs(1, 0);
    
    // Precomputing the 2^i th ancestor for evey node
    precomputeSparseMatrix(N);
    for (int i = 0; i < M; i++)
    {
        cin >> temp1 >> temp2;
        DistributeGifts(temp1, temp2);
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
    
    return 0;
}
