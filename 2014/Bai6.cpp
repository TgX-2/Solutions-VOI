/*-----------------------------
        Author : VietCodes
        10Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a), _b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a), _b=(b);i>=_b;--i)
#define FORSq(i,a,b) for(int i=(a), _b=(b);i*i<=_b;++i)
#define FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c);i<=_b;i+=_c)
#define FORSt(i,s) for(int i=0, _s=(int)(s.size());i<_s;++i)

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pp pop_back()
#define eb emplace_back
#define ers erase
#define ins insert
#define emp empty()
#define rvs reverse

#define BIT(x,i) (((x)>>(i))&1)
#define MASK(i) (1LL<<(i))
#define CNTBIT(x) __builtin_popcountll(x)
#define ODDBIT(x) __builtin_parityll(x)
#define FIRSTBIT(x) __builtin_ctzll(x)

#define len(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
#define alln(x,n) (x)+1, (x)+1+(n)

#define ci const int
#define cs const string
#define cll const long long
#define cull const unsigned long long
#define _ <<" "<<
#define __ << "\n"
#define ___ << " "
#define ____ << "\t"

#define dbn(n) cout << #n << " : " << n __ 
#define dbp(n) cout << #n << ".fi : " << (n).fi << " | " << #n << ".se : " << (n).se __ 
#define dba(a,l,r) FOR(i,(l),(r)) cout << #a << "[" << i << "] : " << (a)[i] __

#define file "voi"
#define ______________TgX______________ main()
#define int long long

#define intmin INT_MIN
#define intmax INT_MAX
#define llongmax LLONG_MAX
#define llongmin LLONG_MIN

using namespace std;
using namespace std::chrono;
typedef long long ll;
typedef unsigned long long ull;
typedef string st;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

void fastio() {
    if (fopen(file".inp", "r")) {
        freopen(file".inp", "r", stdin);
        freopen(file".out", "w", stdout);
        freopen(file".debug", "w", stderr);
    }        
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
}

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a>b) a=b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a<b) a=b; else return 0; return 1;}
/*-----------------------------*/


ci maxn = 503;

int n, src, sink;
int G[maxn][maxn], F[maxn][maxn];
bitset<maxn> vis;
int change[maxn], trace[maxn], Q[maxn];

bool bfs() {
    vis.reset();
    int first(0), last(0);
    Q[fi] = src;
    vis[src] = 1;
    while (first <= last) {
        int u = Q[first++];
        FOR(i,1,n) if (!vis[i]) {
            if (G[u][i] > F[u][i]) {
                change[i] = min(change[u], G[u][i] - F[u][i]);
                trace[i] = u;
            } else if (F[i][u] > 0) {
                change[i] = min(change[u], F[i][u]);
                trace[i] = -u;
            } else continue;

            if (i == sink) return 1;
            Q[++last] = i;
            vis[i] = 1;
        }
    }
    return 0;
}

void update_flow() {
    int v = sink;
    while (v != src) {
        int u = trace[v];
        if (u > 0) F[u][v] += change[sink];
        else {
            u = -u;
            F[v][u] -= change[sink];
        }
        v = u;
    }
}

int max_flow() {
    change[src] = 1e9;
    int flow = 0;
    while (bfs()) {
        flow += change[sink];
        update_flow();
    }
    return flow;
}

void process() {
    cin >> n;
    int C = 0;
    src = n + 1;
    sink = n + 2;
    FOR(i,1,n) {
        int c; cin >> c;
        if (c < 0) G[i][sink] = -c;
        else {
            G[src][i] = c;
            C += c;
        }
    }

    int m; cin >> m;
    FOR(i,1,m) {
        int p, q; cin >> p >> q;
        G[p][q] = C + 1;
    }

    n = n + 2;
    cout << C - max_flow();
}



/*-----------------------------*/
______________TgX______________ {
    auto start = high_resolution_clock::now();
    fastio();
    process();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cerr << "Time: " << duration.count() << " ms" << endl;  
}


/*==============================+
|             INPUT             |
--------------------------------|

================================+
|            OUTPUT             |
--------------------------------|

===============================*/
