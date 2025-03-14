#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <array>
#include <utility>
using namespace std;

const long long dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
long long pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000ll, 100000000ll, 1000000000ll};
const long long target = 123456780;

set<long long> vis;
// map<long long,int> vis;
// multiset<long long> vis;

bool dfs(long long cur,int depth)
{
    if(depth>31) // Korf, Richard E.(1985) Depth-First Iterative Deepening: An Optimal Admissible Tree Search
        return false; // 论文中说最多31步，这里设置一个大于31但不算太大的数应该都是可以的
    if(cur==target)
        return true;
    
    // 获取当前各个数码位置
    int board[3][3];
    int x,y;

    if(vis.count(cur)) // 不剪枝必报TLE
        return false;
    vis.insert(cur);
    // vis[cur]=1;

    long long cur_loc=cur;
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
                new_loc += pow10[8 - (i * 3 + j)] * (board[i][j]);
        swap(board[x][y], board[nx][ny]);

        if(new_loc==target)
            return true;

        // if(vis.count(new_loc))
        //     continue;
        // vis.insert(new_loc);
        if(dfs(new_loc,depth+1))
            return true;
    }
    vis.erase(cur);
    // vis[cur]=0;
    return false;
}

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

    if (dfs(n,0))
        cout << "1" << endl;
    else
        cout << "0" << endl;
    return 0;
}
