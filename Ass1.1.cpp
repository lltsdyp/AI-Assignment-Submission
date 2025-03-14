#include <iostream>
#include <queue>

using namespace std;

constexpr int N=1e5+19;
int graph[N][N];
int vis[N];

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
        if(vis[cur.pos])
            continue;
        vis[cur.pos]=1;
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
