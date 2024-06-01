/*-----------------------------
        Author : TgX.2
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

#define intmax 1e9+7
#define intmin -1e9+7
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

const int maxn = 2e5+7;

int n, id, k; 
int a[maxn], s[maxn];
unordered_map<int,int>f, m;

int fibn(int n) {
	if(f.count(n)) return f[n]; 
	if(n<=2) return 1;
	if(n&1) {
		ll x = fibn(n/2) ; 
		ll y = fibn(n/2+1) ; 
		return f[n] = (x*x%k + y*y%k) % k;
	} else {
        ll x = fibn(n/2) ; 
        ll y = fibn(n/2-1) ;  
        return f[n] = (x*x%k + 2*x*y%k) % k;
    }
}

void sol() {	
    cin >> n >> id >> k;

	f.clear(); m.clear();
	m[0] = 0;  
	a[1] = fibn(id); a[2] = fibn(id+1);
	s[1] = a[1]; s[2] = (s[1]+a[2])%k; 

    if (a[1] == 0) return cout << 1 _ id __ , void();

	m[s[1]] = 1; 
	if(m[s[2]] > 0) {
		cout << 2-m[s[2]] ___ ;
		FOR(i, m[s[2]]+1, 2) cout << i+id-1 ___ ;
		return cout __ , void();
	}

	m[s[2]] = 2;
	FOR(i,3,n) {
		a[i] = (a[i-1]+a[i-2])%k;
		s[i] = (s[i-1]+a[i])%k;
		if(m[s[i]] > 0) {
			cout << i-m[s[i]] ___ ;
			FOR(j, m[s[i]]+1, i) cout << j+id-1 ___ ;
			return cout __ , void();
		}
		m[s[i]] = i ; 
	}	
}

void process() {
    int t; cin >> t;
    while(t--) sol();
}



/*-----------------------------*/
______________TgX______________ {
    auto start = high_resolution_clock::now();
    fastio();
    process();
    void NewFunction(long long &t);
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
