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
int BruteForce(int* w, int* v, int n, int m) {
    int Ans = numeric_limits<int>::min();
    for (int sta = 0; sta < 1 << n; sta++) {
        int value = 0, weight = 0;
        for (int i = 0; i < n; i++) {
            if (!(sta >> i & 1))    continue;
            weight += w[i + 1];
            value += v[i + 1];
        }
        if (weight <= m)    //如果合法
            Ans = max(Ans, value);
    }
    return Ans;
}
const int N = 1e5;
int w[N + 10], v[N + 10];
int main() {
    int n = read(0), m = read(0);
    for (int i = 1; i <= n; i++)   w[i] = read(0);
    for (int i = 1; i <= n; i++)   v[i] = read(0);
    printf("%d\n", BruteForce(w, v, n, m));
    return 0;
}
