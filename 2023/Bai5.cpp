#include <bits/stdc++.h>

using namespace std;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

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
#define vi vector<int>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'

#define name "sdev"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9 + 7;
const int inf = 1e9 + 9;
const ll  oo  = 1e18l + 7;
const int M   = 5e5 + 6;
const int N   = 1e5 + 6;
const int LOG = 31 - __builtin_clz(N);

struct item{
	int l, b, r, t;
};

struct Event{
	int x, l, r, d;

	bool operator < (const Event &it) const{
		return x < it.x;
	}
};

int n;
ll K;
item a[N];
vector<Event> e;
vi vec;
int m = 0, lim = 5e7 + 1;

struct Segment{
	int st[N << 2], cnt[N << 2];

	void init(int n){
		for(int i = 1; i <= n * 4; i++) st[i] = cnt[i] = 0;
	}

	void down(int id, int l, int r){
        if(st[id] > 0) cnt[id] = vec[r + 1] - vec[l];
        else if(l == r) cnt[id] = 0;
        else cnt[id] = cnt[id << 1] + cnt[id << 1 | 1];
    }

	void update(int id, int l, int r, int u, int v, int val){
        if(l > v || r < u) return;
        if(l >= u && r <= v){
            st[id] += val;
            down(id, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, val);
        update(id << 1 | 1, mid + 1, r, u, v, val);

        down(id, l, r);
    }

    ll query(int id, int l, int r, int xl, int xr, int D){
    	int yl = vec[l], yr = vec[r + 1] - 1;
    	if(cnt[id] == 0 || xl + yl > D) return 0;
    	if(st[id]){
	    	ll res = 0;
	    	int m1 = min(xr, D - yr);
	    	if(xl <= m1) res += 1LL * (m1 - xl + 1) * (yr - yl + 1);
	    	ll m2 = max(xl, m1 + 1), m3 = min(xr, D - yl);
	    	if(m2 <= m3){
	    		int n = m3 - m2 + 1, a1 = (D - m2) - yl + 1, a2 = (D - m3) - yl + 1;
	    		res += 1LL * (a1 + a2) * n / 2;   // sum
	    	}
	    	return res;
    	}

    	int mid = (l + r) >> 1;
    	return query(id << 1, l, mid, xl, xr, D) + query(id << 1 | 1, mid + 1, r, xl, xr, D);
    }
} it;

void inp(){
    cin >> n >> K;
    for(int i = 1; i <= n; i++) cin >> a[i].l >> a[i].b >> a[i].r >> a[i].t;
}

void compress(){
	vec.pb(0);
	for(int i = 1; i <= n; i++){
		vec.pb(a[i].b);
		vec.pb(a[i].t + 1);
	}
	vec.pb(lim);
	sort(all(vec));
	vec.erase(unique(all(vec)), vec.end());
	for(int i = 1; i <= n; i++){
    	a[i].b = lower_bound(all(vec), a[i].b) - vec.begin();
    	a[i].t = lower_bound(all(vec), a[i].t + 1) - vec.begin() - 1;
    }
    m = len(vec) - 1;
}

bool check(int val){
	it.init(m + 1);
	ll ans = 0;
	int i = 0; 
    while(i < len(e)){
    	int j = i;
    	while(j < len(e) && e[i].x == e[j].x){
    		it.update(1, 0, m, e[j].l, e[j].r, e[j].d);
    		j++;
    	}
    	i = j;
    	if(j < len(e)) ans += it.query(1, 0, m, e[j - 1].x, e[j].x - 1, val);
    	if(ans >= K) return true;
    }
    return false;
}

void proc(){
    compress();
    for(int i = 1; i <= n; i++){
    	e.pb({a[i].l, a[i].b, a[i].t, 1});
    	e.pb({a[i].r + 1, a[i].b, a[i].t, -1});
    }
    sort(all(e));

    int l = 2, r = 1e8, res = 1e8;
    while(l <= r){
    	int mid = (l + r) >> 1;
    	if(check(mid)){
    		res = mid;
    		r = mid - 1;
    	}
    	else l = mid + 1;
    }
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
