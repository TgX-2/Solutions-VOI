/*------------DEFINE-----------*/
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a), _b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i>=_b; --i)
#define FORSq(i,a,b) for(int i=(a), _b=(b); i*i<=_b; ++i)
#define FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c); i<=_b; i+=_c)
#define FORSt(i,s) for(int i=0, _s=(int)(s.size());i<_s;++i)

#define fi first
#define se second
#define pb push_back
#define len(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
#define alln(x,n) (x)+1, (x)+1+(n)
#define _ <<" "<<
#define __ << "\n"
#define ___ << " "
#define file "voi"
#define int long long
#define _______________mgw______________ main()

#define intmax INT_MAX
#define intmin INT_MIN 
#define llongmax LLONG_MAX 
#define llongmin LLONG_MIN

using    namespace std;
typedef  long long ll;
typedef  string st;
typedef  pair<int,int> pii;
typedef  vector<int> vi;
typedef  vector<pii> vpii;

void fastio(st name, st inp, st out, st dbg) {
    if (fopen((name + "." + inp).c_str(), "r")) {
        freopen((name + "." + inp).c_str(), "r", stdin);
        freopen((name + "." + out).c_str(), "w", stdout);
        freopen((name + "." + dbg).c_str(), "w", stderr);
    }        
}

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a>b) a=b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a<b) a=b; else return 0; return 1;}

/*------------CODE-------------*/

const int maxn = 107, mod = 1e9;

int n,m;
int a[maxn][maxn], dp[maxn][maxn];

void sol() {
    FOR(i,1,m) dp[i][1] = 1;
    FOR(i,1,m) FOR(j,1,n) {
        FOR(x,1,i) FOR(y,1,j) {
            if (y < n && x+y < i+j && __gcd(a[x][y], a[i][j]) > 1)
                dp[i][j] = (dp[i][j] + dp[x][y] + mod) % mod;
        }
    }

    int ans = 0;
    FOR(i,1,m) ans = (ans + dp[i][n] + mod) % mod;
    cout << ans; 
}

void process() {
    cin >> m >> n;
    FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
    sol();
}



/*------------MAIN-------------*/
_______________mgw______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
    fastio(file, "inp", "out", "debug");
    process();
}


/*==============================+
|INPUT                          |
--------------------------------|
2 2
2 4
6 8
================================+
|OUTPUT                         |
--------------------------------|
4
===============================*/
