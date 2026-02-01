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

#define name "comstr"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 1e18l+7;
const int M = 5e5+6;
const int N = 1e5+6;
const int LOG = 31 - __builtin_clz(N);

int n, n1, n2, r;
string s;
vii v[30];
int cnt[N][26], num[N];

void in(){
    cin >> n >> n1 >> n2 >> r;
    cin >> s;
}

void proc(){
    for(int i = 1; i <= n2; i++) v[2].pb(i);

    for(int i = n2 + 1; i <= n1 + n2; i++) v[1].pb(i);

    int k = 2;
    while((int)v[k].size() < n) {
        k++;
        v[k] = v[k - 1];
        for(int x : v[k - 2]) v[k].pb(x);
    }
	
	for(int i = n1 + n2; i < n; i++){
		int id = v[k][i];
		cnt[id][s[i] - 'A']++;
		num[id]++;
	}
	
	int res = 0;
	vii tmp;
	for(int i = 1; i <= n1 + n2; i++){
		int d = cnt[i][s[i - 1] - 'A'];
		res += num[i] - d;

		int mx = 0;
		for(int j = 0; j < 26; j++) maxi(mx, cnt[i][j]);
		tmp.pb(mx - d);
	}
	sort(all(tmp), greater<int>());
	for(int i = 0; i < r; i++) res -= tmp[i];
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
