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

#define file "temp"
#define ______________TgX______________ main()
#define int long long
#define intmax 1e9
#define intmin -1e9
#define llongmax 1e18
#define llongmin -1e18

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

const int maxn = 507;
int a[3*maxn][3*maxn], b[3*maxn][3*maxn];

int n,m, x, y;

void inp() {
    cin >> m >> n;
    FOR(i,1,m) FOR(j,1,n) {
        cin >> a[i][j];
        a[i][j+n] = a[i+m][j] = a[i+m][j+n]  = a[i][j];
    }

    FOR(i,1,2*m) FOR(j,1,2*n) 
        b[i][j] = b[i-1][j] + b[i][j-1] - b[i-1][j-1] + a[i][j];

    // FOR(i,1,2*m) FOR(j,1,2*n) cout << a[i][j] << " \n"[j==2*n];

}

void case1() {
    // cout << "hah\n";
    int r, d; cin >> r >> d;
    x += r; y += d;
    x %= n; y %= m;
}

void case2() {
    int u,v,s,t; cin >> u >> v >> s >> t;
    u = (u + y) % (2 * m);
    v = (v + x) % (2 * n);
    s = (s + y) % (2 * m);
    t = (t + x) % (2 * n);

    cout <<  (b[s][t] - b[s][v-1] - b[u-1][t] + b[u-1][v-1]) __ ;

}

void process() {
    inp();
    x = 0, y = 0;
    int t; cin >> t;
    while(t--) {
        bool typ; cin >> typ;
        if (typ == 0) case1();
        else case2();
        // cout << x _ y __ ;
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
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|

===============================*/
