#include <iostream>
#include <queue>
#include <array>
#include <vector>

using namespace std;

constexpr int N = 1e5 + 19;

class status
{
public:
    int pos;
    int dist;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    queue<status> q;
    q.push({1, 0});
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<int> visited(n + 1, 0);
    for (int _ = 0; _ < m; ++_)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    while (!q.empty())
    {
        status cur = q.front();
        q.pop();
        if (visited[cur.pos])
            continue;
        visited[cur.pos] = 1;
        if (cur.pos == n)
        {
            cout << cur.dist << '\n';
            return 0;
        }
        // 遍历邻接节点
        for (int neighbor : graph[cur.pos])
        {
            q.push({neighbor, cur.dist + 1});
        }
    }
    cout << -1 << '\n';
    return 0;
}
