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
void Dfs(int* w, int* v, int x, int weight, int value, int n, int m, int& Ans) {
    if (x > n) {
        if (weight <= m)
            Ans = min(Ans, value);
        return;
    }
    Dfs(w, v, x + 1, weight, value, n, m, Ans); //不选
    Dfs(w, v, x + 1, weight + w[x], value + v[x], n, m, Ans);   //选
}
int Backtracking_Prune(int* w, int* v, int n, int m) {
    int Ans = numeric_limits<int>::min();
    Dfs(w, v, 1, 0, 0, n, m, Ans);
    return Ans;
}
const int N = 1e5;
int w[N + 10], v[N + 10];
int main() {
    int n = read(0), m = read(0);
    for (int i = 1; i <= n; i++)   w[i] = read(0);
    for (int i = 1; i <= n; i++)   v[i] = read(0);
    printf("%d\n", Backtracking_Prune(w, v, n, m));
    return 0;
}
