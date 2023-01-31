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
    for (int i = 0; i < n; i++) list.emplace_back(i);
    random_shuffle(list.begin(), list.end());
    return list;
}
int GA(vector<vector<int>>& Dis, int n) {
    srand(time(NULL));
    int W = 50, G = 10000;  //种群大小，迭代次数
    double pm = 0.1;    //变异概率
    vector<vector<int>>J; J.resize(W);
    for (int k = 0; k < W; k++) {   //通过最小环法生成W个初始染色体
        vector<int>c = randperm(n), _c;
        _c.emplace_back(0);
        for (auto p : c)    _c.push_back(p + 1);
        _c.emplace_back(0);
        J[k].resize(_c.size());
        while (true) {
            bool Flag = 0;
            for (int i = 1; i < n; i++)
                for (int j = i + 1; j <= n; j++)
                    if (Dis[_c[i - 1]][_c[j]] + Dis[_c[i]][_c[j + 1]] < Dis[_c[i - 1]][_c[i]] + Dis[_c[j]][_c[j + 1]])
                        reverse(_c.begin() + i, _c.begin() + j + 1), Flag |= true;
                            //如果更优则交换，直到不能交换为止
            if (!Flag) {
                _c.back() = n + 1;
                for (int i = 0; i < (int)_c.size(); i++)
                    J[k][_c[i]] = i;    //编码
                break;
            }
        }
    }
    double Ans = 0;
    for (int k = 0; k < G; k++) {
        vector<vector<int>>A = J;   //染色体交换种群
        vector<int>c = randperm(W);
        for (int i = 0; i < W; i += 2) {    //随机匹配，随机找断点
            int F = rand() % n + 1;
            for (int j = F; j <= n; j++)
                swap(A[c[i]][j], A[c[i + 1]][j]);
        }
        vector<int>by;  //随机找到一些变异的染色体编号
        while (by.empty())
            for (int i = 0; i < W; i++)
                if (1.0 * rand() / RAND_MAX < pm)
                    by.emplace_back(i);
        vector<vector<int>>B;
        for (auto p : by)   B.emplace_back(A[p]);
        for (int j = 0; j < (int)by.size(); j++) {
            vector<int>bw;
            while (true) {
                bw.clear();
                bw.emplace_back(0);
                bw.emplace_back(n + 2);
                for (int i = 0; i < 3; i++) //寻找断点
                    bw.emplace_back(rand() % n + 1);
                bool Flag = 0;
                sort(bw.begin(), bw.end());
                Flag |= (bw[0] == bw[1]) | (bw[1] == bw[2]);
                if (!Flag)  break;
            }
            vector<int>temp;    //染色体变异（自交换）
            for (int i = bw[0]; i < bw[1]; i++)     temp.emplace_back(B[j][i]);
            for (int i = bw[2]; i < bw[3]; i++)     temp.emplace_back(B[j][i]);
            for (int i = bw[1]; i < bw[2]; i++)     temp.emplace_back(B[j][i]);
            for (int i = bw[3]; i < bw[4]; i++)     temp.emplace_back(B[j][i]);
            B[j] = temp;
        }
        vector<vector<int>>G;   //新的种群 = 原种群 + 染色体交换 + 染色体变异
        for (auto p : J)    G.emplace_back(p);
        for (auto p : A)    G.emplace_back(p);
        for (auto p : B)    G.emplace_back(p);
        vector<int>VF;
        for (auto g : G) {
            vector<pair<int, int>>Index1;
            for (int i = 0; i < (int)g.size(); i++)
                Index1.emplace_back(MK(g[i], i));
            sort(Index1.begin(), Index1.end()); //解码
            int res = 0;
            for (int i = 1; i < (int)Index1.size(); i++)
                res += Dis[Index1[i - 1].second][Index1[i].second];
            VF.emplace_back(res);   //记录每个个体的代价
        }
        vector<pair<int, int>>Index2;   //给所有个体按照代价排序
        for (int i = 0; i < (int)VF.size(); i++)
            Index2.emplace_back(MK(VF[i], i));
        sort(Index2.begin(), Index2.end());
        J.clear();
        for (int i = 0; i < W; i++) //优胜劣汰，保留W个个体进行下一次迭代
            J.emplace_back(G[Index2[i].second]);
        Ans = Index2[0].first;  //记录最优的个体
    }
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
    printf("%d\n", GA(Dis, n));
    return 0;
}
