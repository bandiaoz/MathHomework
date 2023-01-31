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
vector<int>randperm(int n) {
    vector<int>list;
    for (int i = 1; i <= n; i++) list.emplace_back(i);
    random_shuffle(list.begin(), list.end());
    return list;
}
int SA(vector<vector<int>>& Dis, int n) {
    srand(time(NULL));
    vector<int>list;
    int Min = numeric_limits<int>::max(), L = 1e3;
    for (int i = 1; i <= L; i++) {  //随机生成L个随机序列，取最优的一个作为初始序列
        vector<int>temp = randperm(n);
        temp.insert(temp.begin(), 0);
        temp.emplace_back(0);
        int res = 0;
        for (int j = 1; j < (int)temp.size(); j++)
            res += Dis[temp[j - 1]][temp[j]];
        if (res < Min) {
            Min = res;
            list = temp;
        }
    }
    double T = 1, a = 0.99999, e = 1e-30;   //T是初始问题，a是降温系数，e是临界值
    while (T >= e) {    //模拟退火的交换采用2-opt算法
        int l = rand() % n, r = rand() % n;
        while (l == r)
            l = rand() % n, r = rand() % n;
        if (l > r)    swap(l, r);
        l++, r++;
        int Delta = Dis[list[l - 1]][list[r]] + Dis[list[l]][list[r + 1]] - Dis[list[l - 1]][list[l]] - Dis[list[r]][list[r + 1]];
        if (Delta < 0 || 1.0 * rand() / RAND_MAX <= exp(-Delta / T))    //如果更优，或者更劣但是有概率进行旋转
            reverse(list.begin() + l, list.begin() + r + 1);
        T *= a; //降温
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
    printf("%d\n", SA(Dis, n));
    return 0;
}
