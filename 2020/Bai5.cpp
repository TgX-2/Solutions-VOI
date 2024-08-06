/*-----------------------------
    Author : canoccancap
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

const int maxn = 1e5 + 7;
int n;
struct val {
    int x, y, p, q;
} rec[maxn];

struct tada {
    int val, typ, id;

    bool operator <(tada &other) {
        return (val == other.val ? typ < other.typ : val < other.val);
    };
};
vector<tada> comp_ver[maxn << 1], comp_hor[maxn << 1];
vector<int> ver, hor;
vector<int> g[maxn];

int num[maxn], low[maxn], child[maxn], cnt = 0;
vector<int> cau;
void dfs(int u, int pre = -1) {
    num[u] = low[u] = ++cnt;
    child[u] = 1;
    for(int v : g[u]) if (v != pre) {
        if (num[v]) mini(low[u], num[v]);
        else {
            dfs(v, u);
            child[u] += child[v];
            mini(low[u], low[v]);
            if (low[v] >= num[v])
                cau.pb(v);
        }
    }
}


void process() {
    cin >> n;
    FOR(i, 1, n) {
        int x, y, p, q; cin >> x >> y >> p >> q;
        swap(y, q);
        rec[i] = {x, y, p, q};
        ver.pb(x);
        ver.pb(p);
        hor.pb(y);
        hor.pb(q);
    }

    sort(all(ver)); ver.erase(unique(all(ver)), ver.end());
    sort(all(hor)); hor.erase(unique(all(hor)), hor.end());

    FOR(i, 1, n) {
        rec[i].x = lower_bound(all(ver), rec[i].x) - ver.begin();
        rec[i].p = lower_bound(all(ver), rec[i].p) - ver.begin();
        rec[i].y = lower_bound(all(hor), rec[i].y) - hor.begin();
        rec[i].q = lower_bound(all(hor), rec[i].q) - hor.begin();

        comp_ver[rec[i].x].pb({rec[i].y, 0, i});
        comp_ver[rec[i].x].pb({rec[i].q, 1, i});
        comp_ver[rec[i].p].pb({rec[i].y, 0, i});
        comp_ver[rec[i].p].pb({rec[i].q, 1, i});

        comp_hor[rec[i].y].pb({rec[i].x, 0, i});
        comp_hor[rec[i].y].pb({rec[i].p, 1, i});
        comp_hor[rec[i].q].pb({rec[i].x, 0, i});
        comp_hor[rec[i].q].pb({rec[i].p, 1, i});
    }
    vector<pair<int, int>> e;

    FOR(i, 0, len(ver) - 1) {
        unordered_set<int> s;
        sort(all(comp_ver[i]));
        for(auto val : comp_ver[i]) {
            if (val.typ == 1) 
                s.erase(val.id);
            else {
                for(int id : s) 
                    e.pb({min(id, val.id), max(id, val.id)});
                s.insert(val.id);
            }
        }
    }

    FOR(i, 0, len(hor) - 1) {
        unordered_set<int> s;
        sort(all(comp_hor[i]));
        for(auto val : comp_hor[i]) {
            if (val.typ == 1) 
                s.erase(val.id);
            else {
                for(int id : s) 
                    e.pb({min(id, val.id), max(id, val.id)});
                s.insert(val.id);
            }
        }
    }
    sort(all(e));
    e.erase(unique(all(e)), e.end());
    for(pair<int, int> val : e) {
        g[val.fi].pb(val.se);
        g[val.se].pb(val.fi);
    }

    int ans = intmax;
    FOR(i, 1, n) if (num[i] == 0) {
        cau.clear();
        dfs(i);

        for(int val : cau)
            mini(ans, abs(child[val] - child[i] + child[val]));
    }

    cout << (ans == intmax ? -1 : ans);

}



/*-----------------------------*/
______________TgX______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
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
