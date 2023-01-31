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
void Greedy(const vector<vector<int>>& Dis, map<int, bool>& Vis, int x, int Last, int n, int& Ans) {
    if (x > n) {
        Ans += Dis[Last][0];
        return;
    }
    int Min = numeric_limits<int>::max(), ID = 0;
    for (int i = 1; i <= n; i++) {
        if (Vis[i]) continue;
        if (Dis[Last][i] < Min) {
            Min = Dis[Last][i];
            ID = i;
        }
    }
    Vis[ID] = true;
    Ans += Dis[Last][ID];
    Greedy(Dis, Vis, x + 1, ID, n, Ans);
}
struct node {
    vector<int>list;
    map<int, bool>Vis;
    int Min;
    node() { Min = 0; }
    node(vector<int>list, map<int, bool>Vis, int Min) :list(list), Vis(Vis), Min(Min) {}
    bool operator<(const node& ots)const { return Min < ots.Min; }
    bool operator>(const node& ots)const { return Min > ots.Min; }
};
struct Mininums {   //存储两个最小数
    int M1, M2;
    Mininums(int M1 = numeric_limits<int>::max(), int M2 = numeric_limits<int>::max()) :M1(M1), M2(M2) {}
    void insert(int v) {
        if (v < M1)   M2 = M1, M1 = v;
        else    if (v < M2)   M2 = v;
    }
};
int calc(const vector<vector<int>>& Dis, vector<int>& list, map<int, bool>Vis, int n) {
    int Ans = 0;
    for (int i = 1; i < (int)list.size(); i++)
        Ans += Dis[list[i - 1]][list[i]];
    Ans <<= 1;
    for (int i = 0; i <= n; i++) {
        if (Vis[i] && i != list.front() && i != list.back())
            continue;
        Mininums temp;
        for (int j = 0; j <= n; j++) {
            if (i == j)   continue;
            temp.insert(Dis[i][j]);
        }
        Ans += temp.M1 + temp.M1;   //不在路径中的点计算该行最小的两个数
        if (i == list.front() || i == list.back())
            Ans -= temp.M2; //路径的两端记录最小的数
    }
    return (Ans + 1) >> 1;
}
int babm(const vector<vector<int>>& Dis, int n) {
    map<int, bool>Vis;
    int Max = 0;
    Greedy(Dis, Vis, 1, 0, n, Max); //贪心法计算上限
    priority_queue<node, vector<node>, greater<node>>H;
    H.push(node(vector<int>{0}, map<int, bool>{MK(0, true)}, 0));
    while (!H.empty()) {
        node Now = H.top();
        H.pop();
        if (Now.Min > Max)    continue;
        if ((int)Now.list.size() == n + 1) {
            int Ans = 0;
            for (int i = 1; i < (int)Now.list.size(); i++)
                Ans += Dis[Now.list[i - 1]][Now.list[i]];
            Ans += Dis[Now.list.back()][0];
            Max = min(Max, Ans);
            continue;
        }
        for (int i = 0; i <= n; i++) {  //枚举当前位置填的数
            if (Now.Vis[i]) continue;
            Now.list.emplace_back(i);
            Now.Vis[i] = true;
            int Min = calc(Dis, Now.list, Now.Vis, n);
            if (Min <= Max) //目标函数低于上界则加入队列
                H.push(node(Now.list, Now.Vis, Min));
            Now.list.pop_back();
            Now.Vis[i] = false;
        }
    }
    return Max;
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
    printf("%d\n", babm(Dis, n));
    return 0;
}
