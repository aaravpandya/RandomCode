// C++ program to demonstrate LCA of n-ary tree
// in constant time.
#include "bits/stdc++.h"
using namespace std;
#define sz 1000
#define MAXN 100000
#define dlevel 18

vector<int> adj[sz];  // stores the tree
vector<int> euler;    // tracks the eulerwalk
vector<int> depthArr; // depth for each node corresponding
                      // to eulerwalk
int depth[MAXN];
int parent[MAXN][dlevel];
int FAI[sz];    // stores first appearence index of every node
int level[sz];  // stores depth for all nodes in the tree
int ptr;        // pointer to euler walk
int dp[sz][18]; // sparse table
int logn[sz];   // stores log values
int p2[20];     // stores power of 2
vector<int> number;
void GetParents(int cur, int prev)
{
    depth[cur] = depth[prev] + 1;
    parent[cur][0] = prev;
    for (int i = 0; i < adj[cur].size(); i++)
    {
        if (adj[cur][i] != prev)
            GetParents(adj[cur][i], cur);
    }
}

void buildSparseTable(int n)
{
    // initializing sparse table
    memset(dp, -1, sizeof(dp));

    // filling base case values
    for (int i = 1; i < n; i++)
        dp[i - 1][0] = (depthArr[i] > depthArr[i - 1]) ? i - 1 : i;

    // dp to fill sparse table
    for (int l = 1; l < 15; l++)
        for (int i = 0; i < n; i++)
            if (dp[i][l - 1] != -1 and dp[i + p2[l - 1]][l - 1] != -1)
                dp[i][l] =
                    (depthArr[dp[i][l - 1]] > depthArr[dp[i + p2[l - 1]][l - 1]]) ? dp[i + p2[l - 1]][l - 1] : dp[i][l - 1];
            else
                break;
}

int query(int l, int r)
{
    int d = r - l;
    int dx = logn[d];
    if (l == r)
        return l;
    if (depthArr[dp[l][dx]] > depthArr[dp[r - p2[dx]][dx]])
        return dp[r - p2[dx]][dx];
    else
        return dp[l][dx];
}

void preprocess()
{
    // memorizing powers of 2
    p2[0] = 1;
    for (int i = 1; i < 18; i++)
        p2[i] = p2[i - 1] * 2;

    // memorizing all log(n) values
    int val = 1, ptr = 0;
    for (int i = 1; i < sz; i++)
    {
        logn[i] = ptr - 1;
        if (val == i)
        {
            val *= 2;
            logn[i] = ptr;
            ptr++;
        }
    }
}

/** 
* Euler Walk ( preorder traversal) 
* converting tree to linear depthArray 
* Time Complexity : O(n) 
* */
void dfs(int cur, int prev, int dep)
{
    // marking FAI for cur node
    if (FAI[cur] == -1)
        FAI[cur] = ptr;

    level[cur] = dep;

    // pushing root to euler walk
    euler.push_back(cur);

    // incrementing euler walk pointer
    ptr++;

    for (auto x : adj[cur])
    {
        if (x != prev)
        {
            dfs(x, cur, dep + 1);

            // pushing cur again in backtrack
            // of euler walk
            euler.push_back(cur);

            // increment euler walk pointer
            ptr++;
        }
    }
}

// Create Level depthArray corresponding
// to the Euler walk Array
void makeArr()
{
    for (auto x : euler)
        depthArr.push_back(level[x]);
}

void LCA(int u, int v)
{
    int x = u, y = v;
    int lca = -1;
    // trival case
    if (u == v)
        lca = u;

    else
    {
        if (FAI[u] > FAI[v])
            swap(u, v);

        // doing RMQ in the required range
        lca = euler[query(FAI[u], FAI[v])];
    }
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
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main(int argc, char const *argv[])
{
    // constructing the described tree
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
    // performing required precalculations
    preprocess();

    // doing the Euler walk
    ptr = 0;
    memset(FAI, -1, sizeof(FAI));
    dfs(1, 0, 0);
    GetParents(1, 0);
    // creating depthArray corresponding to euler[]
    makeArr();

    // building sparse table
    buildSparseTable(depthArr.size());

    // cout << "LCA(6,7) : " << LCA(6,7) << "\n";
    // cout << "LCA(6,4) : " << LCA(6,4) << "\n";
    for (int i = 0; i < M; i++)
    {
        cin >> temp1 >> temp2;
        LCA(temp1, temp2);
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
