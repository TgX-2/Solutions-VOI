#include <bits/stdc++.h>

using namespace std;

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define rf if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout);}

#define bit(i, mask) (((mask) >> (i)) & 1)
#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define vi vector<int>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'

#define name "aspal"

template<typename T1, typename T2> bool mini(T1 &a, T2 b) {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b) {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9 + 7;
const int inf = 1e9 + 9;
const ll  oo  = 1e18l + 7;
const int M   = 5e5 + 6;
const int N   = 5e4 + 2;
const int LOG = 31 - __builtin_clz(N);

string l, r;
int mod4[15], cnt[15];
int dp[N][11][11][11];

void add(int &x, const int &y){
	x += y;
	if(x >= mod) x -= mod;
}

void inp(){
    cin >> l >> r;
}

int calc(int id, int r1, int r2, int r3){
	if(id == 0) return (r1 <= 1 && (r1 + r2 * 2 + r3 * 3 <= 3));
	if(dp[id][r1][r2][r3] != -1) return dp[id][r1][r2][r3];

	int res = 0;
	int r0 = 10 - r1 - r2 - r3;
	if(r0 > 0) add(res, 1LL * r0 * calc(id - 1, r1 + 1, r2, r3) % mod);
	if(r1 > 0) add(res, 1LL * r1 * calc(id - 1, r1 - 1, r2 + 1, r3) % mod);
	if(r2 > 0) add(res, 1LL * r2 * calc(id - 1, r1, r2 - 1, r3 + 1) % mod);
	if(r3 > 0) add(res, 1LL * r3 * calc(id - 1, r1, r2, r3 - 1) % mod);

	return dp[id][r1][r2][r3] = res;
}

int get(const string &s, bool o){
	int ans = 0, n = len(s);
	for(int i = 1; i < n; i++) add(ans, 9LL * calc(i - 1, 1, 0, 0) % mod);
	for(int i = 0; i <= 10; i++) mod4[i] = cnt[i] = 0;
	mod4[0] = 10;
	for(int i = 0; i < n; i++){
		int lim = s[i] - '0';
		for(int j = 0; j < lim; j++){
			if(i == 0 && j == 0) continue;
			mod4[cnt[j]]--;
			mod4[(cnt[j] + 1) % 4]++;
			add(ans, calc(n - i - 1, mod4[1], mod4[2], mod4[3]));
			mod4[cnt[j]]++;
			mod4[(cnt[j] + 1) % 4]--;
		}
		mod4[cnt[lim]]--;
		cnt[lim] = (cnt[lim] + 1) % 4;
		mod4[cnt[lim]]++;
	}
	if(o) add(ans, calc(0, mod4[1], mod4[2], mod4[3]));
	return ans;
}

void proc(){
    for(int i = 0; i <= len(r); i++) memset(dp[i], -1, sizeof dp[i]);
    cout << (get(r, 1) - get(l, 0) + mod) % mod;
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
