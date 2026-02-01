#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pl pair<ll, pii>
#define fi first
#define se second
#define pb push_back

using namespace std;
const ll inf = 2e18+7;
const int lmt = 1e5+7;

struct dt{
	int v, t, l;
};

vector<dt> a[lmt];
ll d[lmt];
int n, m, s, t, k;

void in(){
	cin >> n >> m >> s >> t >> k;
	for(int i = 1; i <= m; i++){
		int u, v, t;
		cin >> u >> v >> t;
		a[u].pb({v, t, i});
	}
}

void djk(){
	for(int i = 1; i <= n; i++) d[i] = inf;
	d[s] = 0;
	priority_queue<pl, vector<pl>, greater<pl>> q;
	q.push({0, {s, 0}});
	while(!q.empty()){
		pii p = q.top().se;
		ll val = q.top().fi;
		q.pop();
		int u = p.fi;
		int tmp = p.se;
		if(val > d[u]) continue;
		for(auto x : a[u]){
			int v = x.v;
			ll t = x.t;
			int l = x.l;
			if(tmp == 0){
				if(d[v] > d[u] + t){
					d[v] = d[u] + t;
					q.push({d[v], {v, l}});
				}
			}
			else if(d[v] > d[u] + t + tmp*k + l){
				d[v] = d[u] + t + tmp*k + l;
				q.push({d[v], {v, l}});
			}
		}
	}
}

void proc(){
	djk();
	if(d[t] == inf) cout << -1; else cout << d[t];

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	in();
	proc();

	return 0;
}
