#include <bits/stdc++.h>

using namespace std;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define rf if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout);}
//#define in ({int x = 0; int c = getchar(), n = 0; for(; !isdigit(c); c = getchar()) n = (c == '-'); for(; isdigit(c); c = getchar()) x = x * 10 + c - '0'; n ? -x : x;})

#define bit(i, mask) (((mask) >> (i)) & 1)
#define on(i, mask) ((mask) | (1LL << (i)))
#define off(i, mask) ((mask) & (~(1LL << (i))))

#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define vi vector<int>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'

#define name "fbuy"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 998244353;
const int inf = 1e9 + 9;
const ll  oo  = 1e18l + 7;
const int M   = 5e5 + 6;
const int N   = 2e5 + 2;
const int LOG = 31 - __builtin_clz(N);

struct item{
    int root, branch, sz;
};

int n, k, q, c[N], cost[21];
vi adj[N];
int st[N], en[N], cntDfs = 0;

bool del[N];
int child[N], branch = 0;
vector<item> centroid[N];

int total_cross[N][21], sum_cross[N * 19][21]; // sumpath di qua (u, v) voi u -> cen -> v
int sumTree[N], sumBranch[N * 19], sum[N][21]; // sumpath di qua (u, v) voi u -> cen
int dp[N];                                     // sumpath di qua u
int ans = 0, _ans = 0;

void add(int &x, const int &y){
    x += y;
    if(x >= mod) x -= mod;
}

void sub(int &x, const int &y){
    x -= y;
    if(x < 0) x += mod;
}

void inp(){
    cin >> n >> k >> q;
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 1; i <= k; i++){
        cin >> cost[i];
        if(cost[i] >= mod) cost[i] -= mod;
    }
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

void preDfs(int u, int pre){
    st[u] = ++cntDfs;
    child[u] = 1;
    for(int v : adj[u]){
        if(v == pre) continue;
        preDfs(v, u);
        add(dp[u], 1LL * child[u] * child[v] % mod);
        child[u] += child[v];
    }
    add(dp[u], 1LL * child[u] * (n - child[u]) % mod);
    en[u] = cntDfs;
}

void get_sz(int u, int pre){
    child[u] = 1;
    for(int v : adj[u]){
        if(v == pre || del[v]) continue;
        get_sz(v, u);
        child[u] += child[v];
    }
}

int _find(int u, int pre, int nNode){
    for(int v : adj[u]){
        if(v != pre && !del[v] && child[v] > nNode) return _find(v, u, nNode);
    }
    return u;
}

int count_sz(int u, int r){
    if(st[u] <= st[r] && st[r] <= en[u]) return n - (en[r] - st[r] + 1);
    return en[u] - st[u] + 1;
}

void dfs(int u, int pre, int root, int branch){
    int cnt = count_sz(u, pre);
    add(total_cross[root][c[u]], cnt);
    add(sum_cross[branch][c[u]], cnt);
    add(sum[root][c[u]], 1LL * (sumTree[root] - sumBranch[branch] + mod) * cnt % mod);
    add(ans, 1LL * (total_cross[root][c[u]] - sum_cross[branch][c[u]] + mod) * cnt % mod * cost[c[u]] % mod);
    centroid[u].pb({root, branch, cnt});
    for(int v : adj[u]){
        if(v == pre || del[v]) continue;
        dfs(v, u, root, branch);
    }
}

void centroid_dc(int u){
    get_sz(u, -1);
    int root = _find(u, -1, child[u] / 2);
    del[root] = true;

    add(sumTree[root], n);
    for(int v : adj[root]){
        if(del[v]) continue;
        add(sumBranch[branch], count_sz(v, root));
        dfs(v, root, root, branch++);
    }
    add(ans, 1LL * sum[root][c[root]] * cost[c[root]] % mod);
    add(_ans, 1LL * dp[root] * cost[c[root]] % mod);
    for(int v : adj[root]) if(!del[v]) centroid_dc(v);
}

void updadd(int u){
    add(ans, 1LL * sum[u][c[u]] * cost[c[u]] % mod);
    add(_ans, 1LL * dp[u] * cost[c[u]] % mod);

    for(auto it : centroid[u]){
        int root = it.root, branch = it.branch, cnt = it.sz;
        add(ans, 1LL * (total_cross[root][c[u]] - sum_cross[branch][c[u]] + mod) * cnt % mod * cost[c[u]] % mod);
        if(c[u] == c[root]) add(ans, 1LL * (sumTree[root] - sumBranch[branch] + mod) * cnt % mod * cost[c[u]] % mod);
        
        add(total_cross[root][c[u]], cnt);
        add(sum_cross[branch][c[u]], cnt);
        add(sum[root][c[u]], 1LL * (sumTree[root] - sumBranch[branch] + mod) * cnt % mod);
    }
}

void upddel(int u){
    sub(ans, 1LL * sum[u][c[u]] * cost[c[u]] % mod);
    sub(_ans, 1LL * dp[u] * cost[c[u]] % mod);

    for(auto it : centroid[u]){
        int root = it.root, branch = it.branch, cnt = it.sz;
        sub(ans, 1LL * (total_cross[root][c[u]] - sum_cross[branch][c[u]] + mod) * cnt % mod * cost[c[u]] % mod);
        if(c[u] == c[root]) sub(ans, 1LL * (sumTree[root] - sumBranch[branch] + mod) * cnt % mod * cost[c[u]] % mod);
        
        sub(total_cross[root][c[u]], cnt);
        sub(sum_cross[branch][c[u]], cnt);
        sub(sum[root][c[u]], 1LL * (sumTree[root] - sumBranch[branch] + mod) * cnt % mod);
    }
}

void proc(){
    preDfs(1, 1);
    centroid_dc(1);
    cout << (2LL * ans + _ans) % mod << endl;
    while(q--){
        int u, b; cin >> u >> b;
        upddel(u);
        c[u] = b;
        updadd(u);
        cout << (2LL * ans + _ans) % mod << endl;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
    rf

    int test = 1;
    //cin >> test;

    while(test--){
        inp();
        proc();
    }
    
    cerr << "Time elapsed: " << TIME << "s" << endl;
    return 0;
}
