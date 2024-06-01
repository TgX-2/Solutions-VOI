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

ci maxn = 5e4+7;
int n,m,s;
set<int> g[maxn];

void inp() {
    cin >> n >> m >> s;
    FOR(i,1,m) {
        int u,v; cin >> u >> v;
        g[u].ins(v);
    }
}

void sol(int s) {
    vector<int> trace(maxn, -1), d(maxn, 0);
    vector<bool> check(maxn, 0);
    queue<int> q;
    q.push(s);
    trace[s] = s;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v:g[u]) if (trace[v] != u) {
            if (trace[v] < 0) {
                q.push(v);
                trace[v] = u;
                d[v] = d[u] + 1;
                check[v] = check[u];
            } else if (d[u] + 1 == d[v]) check[v] = 1;
        }
    }
    int ans = 0;
    for(auto x:check) ans += x;
    cout << ans;
}

void process() {
    inp();
    sol(s);
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
