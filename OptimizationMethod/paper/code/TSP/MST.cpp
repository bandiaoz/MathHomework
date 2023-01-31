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
int MST(vector<vector<int>>& Dis, int n) {
    struct Line {
        int x, y, v;
        Line(int x = 0, int y = 0, int v = 0) :x(x), y(y), v(v) {}
        bool operator<(const Line& ots)const { return v < ots.v; }
    };
    vector<Line>lines;
    vector<int>Fa, Vert[n + 1];
    function<int(int)>Find = [&](int x) {return x == Fa[x] ? x : Fa[x] = Find(Fa[x]); };
    //并查集
    for (int i = 0; i <= n; i++)    Fa.emplace_back(i);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            lines.emplace_back(Line(i, j, Dis[i][j]));
    sort(lines.begin(), lines.end());
    for (auto line : lines) {   //Kruskal算法求解MST
        int Fx = 0, Fy = 0;
        if ((Fx = Find(line.x)) != (Fy = Find(line.y))) {
            Fa[Fx] = Fy;
            Vert[line.x].emplace_back(line.y);
            Vert[line.y].emplace_back(line.x);
        }
    }
    vector<int>list;
    function<void(int, int)>Dfs = [&](int x, int fa) {  //Dfs查找前序遍历
        list.emplace_back(x);
        for (auto son : Vert[x]) {
            if (son == fa)    continue;
            Dfs(son, x);
        }
    };
    Dfs(0, 0);
    list.emplace_back(list.front());
    int Ans = 0;
    for (int i = 1; i < (int)list.size(); i++)
        Ans += Dis[list[i - 1]][list[i]];
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
    printf("%d\n", MST(Dis, n));
    return 0;
}