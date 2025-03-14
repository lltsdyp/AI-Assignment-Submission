#include <iostream>
#include <queue>

using namespace std;

constexpr int N=2e5+1;
int graph[N][N];
int vis[N];

class status{
public:
    int pos;
    int dist;
    bool operator<(const status& other) const { 
        return dist < other.dist;
    }
    bool operator>(const status& other) const{
        return dist > other.dist;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    priority_queue<status,vector<status>,greater<status>> q;
    q.push({1,0});
    cin>>n>>m;
    for(int _=0;_<m;++_)
    {
        int u,v,cost;
        cin>>u>>v>>cost;
        if(graph[u][v]==0 || cost<graph[u][v])
            graph[u][v]=cost;
    }
    while(!q.empty())
    {
        status cur=q.top();
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
            if(graph[cur.pos][i]!=0)
            {
                q.push({i,cur.dist+graph[cur.pos][i]});
            }
        }
    }
    cout<<-1<<'\n';
    return 0;
}
