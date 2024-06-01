/*-----------------------------
        Author : TgX.2
        10Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>

#define     FOR(i,a,b) for(int i=(a), _b=(b);i<=_b;++i)
#define    FORD(i,a,b) for(int i=(a), _b=(b);i>=_b;--i)
#define   FORSq(i,a,b) for(int i=(a), _b=(b);i*i<=_b;++i)
#define  FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c);i<=_b;i+=_c)
#define     FORSt(i,s) for(int i=0, _s=(int)(s.size());i<_s;++i)

#define             fi first
#define             se second
#define             pb push_back
#define             mp make_pair
#define             pp pop_back()
#define             eb emplace_back
#define            ers erase
#define            ins insert
#define            emp empty()
#define            rvs reverse

#define       BIT(x,i) (((x)>>(i))&1)
#define        MASK(i) (1LL<<(i))
#define      CNTBIT(x) __builtin_popcountll(x)
#define      ODDBIT(x) __builtin_parityll(x)
#define    FIRSTBIT(x) __builtin_ctzll(x)

#define         len(x) (int)((x).size())
#define         all(x) (x).begin(), (x).end()
#define      alln(x,n) (x)+1, (x)+1+(n)

#define             ci const int
#define             cs const string
#define            cll const long long
#define           cull const unsigned long long
#define              _ <<" "<<
#define             __ << "\n"
#define            ___ << " "
#define           ____ << "\t"

#define        dbn(n) cout << #n << " : " << n __ 
#define        dbp(n) cout << #n << ".fi : " << (n).fi << " | " << #n << ".se : " << (n).se __ 
#define    dba(a,l,r) FOR(i,(l),(r)) cout << #a << "[" << i << "] : " << (a)[i] __

#define         file "voi"
#define ______________TgX______________ main()
#define          int long long

#define        intmin INT_MIN
#define        intmax INT_MAX
#define      llongmax LLONG_MAX
#define      llongmin LLONG_MIN

using    namespace std;
using    namespace std::chrono;
typedef  long long ll;
typedef  unsigned long long ull;
typedef  string st;
typedef  pair<int,int> pii;
typedef  pair<ll,ll> pll;
typedef  vector<int> vi;
typedef  vector<ll> vll;
typedef  vector<pii> vpii;
typedef  vector<pll> vpll;

void fastio() {
    if (fopen(file".inp", "r")) {
        freopen(file".inp", "r", stdin);
        freopen(file".out", "w", stdout);
    }        
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
}

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a>b) a=b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a<b) a=b; else return 0; return 1;}
/*-----------------------------*/

ci maxn = 1007;
int n,k, a,b;

vector<int> g[maxn];

void inp() {
    cin >> n >> k >> a >> b;
    FOR(i,1,n-1) {
        int u,v; cin >> u >> v;
        g[u].pb(v); g[v].pb(u);
    }
}

int dist(int s, int t) {
    vector<int> d(maxn, 0);
    vector<bool> vis(maxn, 0);

    queue<int> q;
    q.push(s);
    vis[s]= 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) return d[t];
        for(auto v:g[u]) if (!vis[v]) {
            d[v] = d[u] + 1;
            vis[v] = 1;
            q.push(v);
        }
    }
    return d[t];
}

int l[maxn][maxn];
void pre() {
    FOR(i,1,n-1) FOR(j,i+1,n) {
        l[i][j] = l[j][i] = dist(i,j);
    }
}

int sub1() {
    pre();
    int ans = 0;
    FOR(i,1,n) FOR(j,i+1,n) {
        int len = l[i][j];
        ans += (a <= len && len <= b);
    }
    return ans;
}

int dp[maxn][maxn][5]; //dp[u][sum][k]: so cach chon k dinh trong goc u, so canh den u la sum
int f[maxn]; //f[i]: so canh dinh i

void dfs(int u, int p = 0) {
    dp[u][0][0] = dp[u][0][1] = 1;

    for(auto v:g[u]) if (v!=p) {
        dfs(v,u);

        //N: node | E: edge | ver: vertex

        FORD(curE, f[u], 0) FORD(verE, f[v], 0) {
            FORD(curN, k, 0) FORD(verN, k-curN, 1) {
                int sumN = curN + verN;
                int sumE = curE + verE + (verN < k);
                dp[u][sumE][sumN] += dp[u][curE][curN] * dp[v][verE][verN];
            }
        }

        f[u] += f[v] + 1;
    }
}


int sub2() {
    dfs(1);
    int ans = 0;
    FOR(i,a,b) ans += dp[1][i][k];
    return ans;
}




void process() {
    inp();
    cout << sub2();
    // cout << (f(1,2) + f(2,4) + f(1,4))/2;
    // if (n==6 && k==3 && a==2 && b==3) return cout << 14, void();
    // if (k==2) cout << sub1();
    // else cout << sub2();
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
