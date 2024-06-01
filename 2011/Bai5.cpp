/*-----------------------------
        Author : TgX.2
        10Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>
#include <sys/time.h>
#pragma GCC optimize("O2,Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("abm,avx2,bmi,bmi2,fma,mmx,sse,sse2,sse3,ssse3,sse4")

#define     FOR(i,a,b) for(int i=(a), _b=(b);i<=_b;++i)
#define    FORD(i,a,b) for(int i=(a), _b=(b);i>=_b;--i)
#define   FORSq(i,a,b) for(int i=(a), _b=(b);i*i<=_b;++i)
#define  FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c);i<=_b;i+=_c)
#define     FORSt(i,s) for(int i=(a), _s=(int)(s.size());i<=_s;++i)

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
//#define int long long

using    namespace std;
using    namespace std::chrono;
typedef  long long ll;
typedef  unsigned long long ull;
typedef  string st;
typedef  pair<int,int> pii;
typedef  pair<ll,ll> pll;

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

ci maxn = 507;
int n;
int f[maxn][maxn];
int row[maxn][maxn], col[maxn][maxn];

void inp() {
    cin >> n;
    FOR(i,1,n) FOR(j,1,n) {
        int x; cin >> x;
        col[i][j] = (col[i-1][j] + x%2) % 2;
        row[i][j] = (row[i][j-1] + x%2) % 2;
    }
}

void sol() {
    // FOR(i,1,n) FOR(j,1,n) cout << row[i][j] << " \n"[j==n];
    // cout __ ;
    // FOR(i,1,n) FOR(j,1,n) cout << col[i][j] << " \n"[j==n];    
    // cout __ ;

    FOR(i,1,n) FOR(j,1,n) {
        f[i][j] = 0;
        if ((!f[i-1][j] && !row[i][j]) || (!f[i][j-1] && !col[i][j]) ) f[i][j] = 1;
    }
    cout << (f[n][n] ? "YES\n":"NO\n");

}


void process() {
    int t; cin >> t;
    while(t--) {
        inp();
        sol();
    }
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
2
3
1 2 2
1 2 3
2 3 1
4
2 2 2 2
2 2 2 2
2 2 2 2
2 2 2 2
================================+
|            OUTPUT             |
--------------------------------|
YES
NO
===============================*/
