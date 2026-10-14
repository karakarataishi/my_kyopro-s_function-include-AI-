/**
作成者：karakarataishi
更新日：2026/10/14
概要：競プロに用いるテンプレート一覧（生成AIによるコードを含みます）
*/

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define inf (ll)0x7fffffffffffffff
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define rep2(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
ll mod = 998244353;

// pair<ll,ll>をハッシュ関数に変換するもの
// unordered_mapやunordered_setでpair<ll,ll>をキーとするときに用いる
// 宣言の方法　↓
// unordered_map<pair<ll,ll>,　値の型,　PairHash >
struct PairHash
{
    size_t operator()(const pair<ll, ll> &p) const
    {
        size_t h1 = hash<ll>{}(p.first);
        size_t h2 = hash<ll>{}(p.second);
        return h1 ^ (h2 << 32) ^ (h2 >> 32);
    }
};

// vector<ll>のハッシュ関数
struct VectorHash
{
    size_t operator()(const vector<ll> &v) const
    {
        size_t seed = v.size();
        for (auto x : v)
        {
            size_t h = hash<ll>{}(x);
            seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

bool which(vector<ll> A, vector<ll> B, ll turn)
{
    int n = A.size();

    unordered_map<ll, int> pos;
    for (int i = 0; i < n; i++)
    {
        pos[A[i]] = i;
    }

    vector<int> C(n);
    for (int i = 0; i < n; i++)
    {
        C[i] = pos[B[i]];
    }

    // BIT
    vector<int> bit(n + 1, 0);

    auto add = [&](int i)
    {
        for (i++; i <= n; i += i & -i)
            bit[i]++;
    };

    auto sum = [&](int i)
    {
        int s = 0;
        for (i++; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    };

    ll inv = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        inv += sum(C[i] - 1);
        add(C[i]);
    }

    return inv <= turn;
}

// セグメント木の使い方：https://qiita.com/tomoya2996/items/7d056676e95138ad93e4

// UnionFindの根をみつける（経路圧縮）
int GetRoot(int x, vector<int> &parent)
{
    if (parent[x] == x)
    {
        return parent[x];
    }
    int root = GetRoot(parent[x], parent);
    parent[x] = root;
    return root;
}

// Union-Findの結合
void UFmarge(int x, int y, vector<int> &parent)
{
    parent[GetRoot(x, parent)] = GetRoot(y, parent);
}

// Union-Findで、おなじグループに属しているか調べる
bool UFcheck(int x, int y, vector<int> &parent)
{
    return GetRoot(x, parent) == GetRoot(y, parent);
}

pair<int, int> GetRoot2(int x, int y, vector<vector<pair<int, int>>> &parent)
{
    if (parent[x][y] == make_pair(x, y))
    {
        return parent[x][y];
    }
    int px = parent[x][y].first;
    int py = parent[x][y].second;
    pair<int, int> root = GetRoot2(px, py, parent);
    parent[x][y] = root;
    return root;
}
// Union-Findの結合
void UFmarge2(int sx, int sy, int gx, int gy, vector<vector<pair<int, int>>> &parent)
{
    pair<int, int> s = GetRoot2(sx, sy, parent);
    int psx = s.first;
    int psy = s.second;
    parent[psx][psy] = GetRoot2(gx, gy, parent);
}

// Union-Findで、おなじグループに属しているか調べる
bool UFcheck2(int sx, int sy, int gx, int gy, vector<vector<pair<int, int>>> &parent)
{
    return GetRoot2(sx, sy, parent) == GetRoot2(gx, gy, parent);
}

// ワーシャルフロイド
// dist配列の初期値は inf / 2にしておく
void warshall_floyd(int n, vector<vector<ll>> &d)
{
    for (int k = 0; k < n; k++)
    { // 経由する頂点
        for (int i = 0; i < n; i++)
        { // 始点
            for (int j = 0; j < n; j++)
            { // 終点
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
// 2つの文字列を2進数として変換するもの（値は10進数返す）
ll moji(string S, char A, char B)
{
    int n = S.size();
    ll sum = 0;
    rep(i, n)
    {
        if (S[i] == A)
        {
            sum += (ll)pow(2, i);
        }
    }
    return sum;
}

// 整数nから、したからiビット目、kビットの値を抽出する関数
ll get_bit(ll n, ll i, ll k)
{
    return (n >> i) % (ll)pow(2, k);
}

// 最大公約数を求める関数
ll gcd(ll a, ll b)
{
    // aとbの値の大きさが逆転しているときに修正をする
    if (a < b)
    {
        ll c = a;
        a = b;
        b = c;
    }
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        return gcd(b, a % b);
    }
}

// 2 ~ nまでに含まれる素数のリストを作成する関数
vector<ll> get_sosu(ll n)
{
    vector<ll> list_sosu;
    vector<bool> sosu_check(n + 1, false);
    for (int i = 2; i <= n; i++)
    {
        if (sosu_check[i])
            continue;
        for (int j = i; j <= n; j += i)
        {
            if (i == j)
                continue;
            sosu_check[j] = true;
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (!sosu_check[i])
            list_sosu.push_back(i);
    }
    return list_sosu;
}

// 桁数を入手する関数
ll get_keta(ll n, ll k)
{
    int cnt = 0;
    while (1)
    {
        n /= k;
        cnt++;
        if (n == 0)
        {
            return cnt;
        }
    }
}

// popcount(2進数にしたときの各桁が1である個数)
int popcount(ll num)
{
    int cnt = 0;
    while (num != 0)
    {
        if (num % 2 == 1)
        {
            cnt++;
        }
        num /= 2;
    }
    return cnt;
}

// (a^b)%pの値を求める関数（繰り返し二乗法）
ll power(ll a, ll b, ll p)
{
    if (b == 0)
    {
        return 1;
    }
    ll now = b;
    ll tmp = a;
    ll res = 1;
    while (1)
    {
        if (now % 2 == 1)
        {
            res = (res * tmp) % p;
        }
        tmp = (tmp * tmp) % p;
        now /= 2;
        if (now == 0)
        {
            break;
        }
    }
    return res;
}

// a の mod m の 逆元を求める
ll modinv(ll a, ll m)
{
    ll b = m, u = 1, v = 0;
    while (b)
    {
        ll t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    u %= m;
    if (u < 0)
        u += m;
    return u;
}

// % mod で階乗の計算をおこなう関数
void calc_kai(vector<ll> &kai, ll mod)
{
    kai[0] = 1;
    rep2(i, 1, kai.size())
    {
        kai[i] = (kai[i - 1] * i) % mod;
    }
}

// % mod で階乗の逆数の計算を行う関数
// kai : % mod で階乗の値を保存している値
// inv : 階乗の逆元を格納する配列
// mod : あまり
void calc_inv(vector<ll> &kai, vector<ll> &inv, ll mod)
{
    int n = kai.size() - 1;
    inv[n] = modinv(kai[n], mod);
    for (int i = n - 1; i >= 0; i--)
    {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
}

// 組み合わせの計算を行う関数
// kai : 階乗の配列、modを取って状態で用意しておく
// mod : あまり
// nCrを求めるために...
// （１）kai配列を用意、calc_kai関数にぶち込む
// （２）inv配列を用意、calc_inv関数にぶち込む
ll nCr(ll n, ll r, vector<ll> &kai, vector<ll> &inv, ll mod)
{
    if (n < r)
        return 0;
    return (kai[n] * ((inv[r] * inv[n - r]) % mod)) % mod;
}

// 負の値でmod p を取るための関数
ll nmod(ll a, ll p)
{
    return ((a % p) + p) % p;
}

// 4方向への探索を行う関数（幅探索で用いる）
// x, y : 周りを探索する座標の中心のこと
// h, w : グリッドの幅、高さ
// num_turn : 現在のターン（初期値からのマンハッタン距離）
// check : グリッドの各座標が探索可能かを格納する二次元配列
// turn : グリッドのターン数を格納する二次元配列
// tansaku : 探索した座標をキューに格納する
void grid_move_haba(int x, int y, int h, int w, int num_turn, vector<vector<bool>> &check, vector<vector<int>> &turn, queue<pair<int, int>> &tansaku)
{
    x--;
    if (x > 0 && !check[x][y])
    {
        tansaku.push(make_pair(x, y));
        turn[x][y] = num_turn;
        check[x][y] = true;
    }
    x++;
    y++;
    if (y < w && !check[x][y])
    {
        tansaku.push(make_pair(x, y));
        turn[x][y] = num_turn;
        check[x][y] = true;
    }
    x++;
    y--;
    if (x < h && !check[x][y])
    {
        tansaku.push(make_pair(x, y));
        turn[x][y] = num_turn;
        check[x][y] = true;
    }
    x--;
    y--;
    if (y > 0 && !check[x][y])
    {
        tansaku.push(make_pair(x, y));
        turn[x][y] = num_turn;
        check[x][y] = true;
    }
}

// ダイクストラを行う関数
// graph : 有向、無向でもおけ
// que : <重さ、座標>の順に入れよう
// dist 距離配列
void dijkstra(vector<vector<pair<ll, ll>>> &graph, priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> &que, vector<ll> &dist)
{
    while (!que.empty())
    {
        auto now = que.top();
        que.pop();
        int x = now.second;
        ll w = now.first;
        if (dist[x] < w)
            continue;
        // cout << x <<  " " << w << endl;
        rep(i, graph[x].size())
        {
            int y = graph[x][i].second;
            ll now_w = graph[x][i].first;
            if (dist[y] > w + now_w)
            {
                dist[y] = min(dist[y], w + now_w);
                que.push(make_pair(w + now_w, y));
            }
        }
    }
}

// 偏角ソートを行う関数
struct point
{
    int x, y;
};

long long cross(const point &a, const point &b)
{
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

bool cmp(const point &a, const point &b)
{
    int ah = (a.y < 0 or (a.y == 0 and a.x < 0));
    int bh = (b.y < 0 or (b.y == 0 and b.x < 0));
    if (ah != bh)
        return ah < bh;
    return cross(a, b) > 0;
}

void argument_sort(vector<point> &points)
{
    sort(points.begin(), points.end(), cmp);
}

// 出次数が1、サイクル数が1の有向グラフに用いる構造体
// to[v]...頂点vの次の頂点
// indeg[v]...頂点vの入次数
// in_cycle[v]...頂点vがcycleに属するか
// cycle_id[v]...頂点vが族sるcycleの番号
// cycle_size[c]...cycle番号cのcycleの長さ
// dist[v]...頂点vからcycleまでの距離
// インスタンスで宣言してから、頂点を追加、その後build()を実行すると使えるようになる。
struct FunctionalGraph
{
    int n;
    vector<int> to;
    vector<int> indeg;

    vector<int> dist;     // cycleまでの距離
    vector<int> cycle_id; // 属するcycle番号
    vector<int> cycle_size;
    vector<bool> in_cycle;

    FunctionalGraph(int n) : n(n), to(n), indeg(n, 0),
                             dist(n, -1), cycle_id(n, -1), in_cycle(n, false) {}

    void add_edge(int u, int v)
    {
        to[u] = v;
        indeg[v]++;
    }

    void build()
    {
        queue<int> q;

        // cycleでない部分を削る（トポロジカル削除）
        for (int i = 0; i < n; i++)
        {
            if (indeg[i] == 0)
                q.push(i);
        }

        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            int u = to[v];
            indeg[u]--;
            if (indeg[u] == 0)
                q.push(u);
        }

        // cycle検出
        int cid = 0;
        for (int i = 0; i < n; i++)
        {
            if (indeg[i] > 0 && cycle_id[i] == -1)
            {
                int cur = i;
                int sz = 0;
                while (cycle_id[cur] == -1)
                {
                    cycle_id[cur] = cid;
                    in_cycle[cur] = true;
                    cur = to[cur];
                    sz++;
                }
                cycle_size.push_back(sz);
                cid++;
            }
        }

        // dist計算（逆辺）
        vector<vector<int>> rev(n);
        for (int i = 0; i < n; i++)
        {
            rev[to[i]].push_back(i);
        }

        queue<int> q2;
        for (int i = 0; i < n; i++)
        {
            if (in_cycle[i])
            {
                dist[i] = 0;
                q2.push(i);
            }
        }

        while (!q2.empty())
        {
            int v = q2.front();
            q2.pop();
            for (int u : rev[v])
            {
                if (dist[u] == -1)
                {
                    dist[u] = dist[v] + 1;
                    cycle_id[u] = cycle_id[v];
                    q2.push(u);
                }
            }
        }
    }
};

int main()
{
}
