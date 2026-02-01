#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

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
#define len(x) (int)((x).size())
#define pb push_back
#define endl '\n'
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

#define name "aznet"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 2e18+7;
const int N = 1e4 + 5;
const int lmt = 1e5+6;

struct item{
	int u, v, id;
};

int n, m, wa[N], wb[N], sz[N], par[N];
bool check[lmt];
item dsc[lmt];

void make_set(){
	for(int i = 1; i <= n; i++){
		par[i] = i;
		sz[i] = 1;
	}
}

int findd(int u){
	if(par[u] == u) return u;
	return par[u] = findd(par[u]);
}

bool uni(int u, int v){
	int a = findd(u), b = findd(v);
	if(a == b) return false;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	par[b] = a;
	return true;
}

void in(){
    cin >> n >> m;
    for(int i = 1; i < n; i++) cin >> wa[i];
   	for(int i = 1; i < n; i++) cin >> wb[i];

   	for(int i = 1; i <= m; i++){
   		int u, v, id;
   		cin >> u >> v >> id;
   		dsc[i] = {u, v, id};
   	}
}

void proc(){
    make_set();
    for(int i = 1; i <= m; i++) check[i] = 0;
    int cnta = 0, cntb = 0;
    for(int i = 1; i <= m; i++){
    	if(dsc[i].id == 1) cnta += uni(dsc[i].u, dsc[i].v);
    }

    make_set();
    for(int i = 1; i <= m; i++){
    	if(dsc[i].id == 2) cntb += uni(dsc[i].u, dsc[i].v);
    }
    
    int res = 2 * inf, da = 0;
    // 0 <= da <= cnta      0 <= db <= cntb
    //                      0 <= n - da - 1 <= cntb         da >= max(n - cntb - 1, 0)
    for(int i = max(0, n - cntb - 1); i <= cnta; i++){
   		if(mini(res, wa[i] + wb[n - i - 1])) da = i;
    }
    //db = n - da - 1;

    // cay khung dang co nhung canh b
    // add nhung canh A bat buoc phai co trong cay khung
    for(int i = 1; i <= m; i++){
    	if(dsc[i].id == 1) check[i] = uni(dsc[i].u, dsc[i].v);
    }

    make_set();

    int cnt = 0;
    for(int i = 1; i <= m; i++){
    	if(check[i]) cnt += uni(dsc[i].u, dsc[i].v);
    }

    for(int i = 1; i <= m; i++){
    	//cout << i << endl;
    	if(cnt == da) break;
    	if(dsc[i].id == 1 && !check[i]){
    		bool ok = uni(dsc[i].u, dsc[i].v);
    		cnt += ok;
    		check[i] = ok;
    	}
    	
    }

    for(int i = 1; i <= m; i++){
    	if(dsc[i].id == 2) check[i] = uni(dsc[i].u, dsc[i].v);
    }
	
	for(int i = 1; i <= m; i++) if(check[i]) cout << i << " ";
	cout << endl;

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(0);

    rf

    int t = 1;
    cin >> t;

    while(t--){
        in();
        proc();
    }

    cerr << "Time elapsed: " << TIME << "s" << endl;
    return 0;
}
