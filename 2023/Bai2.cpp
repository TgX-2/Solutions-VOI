/*-----------------------------
        Author : TgX.2
       11Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>

#define FOR(i, a, b)       for (int i = (a), _b = (b); i <= _b; i += 1)
#define FORD(i, a, b)      for (int i = (a), _b = (b); i >= _b; i -= 1)
#define FORC(i, a, b, c)   for (int i = (a), _b = (b), _c = (c); i <= _b; i += _c)

#define fi                 first
#define se                 second
#define pb                 push_back
#define len(x)             (int)((x).size())
#define all(x)             (x).begin(), (x).end()

#define _                  << " " <<
#define __                 << "\n"

#define ______________TgX______________ main()
#define int                long long
#define intmax             1e9
#define intmin            -1e9
#define llongmax           1e18
#define llongmin          -1e18
#define memo(a, val)       memset((a), (val), sizeof((a)))

using   namespace std;
typedef long long          ll;
typedef pair<int, int>     pii;

template<typename T1, typename T2> 
bool mini(T1 &a, T2 b)
    {if (a > b) a = b; else return 0; return 1;}

template<typename T1, typename T2> 
bool maxi(T1 &a, T2 b)
    {if (a < b) a = b; else return 0; return 1;}
/*-----------------------------*/

const int maxn = 3e5 + 7;
int n, a[maxn];
vector<pair<int, int>> g[maxn << 2];


int pos[maxn];
int sta[maxn << 2];

void build(int id, int l, int r) {
    if (l == r) {
        sta[id] = a[l];
        pos[l] = id;
        return;
    }
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    g[id << 1].pb({id, 0});
    g[id << 1 | 1].pb({id, 0});
}

void update(int id, int l, int r, int u, int v, int val) {
    if (v < l or r < u) return;
    if (u <= l and r <= v) return g[id].pb({val, 1}), void();
    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
}

vector<pair<int, int>> inp;
int dis[maxn << 2];

void bfs(int s) {
    deque<int> q; q.push_front(s);
    dis[s] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop_front();
        for(auto val : g[u]) {
            int v = val.fi, w = val.se;
            if (dis[v] == -1 and sta[v] < sta[u]) {
                dis[v] = dis[u] + w;
                sta[v] = sta[u];
                if (w == 0) q.push_front(v);
                else q.push_back(v);
            }
        }
    }
}


void process() {
    cin >> n;

    FOR(i, 1, n)
        cin >> a[i];
    build(1, 1, n);

    FOR(i, 1, n)
        inp.pb({a[i], pos[i]});
    sort(all(inp), greater<pair<int, int>>());

    FOR(i, 1, n) {
        int l, r; cin >> l >> r;
        update(1, 1, n, l, r, pos[i]);
    }

    memo(dis, -1);
    for(auto val : inp) {
        if (dis[val.se] == -1)
            bfs(val.second);
    }

    cout << *max_element(dis + 1, dis + n * 4 + 4) + 1;
}



/*-----------------------------*/
______________TgX______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    } else {
        freopen("income.inp", "r", stdin);
        freopen("income.out", "w", stdout);   
    }
    process();
}


/*==============================+
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|

===============================*/
