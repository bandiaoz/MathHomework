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
int Enumerative(const vector<vector<int>>& Dis, int n) {
    int p[n + 10], Ans = numeric_limits<int>::max();
    for (int i = 1; i <= n; i++)  p[i] = i;
    p[0] = p[n + 1] = 0;
    do {
        int temp = 0;
        for (int i = 0; i <= n; i++)
            temp += Dis[p[i]][p[i + 1]];
        Ans = min(Ans, temp);
    } while (next_permutation(p + 1, p + 1 + n));
    //next_permutation生成下一个全排列，复杂度是均摊O(1)的
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
    printf("%d\n", Enumerative(Dis, n));
    return 0;
}
