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
int Dynamic(int* w, int* v, int n, int m) {
    int F[m + 10], weight = 0;
    memset(F, 0, sizeof(F));
    for (int i = 1; i <= n; i++) {  //枚举每个物品
        weight += w[i];
        for (int j = min(weight, m); j >= w[i]; j--)    //倒序枚举更新
            F[j] = max(F[j], F[j - w[i]] + v[i]);
    }
    int Ans = 0;
    for (int i = m; i; i--)
        Ans = max(Ans, F[i]);
    return Ans;
}
const int N = 1e5;
int w[N + 10], v[N + 10];
int main() {
    int n = read(0), m = read(0);
    for (int i = 1; i <= n; i++)   w[i] = read(0);
    for (int i = 1; i <= n; i++)   v[i] = read(0);
    printf("%d\n", Dynamic(w, v, n, m));
    return 0;
}
