/*program from Wolfycz*/
#include<map>
#include<set>
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
#define lowbit(x) ((x)&(-x))
using namespace std;
typedef long long ll;
template<typename T>inline T read(T x) {
    int f = 1; char ch = getchar();
    for (; ch < '0' || ch>'9'; ch = getchar())  if (ch == '-')  f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar())  x = (x << 1) + (x << 3) + ch - '0';
    return x * f;
}
int Dynamic(const vector<vector<int>>& Dis, int n) {
    int F[n + 1][1 << (n + 1)];
    memset(F, 0x7f, sizeof(F));
    F[0][1] = 0;    //初始在0号点
    for (int sta = 0; sta < 1 << (n + 1); sta++)
        for (int i = 0; i <= n; i++)
            if (sta >> i & 1)   //枚举集合中的点i
                for (int k = 0; k <= n; k++)
                    if (sta >> k & 1 && i != k)   //枚举集合中另一个点k，从k走到i
                        F[i][sta] = min(F[i][sta], F[k][sta ^ (1 << i)] + Dis[k][i]);
    int Ans = numeric_limits<int>::max();
    for (int i = 1; i <= n; i++)
        Ans = min(Ans, F[i][(1 << (n + 1)) - 1] + Dis[i][0]);
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
    printf("%d\n", Dynamic(Dis, n));
    return 0;
}
