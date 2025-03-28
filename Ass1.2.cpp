#include <climits>
#include <iostream>

using namespace std;

constexpr int N = 9999;
int graph[N][N];
int vis[N];
int dis[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  dis[1] = 0;
  for (int i = 2; i <= n; ++i) {
    dis[i] = INT_MAX >> 1; // 防止加爆了
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < n; ++j) {
      graph[i][j] = INT_MAX >> 1;
    }
  }

  for (int _ = 0; _ < m; ++_) {
    int u, v, cost;
    cin >> u >> v >> cost;
    if (cost < graph[u][v])
      graph[u][v] = cost;
  }
  for (int i = 1; i <= n; ++i) {
    int minNode = -1;
    for (int j = 1; j <= n; ++j) {
      if (!vis[i] && (minNode == -1 || dis[i] < dis[minNode]))
        minNode = i;
    }
    vis[minNode] = 1;
    for (int j = 1; j <= n; ++j) {
      int newDis = dis[minNode] + graph[minNode][j];
      if (newDis < dis[j])
        dis[j] = newDis;
    }
  }
  cout << (dis[n] == INT_MAX >> 1 ? -1 : dis[n]) << '\n';
  return 0;
}
