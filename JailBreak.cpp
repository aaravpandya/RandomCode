#include <iostream>
#include <vector>

using namespace std;
int X,R,N = 0;
int GetJumps(int a)
{
    int jumps = 0;
    int current_height = 0;
    while(true)
    {
        
        jumps++;
        current_height += X;
        if((a-current_height) <= 0)
        {
            return jumps;
        }
        else
            current_height -= R;
    }
}

int Jumps(){
    cin>>X>>R>>N;
    int input;
    vector<int> walls;
    for(int i = 0 ; i < N; i++)
    {
        cin>>input;
        walls.push_back(input);
    }
    int result = 0;
    for(int i = 0; i< N; i++)
    {
        result += GetJumps(walls[i]);
    }
    return result;
}



int main()
{
    cout<<Jumps();
}