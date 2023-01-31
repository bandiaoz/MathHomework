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
int calc(int* w, int* v, int* id, int x, int weight, int value, int n, int m) {
    return value + ceil(1.0 * (m - weight) * v[id[x]] / w[id[x]]);
}   //目标函数
struct node {
    int x, w, v, Max;
    node(int x = 0, int w = 0, int v = 0) :x(x), w(w), v(v) { Max = 0; }
    bool operator<(const node& ots)const { return Max < ots.Max; }
};
int Bfs(int* w, int* v, int* id, int x, int n, int m) {
    priority_queue<node>H;  //优先队列，优先扩展目标函数值更大的节点
    H.push(node(x, 0, 0));
    int weight = 0, Min = 0;
    for (int i = 1; i <= n; i++) {  //计算下界
        if (weight + w[id[i]] > m)  continue;
        weight += w[id[i]];
        Min += v[id[i]];
    }
    while (!H.empty()) {
        node Now = H.top();
        H.pop();
        if (Now.x > n) {    //找到一个可行解，更新下界
            Min = max(Min, Now.v);
            continue;
        }
        node ls(Now.x + 1, Now.w, Now.v);   //不选
        node rs(Now.x + 1, Now.w + w[id[Now.x]], Now.v + v[id[Now.x]]); //选
        ls.Max = calc(w, v, id, ls.x, ls.w, ls.v, n, m);
        rs.Max = calc(w, v, id, rs.x, rs.w, rs.v, n, m);
        if (ls.w <= m && (ls.x > n || ls.Max >= Min)) H.push(ls);
        if (rs.w <= m && (rs.x > n || rs.Max >= Min)) H.push(rs);
        //满足限制，且目标值不低于下界，则加入队列
    }
    return Min;
}
int babm(int* w, int* v, int n, int m) {
    int id[n + 10];
    for (int i = 1; i <= n; i++)  id[i] = i;
    sort(id + 1, id + 1 + n, [=](int x, int y) {return v[x] * w[y] >= v[y] * w[x]; });
    return Bfs(w, v, id, 1, n, m);
}
const int N = 1e5;
int w[N + 10], v[N + 10];
int main() {
    int n = read(0), m = read(0);
    for (int i = 1; i <= n; i++)   w[i] = read(0);
    for (int i = 1; i <= n; i++)   v[i] = read(0);
    printf("%d\n", babm(w, v, n, m));
    return 0;
}
