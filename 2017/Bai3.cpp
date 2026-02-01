#include <bits/stdc++.h>

using namespace std;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

#define rf if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout);}
#define rd ({int x = 0; int c = getchar(), n = 0; for(; !isdigit(c); c = getchar()) n = (c == '-'); for(; isdigit(c); c = getchar()) x = x * 10 + c - '0'; n ? -x : x;})

#define bit(i, mask) (((mask) >> (i)) & 1)
#define on(i, mask) ((mask)  (1LL << (i)))
#define off(i, mask) ((mask) & (~(1LL << (i))))

#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define vii vector<int>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

#define name "test"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 1e18l+7;
const int M = 5e5+6;
const int N = 1e5+6;
const int LOG = 31 - __builtin_clz(N);

struct item{
    int u, v, w;

    bool operator < (const item &it){
        return w > it.w;
    }
};

int n, m;
item Edge[N];
vector<pii> adj[N];
int high[N], par[N][LOG + 1], mx[N][LOG + 1];
bool check[N];

struct Dsu{
    int par[N], sz[N];

    Dsu(){
        for(int i = 1; i < N; i++){
            par[i] = i;
            sz[i] = 1;
        }
    }

    int root(int u){
        return (par[u] == u) ? u : par[u] = root(par[u]);
    }

    bool uni(int u, int v){
        u = root(u), v = root(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }
} dsu;

void in(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> Edge[i].u >> Edge[i].v >> Edge[i].w;
}

void dfs(int u) {
    for(auto it : adj[u]) {
        int v = it.fi;
        if (v == par[u][0]) continue;
        par[v][0] = u;
        high[v] = high[u] + 1;
        mx[v][0] = it.se;
        dfs(v);
    }
}

int lca(int u, int v){
    int res = -inf;
    if (high[u] < high[v]) swap(u, v);
    for(int i = LOG; i >= 0; i--){
        if(high[par[u][i]] >= high[v]){
            maxi(res, mx[u][i]);
            u = par[u][i];
        }
    }
    if (u == v) return res;
    for(int i = LOG; i >= 0; i--){
    	if (par[u][i] != par[v][i]){
            maxi(res, mx[u][i]); maxi(res, mx[v][i]);
        	u = par[u][i];
        	v = par[v][i];
    	}
    }
    maxi(res, mx[u][0]); maxi(res, mx[v][0]);
    return res;
}

void proc(){
    sort(Edge + 1, Edge + m + 1);
    for(int i = 1; i <= m; i++){
        if(!dsu.uni(Edge[i].u, Edge[i].v)) continue;
        adj[Edge[i].u].pb({Edge[i].v, Edge[i].w});
        adj[Edge[i].v].pb({Edge[i].u, Edge[i].w});
        check[i] = true;
    }

    for(int i = 1; i <= n; i++){
        if(!par[i][0]){
            par[i][0] = i;
            dfs(i);
        }
    }
    
    for(int j = 1; j <= LOG; j++){
		for(int i = 1; i <= n; i++){
            par[i][j] = par[par[i][j - 1]][j - 1];
            mx[i][j] = max(mx[par[i][j - 1]][j - 1], mx[i][j - 1]);
        }
	}
	high[0] = -1;

    int res = 0;
    for(int i = 1; i <= m; i++){
        if(!check[i]){
            maxi(res, Edge[i].w + lca(Edge[i].u, Edge[i].v));
//            cout << Edge[i].u << ' ' << Edge[i].v << ' ' << Edge[i].w << ' ' << lca(Edge[i].u, Edge[i].v) << endl;
        }
    }

    cout << res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    rf

    int test = 1;
    //cin >> test;

    while(test--){
        in();
        proc();
    }

    cerr << "Time elapsed: " << TIME << "s" << endl;
    return 0;
}
