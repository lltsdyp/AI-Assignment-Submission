#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>
using namespace std;

using status = std::tuple<long long, int, string>;
const long long dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
const char action[]={'u','l','r','d'};
long long pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const long long target = 123456780;


// 小顶堆构造
class cmp {
public:
    bool operator()(const status& a, const status& b) {
        return get<1>(a) > get<1>(b);
    }
};

// 曼哈顿距离作代价函数
int cost(long long loc)
{
    int board[3][3];
    long long temp = loc;
    for (int i = 2; i >= 0; --i)
    {
        for (int j = 2; j >= 0; --j)
        {
            board[i][j] = temp % 10;
            temp /= 10;
        }
    }

    int total = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int num = board[i][j];
            if (num == 0)
                continue;
            int target_i = (num - 1) / 3;
            int target_j = (num - 1) % 3;
            total += abs(i - target_i) + abs(j - target_j);
        }
    }
    return total;
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
    priority_queue<status,vector<status>,cmp> pq;
    pq.push({n, cost(n),""});
    unordered_map<long long,string> vis;
    string result = "unsolvable";

    while (!pq.empty())
    {
        int board[3][3];
        int x, y;
        auto cur = pq.top();
        pq.pop();

        // 查重
        if (vis.count(get<0>(cur)))
            continue;
        vis[get<0>(cur)]=get<2>(cur);

        if (get<0>(cur) == target)
        {
            result = get<2>(cur);
            break;
        }

        // 检查位置
        long long cur_loc = get<0>(cur);
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

            if (!vis.count(new_loc))
            {
                pq.push({new_loc, get<1>(cur) + 1 - cost(get<0>(cur)) + cost(new_loc),
                    get<2>(cur) + action[i]});
            }
            swap(board[x][y], board[nx][ny]);
        }
    }
    cout << result << endl;
    return 0;
}
