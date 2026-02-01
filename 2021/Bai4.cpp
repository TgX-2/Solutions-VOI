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

#define name "bonus"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 1e18l+7;
const int M = 1e6+5;
const int N = 3e5+6;
const int LOG = 31 - __builtin_clz(N);

struct Trie{
	struct Node{
		ll val;
		int child[26];
	} node[1 << 20];

	int cur = 0;

	void add(const string &s, ll val){
		int pos = 0;
		for(char c : s){
			maxi(node[pos].val, val);
			if(!node[pos].child[c - 'A']) node[pos].child[c - 'A'] = ++cur;
			pos = node[pos].child[c - 'A'];
		}
	}

	ll get(const string &s){
		int pos = 0;
		for(char c : s){
			if(!node[pos].child[c - 'A']) return 0;
			pos = node[pos].child[c - 'A'];
		}
		return node[pos].val;
	}
} trie;

int n, m, a[N], lim = 0;
string s[N];
vii adj[N], big[N];
ll dp[N], g[N], res = 0;

void in(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
    	cin >> s[i] >> a[i];
    	maxi(lim, a[i]);
    }
    for(int i = 1; i <= m; i++){
    	int u, v; cin >> u >> v;
    	adj[u].pb(v);
    	adj[v].pb(u);
    }
}

void proc(){
	int Block = sqrt(m);
    for(int i = 1; i <= lim; i++){
    	if(len(adj[i]) > Block) for(int j : adj[i]) big[j].pb(i);
    }

	for(int i = 1; i <= n; i++){
		int u = a[i];
		for(int v : big[u]) maxi(dp[u], g[v]);

		ll val = max(dp[u], trie.get(s[i])) + a[i];
		trie.add(s[i], val);
		maxi(res, val);

		if(len(adj[u]) <= Block){
			for(int v : adj[u]) maxi(dp[v], val);
		}
		else maxi(g[u], val);
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
