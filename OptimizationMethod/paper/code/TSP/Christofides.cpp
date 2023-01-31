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
struct FLOWER {
    const static int N = 5e2;
    struct edge {
        int u, v, w;
        edge(int u = 0, int v = 0, int w = 0) :u(u), v(v), w(w) {}
    }g[N][N];
    int lab[N], slack[N], F[N], pa[N], flower_from[N][N], S[N], Vis[N], match[N];
    int n, m, n_x;
    vector<int>flower[N];
    deque<int>q;
    int dist(const edge& e) { return lab[e.u] + lab[e.v] - (g[e.u][e.v].w << 1); }
    void update_slack(int u, int x) {
        if (!slack[x] || dist(g[u][x]) < dist(g[slack[x]][x]))
            slack[x] = u;
    }
    void set_slack(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; u++)
            if (g[u][x].w > 0 && F[u] != x && !S[F[u]])
                update_slack(u, x);
    }
    void push(int x) {
        if (x <= n) return q.push_back(x);
        for (int i = 0; i < (int)flower[x].size(); i++)
            push(flower[x][i]);
    }
    void set_st(int x, int b) {
        F[x] = b;
        if (x <= n)   return;
        for (auto p : flower[x])
            set_st(p, b);
    }
    int get_pr(int x, int v) {
        int pr = find(flower[x].begin(), flower[x].end(), v) - flower[x].begin();
        if (pr & 1) {
            reverse(flower[x].begin() + 1, flower[x].end());
            return (int)flower[x].size() - pr;
        }
        else   return pr;
    }
    void set_match(int x, int y) {
        match[x] = g[x][y].v;
        if (x <= n)   return;
        edge e = g[x][y];
        int xr = flower_from[x][e.u], pr = get_pr(x, xr);
        for (int i = 0; i < pr; i++)
            set_match(flower[x][i], flower[x][i ^ 1]);
        set_match(xr, y);
        rotate(flower[x].begin(), flower[x].begin() + pr, flower[x].end());
    }
    void augment(int x, int y) {
        int temp = F[match[x]];
        set_match(x, y);
        if (!temp)  return;
        set_match(temp, F[pa[temp]]);
        augment(F[pa[temp]], temp);
    }
    int get_lca(int x, int y) {
        static int t = 0;
        for (++t; x || y; swap(x, y)) {
            if (!x) continue;
            if (Vis[x] == t)  return x;
            Vis[x] = t;
            x = F[match[x]];
            if (x)  x = F[pa[x]];
        }
        return 0;
    }
    void add_blossom(int u, int lca, int v) {
        int b = n + 1;
        while (b <= n_x && F[b])    b++;
        if (b > n_x)  ++n_x;
        lab[b] = S[b] = 0;
        match[b] = match[lca];
        flower[b].clear();
        flower[b].emplace_back(lca);
        for (int x = u, y; x != lca; x = F[pa[y]]) {
            flower[b].emplace_back(x);
            flower[b].emplace_back(y = F[match[x]]);
            push(y);
        }
        reverse(flower[b].begin() + 1, flower[b].end());
        for (int x = v, y; x != lca; x = F[pa[y]]) {
            flower[b].emplace_back(x);
            flower[b].emplace_back(y = F[match[x]]);
            push(y);
        }
        set_st(b, b);
        for (int x = 1; x <= n_x; x++)  g[b][x].w = g[x][b].w = 0;
        for (int x = 1; x <= n; x++)    flower_from[b][x] = 0;
        for (int i = 0; i < (int)flower[b].size(); i++) {
            int temp = flower[b][i];
            for (int x = 1; x <= n_x; x++)
                if (g[b][x].w == 0 || dist(g[temp][x]) < dist(g[b][x]))
                    g[b][x] = g[temp][x], g[x][b] = g[x][temp];
            for (int x = 1; x <= n; x++)
                if (flower_from[temp][x])
                    flower_from[b][x] = temp;
        }
        set_slack(b);
    }
    void expand_blossom(int b) {
        for (int i = 0; i < (int)flower[b].size(); i++)
            set_st(flower[b][i], flower[b][i]);
        int xr = flower_from[b][g[b][pa[b]].u], pr = get_pr(b, xr);
        for (int i = 0; i < pr; i += 2) {
            int xs = flower[b][i], xns = flower[b][i + 1];
            pa[xs] = g[xns][xs].u;
            S[xs] = 1, S[xns] = 0;
            slack[xs] = 0, set_slack(xns);
            push(xns);
        }
        S[xr] = 1, pa[xr] = pa[b];
        for (int i = pr + 1; i < (int)flower[b].size(); i++) {
            int xs = flower[b][i];
            S[xs] = -1, set_slack(xs);
        }
        F[b] = 0;
    }
    bool on_found_edge(const edge& e) {
        int Fu = F[e.u], Fv = F[e.v];
        if (!~S[Fv]) {
            pa[Fv] = e.u, S[Fv] = 1;
            int nu = F[match[Fv]];
            slack[Fv] = slack[nu] = 0;
            S[nu] = 0, push(nu);
        }
        if (!S[Fv]) {
            int lca = get_lca(Fu, Fv);
            if (!lca) {
                augment(Fu, Fv);
                augment(Fv, Fu);
                return true;
            }
            else   add_blossom(Fu, lca, Fv);
        }
        return false;
    }
    bool matching() {
        memset(S, 0xff, sizeof(S));
        memset(slack, 0x00, sizeof(slack));
        q.clear();
        for (int i = 1; i <= n_x; i++) {
            if (F[i] == i && !match[i]) {
                pa[i] = S[i] = 0;
                push(i);
            }
        }
        if (q.empty())  return false;
        while (true) {
            while (!q.empty()) {
                int u = q.front(); q.pop_front();
                if (S[F[u]] == 1)   continue;
                for (int v = 1; v <= n; v++) {
                    if (g[u][v].w > 0 && F[u] != F[v]) {
                        if (dist(g[u][v]) == 0) {
                            if (on_found_edge(g[u][v]))
                                return true;
                        }
                        else update_slack(u, F[v]);
                    }
                }
            }
            int d = numeric_limits<int>::max();
            for (int i = n + 1; i <= n_x; i++)
                if (F[i] == i && S[i] == 1)
                    d = min(d, lab[i] >> 1);
            for (int i = 1; i <= n_x; i++) {
                if (F[i] == i && slack[i]) {
                    if (!~S[i]) d = min(d, dist(g[slack[i]][i]));
                    if (!S[i])  d = min(d, dist(g[slack[i]][i]) >> 1);
                }
            }
            for (int i = 1; i <= n; i++) {
                if (!S[F[i]]) {
                    if (lab[i] <= d)  return false;
                    lab[i] -= d;
                }
                if (S[F[i]] == 1) lab[i] += d;
            }
            for (int i = n + 1; i <= n_x; i++) {
                if (F[i] == i) {
                    if (!S[F[i]])       lab[i] += d << 1;
                    if (S[F[i]] == 1)   lab[i] -= d << 1;
                }
            }
            q.clear();
            for (int i = 1; i <= n_x; i++)
                if (F[i] == i && slack[i] && F[slack[i]] != i && !dist(g[slack[i]][i]))
                    if (on_found_edge(g[slack[i]][i]))
                        return true;
            for (int i = n + 1; i <= n_x; i++)
                if (F[i] == i && S[i] == 1 && !lab[i])
                    expand_blossom(i);
        }
        return false;
    }
    void weight_blossom() {
        memset(match, 0x00, sizeof(match));
        n_x = n;
        for (int i = 0; i <= n; i++)
            F[i] = i, flower[i].clear();
        int wMax = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                flower_from[i][j] = i == j ? i : 0;
                wMax = max(wMax, g[i][j].w);
            }
        }
        for (int i = 1; i <= n; i++)  lab[i] = wMax;
        while (matching());
        return;
    }
}fl;    //带花树
struct GRAPH {
    const static int N = 5e2, M = N << 1;
    int pre[(M << 1) + 10], now[N + 10], child[(M << 1) + 10], Degree[N + 10], tot;
    bool Vis[(M << 1) + 10];
    GRAPH() { tot = 1; }
    void link(int x, int y) { pre[++tot] = now[x], now[x] = tot, child[tot] = y, Degree[y]++; }
    void connect(int x, int y) { link(x, y), link(y, x); }
    void Dfs(vector<int>& res, int x) { //Dfs暴力寻找欧拉回路
        res.push_back(x);
        if (res.size() > 1 && res.front() == res.back())    return;
        for (int p = now[x]; p; p = pre[p]) {
            if (Vis[p]) continue;
            Vis[p] = Vis[p ^ 1] = 1;
            int son = child[p];
            Degree[x]--, Degree[son]--;
            Dfs(res, son);
            if (res.front() == res.back())  return;
        }
    }
    void euler(int x, vector<int>& list) {  //欧拉回路
        vector<int>res;
        Dfs(res, x);
        for (auto p : res) {
            if (Degree[p])  euler(p, list);
            else    list.push_back(p);
        }
    }
}Graph;
struct Line {
    int x, y, v;
    Line(int x = 0, int y = 0, int v = 0) :x(x), y(y), v(v) {}
    bool operator<(const Line& ots)const { return v < ots.v; }
};
int Christofides(const vector<vector<int>>& Dis, int n) {
    vector<Line>lines;
    vector<int>Fa, Degree(n + 1);
    function<int(int)>Find = [&](int x) {return x == Fa[x] ? x : Fa[x] = Find(Fa[x]); };
    for (int i = 0; i <= n; i++)
        Fa.emplace_back(i);
    int Max = numeric_limits<int>::min();
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            lines.emplace_back(Line(i, j, Dis[i][j]));
            Max = max(Max, Dis[i][j]);
        }
    }
    sort(lines.begin(), lines.end());
    for (auto line : lines) {   //生成MST，并建图
        int Fx = 0, Fy = 0;
        if ((Fx = Find(line.x)) != (Fy = Find(line.y))) {
            Fa[Fx] = Fy;
            Degree[line.x]++;
            Degree[line.y]++;
            Graph.connect(line.x, line.y);
        }
    }
    int list[n + 1], m = 0;
    for (int i = 0; i <= n; i++)
        if (Degree[i] & 1)
            list[++m] = i;
    for (int i = 1; i <= m; i++)    //找到奇度数点加入带花树
        for (int j = 1; j <= m; j++)
            fl.g[i][j] = FLOWER::edge(i, j, Max - Dis[list[i]][list[j]]);
    fl.n = m;
    fl.weight_blossom();    //求最大带权匹配
    for (int i = 1; i <= m >> 1; i++)
        Graph.connect(list[i], list[fl.match[i]]);  //最大匹配与MST加入同一个图
    vector<int>Euler, Hamilton;
    Graph.euler(0, Euler);  //找到新图的欧拉回路
    map<int, bool>Vis;
    for (auto p : Euler) {  //通过欧拉回路生成哈密顿回路
        if (!Vis[p])    Hamilton.emplace_back(p);
        Vis[p] = true;
    }
    Hamilton.emplace_back(Hamilton.front());
    int Ans = 0;
    for (int i = 0; i < (int)Hamilton.size(); i++)
        Ans += Dis[Hamilton[i]][Hamilton[i + 1]];
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
    printf("%d\n", Christofides(Dis, n));
    return 0;
}
