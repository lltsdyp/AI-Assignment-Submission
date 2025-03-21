#include <iostream>
#include <queue>
#include <list>
#include <climits>

using namespace std;

constexpr int N=9999;
// int graph[N][N];
// int vis[N];

class status{
public:
    int pos;
    int dist;
};

// 实现小顶堆（不含堆优化）
class pq_no_heap{
private:
    std::list<status> q;
public:
    pq_no_heap()=default;
    ~pq_no_heap()=default;
    void push(status s) {
        auto it = q.begin();
        while (it != q.end() && it->dist < s.dist) {
            ++it;
        }
        q.insert(it, s);  
    }

    void pop() {
        if (!q.empty()) {
            q.pop_front(); 
        }
    }

    status front() const {
        return q.front();
    }

    bool empty() const {
        return q.empty();
    }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    pq_no_heap q;
    q.push({1,0});
    cin>>n>>m;
    vector<vector<int>> graph(n+1,vector<int>(n+1,0));
    vector<int> vis(n+1,INT_MAX);
    for(int _=0;_<m;++_)
    {
        int u,v,cost;
        cin>>u>>v>>cost;
        if(graph[u][v]==0 || cost<graph[u][v])
            graph[u][v]=cost;
    }
    while(!q.empty())
    {
        status cur=q.front();
        q.pop();
        if(cur.dist>vis[cur.pos])
            continue;
        vis[cur.pos]=cur.dist;
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
