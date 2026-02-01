#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

#define rf if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout);}
#define rd ({int x = 0; int c = getchar(), n = 0; for(; !isdigit(c); c = getchar()) n = (c == '-'); for(; isdigit(c); c = getchar()) x = x * 10 + c - '0'; n ? -x : x;})

#define bit(i, mask) (((mask) >> (i)) & 1)
#define on(i, mask) ((mask) | (1LL << (i)))
#define off(i, mask) ((mask) & (~(1LL << (i))))

#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define vii vector<int>
#define all(a) (a).begin(), (a).end()
#define len(x) (int)((x).size())
#define pb push_back
#define endl '\n'
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

#define name ""

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 2e18+7;
const int lmt = 1e5+6;
const int LOG = 18;

struct item{
	int u, v, w;
};

item dsc[lmt];
int n, m, pa[lmt], sz[lmt], par[lmt][20], mn[lmt][20], high[lmt];
vector<pii> a[lmt];
bool check[lmt];

bool cmp(item a, item b){
	return a.w > b.w;
}

void in(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
    	int u, v, w;
    	cin >> u >> v >> w;
    	dsc[i] = {u, v, w};
    }
    sort(dsc + 1, dsc + m + 1, cmp);
}

void make_set(){
	for(int i = 1; i <= n; i++){
		pa[i] = i;
		sz[i] = 1;
	}
}

int findd(int u){
	if(pa[u] == u) return u;
	return pa[u] = findd(pa[u]);
}

bool uni(int u, int v){
	int a = findd(u), b = findd(v);
	if(a == b) return false;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += b;
	pa[b] = a;
	return true;
}

void dfs(int u){
	for(auto it : a[u]){
		int v = it.fi;
		if(v == par[u][0]) continue;
		mn[v][0] = it.se;
		par[v][0] = u;
		high[v] = high[u] + 1;
		dfs(v); 
	}
}

int lca(int u, int v){
	if(high[u] < high[v]) return lca(v, u);
	int res = inf;
	for(int i = LOG; i >= 0; i--){
		if(high[par[u][i]] >= high[v]){
			res = min(res, mn[u][i]);
			u = par[u][i];
		}
	}
	if(u == v) return res;
	for(int i = LOG; i >= 0; i--){
		if(par[u][i] != par[v][i]){
			res = min(res, mn[u][i]);
			res = min(res, mn[v][i]);
			u = par[u][i];
			v = par[v][i];
		}
	}
	res = min(res, mn[u][0]);
	res = min(res, mn[v][0]);
	return res;
}

void proc(){
	make_set();
    for(int i = 1; i <= m; i++){
    	int u = dsc[i].u, v = dsc[i].v;
    	if(!uni(u, v)) continue;
    	a[u].pb({v, dsc[i].w});
    	a[v].pb({u, dsc[i].w});
    	check[i] = true;
    }
    dfs(1);
    for(int j = 1; j <= LOG; j++){
    	for(int i = 1; i <= n; i++){
    		par[i][j] = par[par[i][j - 1]][j - 1];
    		mn[i][j] = min(mn[par[i][j - 1]][j - 1], mn[i][j - 1]);
    	}
    }
    high[0] = -1;

    ll res = 0;
    for(int i = 1; i <= m; i++){
    	if(!check[i]){
    		int u = dsc[i].u, v = dsc[i].v;
    		res += lca(u, v) - dsc[i].w;
    	}
    }
    cout << res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(0);

    rf

    int t = 1;
    //cin >> t;

    while(t--){
        in();
        proc();
    }

    cerr << "Time elapsed: " << TIME << "s" << endl;
    return 0;
}
