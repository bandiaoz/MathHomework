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
int ClarkeWright(vector<vector<int>>& Dis, int n) {
    struct node {
        int x, y, f;
        node(int x = 0, int y = 0, int f = 0) :x(x), y(y), f(f) {}
        bool operator<(const node& ots)const { return f > ots.f; }
    };
    vector<node>pairs;
    for (int i = 1; i <= n; i++)    //统计点对
        for (int j = 1; j < i; j++)
            pairs.emplace_back(node(i, j, Dis[0][i] + Dis[j][0] - Dis[i][j]));
    sort(pairs.begin(), pairs.end());
    vector<int>list[n + 1], Frm(n + 1);
    for (int i = 1; i <= n; i++)    //每个序列初始只包含自己
        list[Frm[i] = i].emplace_back(i);
    for (auto pair : pairs) {
        int Fx = Frm[pair.x], Fy = Frm[pair.y];
        if (Fx == Fy) continue; //如果在同一个序列中则跳过
        if (list[Fx].front() != pair.x && list[Fx].back() != pair.x)    continue;
        if (list[Fy].front() != pair.y && list[Fy].back() != pair.y)    continue;
        //不在序列头/尾则跳过
        if (list[Fx].front() == pair.x) reverse(list[Fx].begin(), list[Fx].end());
        if (list[Fy].back() == pair.y)  reverse(list[Fy].begin(), list[Fy].end());
        //同一方向
        for (auto p : list[Fy]) {   //将y所在序列加入x中
            Frm[p] = Fx;
            list[Fx].emplace_back(p);
        }
        list[Fy].clear();
    }
    Frm[0] = Frm[1];
    list[Frm[0]].insert(list[Frm[0]].begin(), 0);
    list[Frm[0]].emplace_back(0);   //在序列头尾加上0，统计答案
    int Ans = 0;
    for (int i = 1; i < (int)list[Frm[0]].size(); i++)
        Ans += Dis[list[Frm[0]][i - 1]][list[Frm[0]][i]];
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
    printf("%d\n", ClarkeWright(Dis, n));
    return 0;
}
