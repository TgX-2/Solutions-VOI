/*-----------------------------
        Author : TgX.2
       10Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a), _b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a), _b=(b);i>=_b;--i)
#define FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c);i<=_b;i+=_c)
#define FORSq(i,a,b) for(int i=(a), _b=(b);i*i<=_b;++i)
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

#define _ <<" "<<
#define __ << "\n"
#define ___ << " "
#define ____ << "\t"

#define file "reform"
#define ______________TgX______________ main()
#define int long long
#define intmax 1e9
#define intmin -1e9
#define llongmax 1e18
#define llongmin -1e18
#define memo(a, val) memset((a), (val), sizeof((a)))

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

// int dx[] = {1,-1,0,0} , dy[] = {0,0,1,-1};                         // 4 Direction
// int dx[] = {1,-1,0,0,1,1,-1,-1} , dy[] = {0,0,1,-1,1,-1,1,-1};     // 8 Direction
// int dx[] = {1,-1,1,-1,2,2,-2,-2} , dy[] = {2,2,-2,-2,1,-1,1,-1};   // Knight Direction
// int dx[] = {2,-2,1,1,-1,-1} , dy[] = {0,0,1,-1,1,-1};              // Hexagonal Direction

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

const int maxn = 2e5+7;
int n, m;
vi g[maxn];

int cntcau[maxn], cntdinh[maxn], cntcon[maxn];
int num[maxn], low[maxn];
int cc = 0,cau, khop, cnt;
int ans = 0, subv[maxn];
void dfs(int u, int p) {
    low[u] = num[u] = ++cnt;
    cntdinh[cc]++;
    for(auto v:g[u]) if (v!=p) {
        if (num[v]) mini(low[u], num[v]);
        else {
            dfs(v,u);
            subv[u] += subv[v]; 
            mini(low[u], low[v]);
            if (low[v]==num[v]) {
                cntcau[cc]++;
                cntcon[1] += subv[v] * (n - subv[v]) - 1;
            }
        }
    }
    subv[u]++;
}

void process() {
    cin >> n >> m;
    FOR(i,1,m) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    FOR(i,1,n) if (!num[i]) {
        cc++;
        if (cc == 3) return cout << 0, void();
        dfs(i, -1);
    }
    // assert(cc != 1);
    // FOR(i,1,n)
    //     cout << subv[i] __ ;
    if (cc == 1) cout << cntcon[1] + (m - cntcau[1]) * ((n - 1) * n / 2 - m);
    else cout << (m -  cntcau[1] - cntcau[2]) * cntdinh[1] * cntdinh[2];
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
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|

===============================*/
