/*-----------------------------
        Author : TgX.2
       12Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>
using   namespace std;

#ifdef TGX
#include "debug.h"
#else
#define debug(...)
#endif

#define FOR(i, a, b)       for (int i = (a), _b = (b); i <= _b; i += 1)
#define FORD(i, a, b)      for (int i = (a), _b = (b); i >= _b; i -= 1)

#define fi                 first
#define se                 second
#define pb                 push_back
#define len(x)             (int)((x).size())
#define all(x)             (x).begin(), (x).end()

#define _                  << " " <<
#define __                 << "\n"
#define ___                << " "

#define ______________TgX______________ main()
// #define int                long long

template<typename T1, typename T2> 
bool mini(T1 &a, T2 b)
    {if (a > b) a = b; else return 0; return 1;}

template<typename T1, typename T2> 
bool maxi(T1 &a, T2 b)
    {if (a < b) a = b; else return 0; return 1;}
/*-----------------------------*/

const int maxn = 2e5 + 7;
const int logg  = 18;
int n, q, a[maxn];
vector<int> g[maxn];

array<int, 3> edge[maxn];

int par[logg][maxn];
int mmax[logg][maxn];
int dep[maxn];
void dfs(int u, int pre) {
    par[0][u] = pre;
    mmax[0][u] = a[u];

    for(const int &v : g[u]) if (v != pre) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

inline int get(int u, int v) {
    int ans = -1e9;

    if (dep[u] < dep[v]) swap(u, v);

    FORD(k, logg - 1, 0) {
        if (dep[u] - (1 << k) >= dep[v]) {
            ans = max(ans, mmax[k][u]);
            u = par[k][u];
        }
    }

    if (u == v) {
        maxi(ans, a[u]);
        return ans;
    }

    FORD(k, logg - 1, 0) {
        if (par[k][u] != 0 and par[k][u] != par[k][v]) {
            ans = max({ans, mmax[k][u], mmax[k][v]});
            u = par[k][u];
            v = par[k][v];
        }
    }
    return max({ans, a[u], a[v], a[par[0][u]]});
}

long long dp[maxn];


void process() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 2, n) {
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0);

    FOR(k, 1, logg - 1) {
        FOR(u, 1, n) {
            par[k][u] = par[k - 1][par[k - 1][u]];
            mmax[k][u] = max(mmax[k - 1][u], mmax[k - 1][par[k - 1][u]]);
        }
    }

    cin >> q;
    long long ans = 0;
    FOR(i, 0, n + 1) dp[i] = -1e18;
    dp[1] = 0LL;

    FOR(i, 1, q) {
        int u, v, w; cin >> u >> v;
        w = get(u, v);

        if (dp[u] != -1e9) {
            maxi(dp[v], dp[u] + w * 1LL);
            ans = max(ans, dp[v]);
        }
    }

    cout << ans;
}




/*-----------------------------*/
______________TgX______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    } else {
        freopen("SHIP.inp", "r", stdin);
        freopen("SHIP.out", "w", stdout);
    }
    process();
    cerr << "Time: " << 1.0 * clock() / CLOCKS_PER_SEC << " s." __ ;
}


/*==============================+
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|

===============================*/
