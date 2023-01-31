/*program from Wolfycz*/
#include<map>
#include<cmath>
#include<ctime>
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
int K_OPT(vector<vector<int>>& Dis, int n) {
    srand(time(NULL));
    vector<int>list(1, 0);
    for (int i = 1; i <= n; i++)  list.emplace_back(i);
    list.emplace_back(0);
    random_shuffle(list.begin() + 1, list.end() - 1);   //生成随机序列
    int Limit = 1e3, Times = 0;
    while (true) {
        if (Times > Limit)    break;
        int l = rand() % n, r = rand() % n; //随机生成两个断点
        while (l == r)  //断点不能相同
            l = rand() % n, r = rand() % n;
        if (l > r)    swap(l, r);
        l++, r++;
        int Saving = Dis[list[l - 1]][list[l]] + Dis[list[r]][list[r + 1]] - Dis[list[l - 1]][list[r]] - Dis[list[l]][list[r + 1]];
        if (Saving > 0) {   //判断是否交换
            Times = 0;
            reverse(list.begin() + l, list.begin() + r + 1);
        }
        else Times++;
    }
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
    printf("%d\n", K_OPT(Dis, n));
    return 0;
}
