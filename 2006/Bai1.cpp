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
#define memo(a, val) memset((a), (val), sizeof((a)))

using namespace std;
using namespace std::chrono;
typedef long long ll;
typedef unsigned long long ull;
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


const int maxn = 1e4 + 7;
 
int n, f[maxn][(1 << 4)], a[4][maxn];
 
bool check(int x, int y) {
 
}
 
int dp(int id, int mask) {
    if (id == n) {
        return 0;
    }
 
    int &ans = f[id][mask];
    if (ans != -1) return ans;
 
    ans = intmin;
    FOR(mask2, 0, (1 << 4) - 1) {
        if ((mask & mask2) == 0) {
            int x = 0;
            bool is = 1, check = 0;
            FOR(i, 0, 8) {
                if (mask2 & (1 << i)) {
                    x += a[i][id];
                    if (check) 
                        {is = 0; break;}
                    check = 1;
                } else check = 0;
            }
            // cout << " " << x __ ;
            if (is) maxi(ans, dp(id + 1, mask2) + x);
        }
    }
    return ans;
}
 
void process() {
    cin >> n;
 
    bool is = 1;
    int ans = intmin;
 
    FOR(i, 0, 3) 
        FOR(j, 0, n - 1) {
            cin >> a[i][j];
            if (a[i][j] > 0) is = 0;
            else maxi(ans, a[i][j]);
        }
    
    if (is) return cout << ans , void();
 
    memo(f, -1);
 
    cout << dp(0, 0);
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
