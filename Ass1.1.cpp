#include <iostream>
#include <queue>
#include <array>
#include <vector>

using namespace std;

constexpr int N=1e5+19;

class status{
public:
    int pos;
    int dist;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    queue<status> q;
    q.push({1,0});
    cin>>n>>m;
    vector<vector<int>> graph(n+1,vector<int>(n+1,0));
    vector<int> visited(n+1,0);
    for(int _=0;_<m;++_)
    {
        int u,v;
        cin>>u>>v;
        graph[u][v]=1;
    }
    while(!q.empty())
    {
        status cur=q.front();
        q.pop();
        if(visited[cur.pos])
            continue;
        visited[cur.pos]=1;
        if(cur.pos==n)
        {
            cout<<cur.dist<<'\n';
            return 0;
        }
        for(int i=1;i<=n;++i)
        {
            if(graph[cur.pos][i]==1)
            {
                q.push({i,cur.dist+1});
            }
        }
    }
    cout<<-1<<'\n';
    return 0;
}
