#include <bits/stdc++.h>

using namespace std;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

#define rf if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout);}
#define rd ({int x = 0; int c = getchar(), n = 0; for(; !isdigit(c); c = getchar()) n = (c == '-'); for(; isdigit(c); c = getchar()) x = x * 10 + c - '0'; n ? -x : x;})

#define bit(i, mask) (((mask) >> (i)) & 1)
#define on(i, mask) ((mask) | (1LL << (i)))
#define off(i, mask) ((mask) & (~(1LL << (i))))

#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define vii vector<int>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

#define name ""

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 1e18l+7;
const int M = 5e5+6;
const int N = 5e2+1;
const int LOG = 31 - __builtin_clz(N);

int n, k, r, p;
int a[5], b[5];
ll f[N][N];

void in(){
    cin >> n >> k >> r >> p;
    for(int i = 1; i <= n; i++){
    	for(int j = 1; j <= n; j++){
    		cin >> f[i][j];
    		f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
    	}
    }
}

inline ll get(int u, int v, int x, int y){
	return f[x][y] - f[u - 1][y] - f[x][v - 1] + f[u - 1][v - 1];
}

void proc(){
	ll res = 0;
    for(int T = 1; T <= k; T++){
    	ll ans = 0;
    	for(int i = 0; i < p; i++) cin >> a[i] >> b[i];
    	for(int mask = 1; mask < (1 << p); mask++){
    		int u = 1, v = 1, x = n, y = n;
    		for(int i = 0; i < p; i++){
    			if(bit(i, mask)){
    				maxi(u, a[i]);
    				maxi(v, b[i]);
    				mini(x, a[i] + r - 1);
    				mini(y, b[i] + r - 1);
    			}
    		}
    		if(u > x || v > y) continue;
    		if(__builtin_popcount(mask) & 1) ans += get(u, v, x, y);
    		else ans -= get(u, v, x, y);
    	}
    	maxi(res, ans);
    }
    cout << res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    rf

    int test = 1;
    //cin >> test;

    while(test--){
        in();
        proc();
    }

    cerr << "Time elapsed: " << TIME << "s" << endl;
    return 0;
}
