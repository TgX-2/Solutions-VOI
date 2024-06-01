/*-----------------------------
        Author : TgX.2
        10Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>
#include <sys/time.h>
#pragma GCC optimize("O2,Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define FOR(i,a,b) for(int i=a; i<=b; i++)
#define FORD(i,a,b) for(int i=a; i>=b; i--)
#define FORS(i,a,b) for(int i=(a);i*i<=(b);i++)
#define FORC(i,a,b,c) for(int i=(a);i<=(b);i+=(c))
#define FORE(i,a) for(auto i=(a).cbegin();i!=(a).cend();i++)
#define REPN(i,n) for(int i=1; i<=(n); i++)
#define REPS(i,s) for(int i=0;i<(s).size(); i++)
#define REPV(a) for(int& x:(a)) cin >> x
#define REPA(a,n) for(int i=1;i<=n;i++) {int& x=a[i]; cin >> x;}

#define emp empty()
#define rvs reverse
#define pb push_back
#define pp pop_back()
#define eb emplace_back
#define ins insert
#define ers erase
#define fi first
#define se second
#define mp make_pair

#define BIT(x, i) (((x) >> (i))&1)
#define MASK(i) (1LL<<(i))
#define CNTBIT(x) __builtin_popcountll(x)
#define ODDBIT(x) __builtin_parityll(x)
#define FIRSTBIT(x) __builtin_ctzll(x)
#define SUBSET(big, small) (((big)&(small))==(small))

#define len(x) (x).size()
#define all(x) (x).begin(), (x).end()
#define alln(x,n) (x)+1, (x)+1+(n)

#define ci const int
#define cll const long long
#define cull const unsigned long long

#define _ <<" "<<
#define __ << "\n"
#define ___ << " "

#define file "voi"
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define ______________TgX______________ signed main()
//#define int long long

using namespace std;
using namespace std::chrono;
typedef long long ll;
typedef unsigned long long ull;
typedef string st;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

void fastio() {
    if (fopen(file".inp", "r")) {
        freopen(file".inp", "r", stdin);
        freopen(file".out", "w", stdout);
    }        
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
}

template<typename T> void maxi(T &a, const T &b) {if (a < b) a = b;}
template<typename T> void mini(T &a, const T &b) {if (a > b) a = b;}
/*-----------------------------*/

ci maxn = 2e5+7;
int n, a[maxn], b[maxn];

void process() {
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> b[i];

    sort(alln(a,n));
    sort(alln(b,n));

    int i = 1, j = 1, ans = 0;
    int r = INT_MIN;
    while(i<= n && j<=n) {
        while(j <= n && b[j] <= r && a[i] > r) j++;

        if (a[i] > r && b[j] > r) {
            ans++;
            r = max(a[i],b[j]);
        }

        i++;
    }
    
    cout << ans;
}



/*-----------------------------*/
______________TgX______________ {
    auto start = high_resolution_clock::now();
    fastio();
    process();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cerr << "Time: " << duration.count() << " ms" << endl;  
    return 0;
}
