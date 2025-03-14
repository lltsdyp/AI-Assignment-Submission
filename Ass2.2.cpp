#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <utility>
using namespace std;

using status = std::pair<long long, int>;
const long long dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
long long pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const long long target = 123456780;

int main()
{
    long long n = 0;
    // 最先输入的是最高位，故倒序
    for (int i = 8; i >= 0; --i)
    {
        string s;
        cin >> s;
        char c = s[0];
        if (c == 'x')
        {
            n += pow10[i] * 0;
        }
        else
        {
            n += pow10[i] * (c - '0');
        }
    }

    queue<status> q;
    q.push({n, 0});
    unordered_set<long long> vis;
    int result = -1;

    while (!q.empty())
    {
        int board[3][3];
        int x, y;
        auto cur = q.front();
        q.pop();

        // 查重
        if (vis.count(cur.first))
            continue;
        vis.insert(cur.first);

        if (cur.first == target)
        {
            result = cur.second;
            break;
        }
        
        // 检查位置
        long long cur_loc = cur.first;
        for (int i = 2; i >= 0; i--)
            for (int j = 2; j >= 0; j--)
            {
                board[i][j] = cur_loc % 10;
                cur_loc /= 10;
                if (!board[i][j])
                    x = i, y = j;
            }

        // 尝试移动
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx > 2 || ny > 2)
                continue;
            swap(board[x][y], board[nx][ny]);

            long long new_loc = 0;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    // 同样的问题，最先出现的是最高位
                    new_loc += pow10[8-(i * 3 + j)] * (board[i][j]);

            if (!vis.count(new_loc))
            {
                q.push({new_loc, cur.second + 1});
            }
            swap(board[x][y], board[nx][ny]);
        }
    }
    cout << result << endl;
    return 0;
}