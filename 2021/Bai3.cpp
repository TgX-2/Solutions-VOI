#include <bits/stdc++.h>

using namespace std;

//mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define rf if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout);}
//#define in ({int x = 0; int c = getchar(), n = 0; for(; !isdigit(c); c = getchar()) n = (c == '-'); for(; isdigit(c); c = getchar()) x = x * 10 + c - '0'; n ? -x : x;})

#define bit(i, mask) (((mask) >> (i)) & 1)
#define on(i, mask) ((mask) | (1LL << (i)))
#define off(i, mask) ((mask) & (~(1LL << (i))))

#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define plx pair<ll, int>
#define vi vector<int>
#define vvi vector<vi>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'
#define ub(x, i) upper_bound(all(x), i) - x.begin()
#define lb(x, i) lower_bound(all(x), i) - x.begin()

#define name ""

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 1e18l+7;
const int M = 5e5+6;
const int N = 1 << 20;
const int LOG = 31 - __builtin_clz(N);

int n, k, L, R;
int cnt[N], gt[N], rv[N];

void add(int &x, const int &y){
	x += y;
	if(x >= mod) x -= mod;
}

void sub(int &x, const int &y){
	x -= y;
	if(x < 0) x += mod;
}

void inp(){
    cin >> n >> k >> L >> R;
    for(int i = 1; i <= n; i++){
    	int x; cin >> x;
    	cnt[x]++;
    }
}

int pw(int a, int n){
	int res = 1;
	while(n > 0){
		if(n & 1) res = 1LL * res * a % mod;
		a = 1LL * a * a % mod;
		n >>= 1;
	}
	return res;
}

void init(){
	gt[0] = 1;
	for(int i = 1; i < N; i++) gt[i] = 1LL * gt[i - 1] * i % mod;
	rv[N - 1] = pw(gt[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; i--) rv[i - 1] = 1LL * rv[i] * i % mod;
}

int nCk(int n, int k){
	if(n < k || n < 0 || k < 0) return 0;
	return 1LL * gt[n] * rv[k] % mod * rv[n - k] % mod;
}

void proc(){
	init();
    for(int i = 0; i < 20; i++){
    	for(int mask = 0; mask < (1 << 20); mask++){
    		if(bit(i, mask)) cnt[mask] += cnt[mask ^ (1 << i)];
    	}
    }
    for(int mask = 0; mask < (1 << 20); mask++) cnt[mask] = nCk(cnt[mask], k);
    for(int i = 0; i < 20; i++){
    	for(int mask = 0; mask < (1 << 20); mask++){
    		if(bit(i, mask)) sub(cnt[mask], cnt[mask ^ (1 << i)]);
    	}
    }
    int res = 0;
    for(int i = (L + 2) / 3 * 3; i <= R; i += 3) add(res, cnt[i]);
    cout << res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
    rf

    int test = 1;
    //cin >> test;

    while(test--){
        inp();
        proc();
    }
    
    cerr << "Time elapsed: " << TIME << "s" << endl;
    return 0;
}
