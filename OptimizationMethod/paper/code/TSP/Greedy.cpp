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
    if (x > n) {    //搜索到底
        Ans += Dis[Last][0];
        return;
    }
    int Min = numeric_limits<int>::max(), ID = 0;
    for (int i = 1; i <= n; i++) {  //找到未访问过的最近点的
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
int Greedy(const vector<vector<int>>& Dis, int n) {
    map<int, bool>Vis;
    int Ans = 0;
    Greedy(Dis, Vis, 1, 0, n, Ans);
    //这里使用了函数同名不同参的重载
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
    printf("%d\n", Greedy(Dis, n));
    return 0;
}
