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
int Greedy(int* w, int* v, int n, int m) {
    int id[n + 10];
    for (int i = 1; i <= n; i++)  id[i] = i;
    sort(id + 1, id + 1 + n, [=](int x, int y) {return v[x] * w[y] >= v[y] * w[x]; });  //按单位价值排序
    int weight = 0, value = 0;
    for (int i = 1; i <= n; i++) {  //贪心选取
        if (weight + w[id[i]] > m)  continue;
        weight += w[id[i]];
        value += v[id[i]];
    }
    return value;
}
const int N = 1e5;
int w[N + 10], v[N + 10];
int main() {
    int n = read(0), m = read(0);
    for (int i = 1; i <= n; i++)   w[i] = read(0);
    for (int i = 1; i <= n; i++)   v[i] = read(0);
    printf("%d\n", Greedy(w, v, n, m));
    return 0;
}
