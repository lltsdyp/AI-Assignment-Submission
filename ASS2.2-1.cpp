#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <utility>
using namespace std;

using status = pair<int, long long>;
const long long dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
long long pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const long long target = 123456780;

int main()
{
    long long n = 0;
    for (int i = 8; i >= 0; --i)
    {
        string s;
        cin >> s;
        char c = s[0];
        if (c == 'x')
            n += pow10[i] * 0;
        else
            n += pow10[i] * (c - '0');
    }

    priority_queue<status, vector<status>, greater<status>> pq;
    unordered_map<long long, int> dist;
    dist[n] = 0;
    pq.push({0, n});

    unordered_set<long long> visited;
    int result = -1;

    while (!pq.empty())
    {
        int board[3][3];
        int x, y;
        auto cur = pq.top();
        pq.pop();
        int current_steps = cur.first;
        long long current_state = cur.second;

        // 查重
        if (visited.count(current_state))
            continue;
        visited.insert(current_state);

        if (current_steps > dist[current_state])
            continue;

        if (current_state == target)
        {
            result = current_steps;
            break;
        }

        // 检查位置
        long long cur_loc = current_state;
        for (int i = 2; i >= 0; i--)
            for (int j = 2; j >= 0; j--)
            {
                board[i][j] = cur_loc % 10;
                cur_loc /= 10;
                if (!board[i][j])
                    x = i, y = j;
            }

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx > 2 || ny > 2)
                continue;
            swap(board[x][y], board[nx][ny]);

            long long new_state = 0;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    // 同样的问题，最先出现的是最高位
                    new_state += pow10[8 - (i * 3 + j)] * board[i][j];

            int new_steps = current_steps + 1;
            if (dist.find(new_state) == dist.end() || new_steps < dist[new_state])
            {
                dist[new_state] = new_steps;
                pq.push({new_steps, new_state});
            }

            swap(board[x][y], board[nx][ny]);
        }
    }
    cout << result << endl;
    return 0;
}