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

#define name "workout"

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

int n, m, k;
vector<pii> adj[N];
int p[15], a[15], b[15];
vii ez, hard;
ll d[11][N];
bool vis[N];
int numez = 0;
ll dp[N][1 << 5][7];

void in(){
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++){
    	int u, v, w; cin >> u >> v >> w;
    	adj[u].pb({v, w});
    	adj[v].pb({u, w});
    }
    for(int i = 1; i <= k; i++){
    	if(i == 1) cin >> a[i] >> b[i];
    	else{
    		cin >> p[i] >> a[i] >> b[i];
    		if(p[i]) ez.pb(i); else hard.pb(i);
    	}
    }
    numez = len(ez);
}

#define pll pair<ll, int>

void djk(int id, ll d[]){
	for(int i = 1; i <= n; i++) d[i] = oo;
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	pq.push({d[a[id]] = 0, a[id]});
	while(!pq.empty()){
		pll p = pq.top(); pq.pop();
		ll val = p.fi;
		int u = p.se;
		if(val != d[u]) continue;
		for(auto it : adj[u]){
			int v = it.fi, w = it.se;
			if(mini(d[v], d[u] + w)) pq.push({d[v], v});
		}
	}

	vis[b[id]] = true;
	queue<int> q;
	q.push(b[id]);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto it : adj[u]){
			int v = it.fi, w = it.se;
			if(d[v] + w == d[u] && !vis[v]){
				vis[v] = true;
				q.push(v);
			}
		}
	}

	for(int i = 1; i <= n; i++) if(!vis[i]) d[i] = oo; else vis[i] = 0;
}

ll calc(int u, int mask, int cur){
	if(u == b[1]) return 0;
	if(dp[u][mask][cur] != -1) return dp[u][mask][cur];
	
	ll res = 0;
	for(auto it : adj[u]){
		int v = it.fi, w = it.se;
		if(d[1][u] + w != d[1][v]) continue;
		
		if(cur < numez && d[ez[cur]][u] + w == d[ez[cur]][v]) maxi(res, calc(v, mask, cur) + w);

		bool ok = false;
		for(int id : hard){
			if(d[id][u] == d[1][u] && d[id][u] + w == d[id][v]){
				ok = true;
				break;
			}
		}
		if(ok) maxi(res, calc(v, mask, numez) + w);
		else{
			for(int i = 0; i < numez; i++){
				if(bit(i, mask)) continue;
				if(d[ez[i]][u] + w == d[ez[i]][v]) maxi(res, calc(v, mask | (1 << i), i) + w);
			}
			maxi(res, calc(v, mask, numez));
		}
	}

	return dp[u][mask][cur] = res;
}

void proc(){
    for(int i = 1; i <= k; i++) djk(i, d[i]);

    memset(dp, -1, sizeof dp);
    cout << calc(a[1], 0, numez);
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
