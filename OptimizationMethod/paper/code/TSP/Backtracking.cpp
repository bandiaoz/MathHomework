/*program from Wolfycz*/
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<limits.h>
#include<iostream>
#include<algorithm>
#define MK make_pair
#define sqr(x) ((x)*(x))
#define pii pair<int,int>
#define UNUSED(x) (void)(x)
using namespace std;
typedef long long ll;
template<typename T>inline T read(T x) {
    int f = 1; char ch = getchar();
    for (; ch < '0' || ch>'9'; ch = getchar())  if (ch == '-')  f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar())  x = (x << 1) + (x << 3) + ch - '0';
    return x * f;
}
void Dfs(int x, const vector<vector<int>>& Dis, map<int, bool>& Vis, int Last, int temp, int& Ans, int n) {
    if (temp >= Ans)   return;  //剪枝
    if (x > n) {
        Ans = min(Ans, temp + Dis[Last][0]);
        return;
    }
    for (int i = 1; i <= n; i++) {  //枚举当前位置填的数
        if (Vis[i]) continue;
        Vis[i] = true;
        Dfs(x + 1, Dis, Vis, i, temp + Dis[Last][i], Ans, n);
        Vis[i] = false;
    }
}
int Backtracking(const vector<vector<int>>& Dis, int n) {
    int Ans = numeric_limits<int>::max();
    map<int, bool>Vis;
    Dfs(1, Dis, Vis, 0, 0, Ans, n);
    return Ans;
}
int main() {
    int n = read(0);
    vector<vector<int>>Dis;
    for (int i = 0; i <= n; i++) {
        vector<int>temp;
        for (int j = 0; j <= n; j++)
            temp.emplace_back(read(0));
        Dis.emplace_back(temp);
    }
    printf("%d\n", Backtracking(Dis, n));
    return 0;
}
