#include <iostream>
#include <vector>

using namespace std;

vector<int> bars;

void buildArray()
{
    register int M, N, P, Q = 0;

    cin >> M >> N >> P >> Q;
    for (register int i = M; i <= N; i++)
    {
        for (register int j = P; j <= Q; j++)
        {
            bars.push_back(i);
            bars.push_back(j);
        }
    }
}

int GetChildren(int a , int b)
{
    // if( a == b)
    //     return 1;
    // else if ( a < b)
    //     {
    //         return (1 + (GetChildren(a, b-a)));
    //     }
    // else if ( a > b)
    //     {
    //         return (1 + (GetChildren(a-b, b)));
    //     }
    // else
    //     return NULL;
    register int children = 0;
    do 
    {
        if(a == b)
            children++;
        else if(a < b)
            {
                children++;
                b = b-a;
            }
        else if( a > b)
        {
            children++;
            a = a - b;
        }
    } while(a!=b);
    children++;
    return children;
}

int GetResult()
{
    int result = 0;
    register int a,b = 0;
    vector<int>::iterator vect_iter;
    vect_iter = bars.begin();
    while(vect_iter != bars.end())
    {
        //pass one bar to GetChildren which returns the number of children and store it in result
        a = *vect_iter;
        vect_iter++;
        b = *vect_iter;
        result += GetChildren(a,b);
        vect_iter++;
    }
    return result;
}

int main()
{
    int result = 0;
    buildArray();
    result = GetResult();
    cout<<result;
}