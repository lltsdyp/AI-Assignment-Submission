#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class status {
public:
  int pos;
  int dist;
  bool operator>(const status &other) const { return dist > other.dist; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  priority_queue<status, vector<status>, greater<status>> q;
  cin >> n >> m;

  // 初始化邻接表
  vector<vector<pair<int, int>>> adj(n + 1);

  // 防止加爆
  vector<int> dist(n + 1, INT_MAX >> 1);
  dist[1] = 0;
  q.push({1, 0});

  for (int _ = 0; _ < m; ++_) {
    int u, v, cost;
    cin >> u >> v >> cost;
    adj[u].emplace_back(v, cost);
  }

  while (!q.empty()) {
    status cur = q.top();
    q.pop();

    if (cur.dist > dist[cur.pos])
      continue;

    if (cur.pos == n) {
      cout << cur.dist << '\n';
      return 0;
    }

    for (const auto &edge : adj[cur.pos]) {
      int neighbor = edge.first;
      int new_dist = cur.dist + edge.second;
      // 更新更短路径
      if (new_dist < dist[neighbor]) {
        dist[neighbor] = new_dist;
        q.push({neighbor, new_dist});
      }
    }
  }

  // 无法到达终点
  cout << -1 << '\n';
  return 0;
}