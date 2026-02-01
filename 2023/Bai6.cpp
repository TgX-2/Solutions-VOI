#include <stdio.h>

#include <algorithm>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define TASK "FOOD"
const int N = 5e3 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;
using Line = pair<long long, long long>;
#define a first
#define b second

int n, s;
int Q[N], W[N], C[N];
vector<int> adj[N];

long long eval(Line f, long long x) {
    return f.a * x + f.b;
}

deque<Line> d;

long long get_intersection(Line a, Line b) {
    long long x = (b.b - a.b) / (a.a - b.a);
    while (eval(a, x) <= eval(b, x)) {
        x--;
    }
    while (eval(a, x) > eval(b, x)) {
        x++;
    }
    return x;
}

long long get_min(long long x) {
    while ((d.size() > 1) && (eval(d[1], x) <= eval(d[0], x))) d.pop_front();
    return eval(d.front(), x);
}

void insert(long long a, long long b) {
    Line cur = {a, b};
    while (d.size() >= 2 && get_intersection(d.back(), d[d.size() - 2]) >= get_intersection(cur, d.back())) {
        d.pop_back();
    }
    d.push_back(cur);
}

int tree[N], time_out[N];
int Time;
long long f[N][N];

void dfs(int u, int p = -1) {
    ++Time;
    tree[Time] = u;
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
    }
    time_out[u] = Time;
}

void solve() {
    memset(f, 0x3f, sizeof(f));
    Time = 0;
    dfs(1);
    f[n + 1][0] = 0;
    for (int i = n; i >= 1; i--) {
        int u = tree[i];
        for (int j = 0; j <= Q[u]; j++) {
            long long cur = min<long long>(s, 1ll * W[u] * j);
            f[i][cur] = min(f[i][cur], 1ll * j * j * C[u]);
        }
        for (int j = 0; j <= s; j++) {
            f[i][j] = min(f[i][j], f[time_out[u] + 1][j]);
        }
        for (int mod = 0; mod < W[u]; mod++) {
            d.clear();
            int k = 0;
            for (int j = mod; j <= s; j += W[u]) {
                while (d.size()) {
                    int last_k = d.front().a / (-2ll * C[u]);
                    if (k - last_k > Q[u]) {
                        d.pop_front();
                    } else {
                        break;
                    }
                }
                if (d.size()) {
                    f[i][j] = min(f[i][j], get_min(k) + 1ll * k * k * C[u]);
                }
                if (f[i + 1][j] != INF) {
                    insert(-2ll * k * C[u], 1ll * k * k * C[u] + f[i + 1][j]);
                }
                k++;
            }
        }
        for (int j = s; j >= 0; j--) {
            f[i][j] = min(f[i][j], f[i][j + 1]);
        }
    }
    cout << (f[1][s] == INF ? -1 : f[1][s]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if (fopen(TASK ".INP", "r")) {
        freopen(TASK ".INP", "r", stdin);
        freopen(TASK ".OUT", "w", stdout);
    }
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> Q[i] >> W[i] >> C[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    solve();
    return 0;
}
