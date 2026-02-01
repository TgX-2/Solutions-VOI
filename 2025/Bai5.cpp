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

#define name "tseq"

template<typename T1, typename T2> bool mini(T1 &a, T2 b) {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b) {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9 + 7;
const int inf = 1e9 + 9;
const ll  oo  = 1e18l + 7;
const int M   = 5e5 + 6;
const int N   = 2e6 + 6;
const int LOG = 31 - __builtin_clz(N);

struct item{
	int t, x, y;
};

int q;
item que[N];
vi vecEnd;
int m, nxt[N];
int num = -1, pos[N];
pii seg[N], posSeg[N];
pair<ll, int> bit[N];

// cac doan duoc danh so tu 0...

ll calc(int l, int r){
	return 1LL * (l + r) * (r - l + 1) / 2;
}

void update(int id, int l, int r, int k){
	id++;
	if(k == 1) posSeg[id] = make_pair(l, r); else posSeg[id] = make_pair(0, -1);
	for(; id <= num + 1; id += id & (-id)){
		bit[id].fi += 1LL * k * calc(l, r);
		bit[id].se += k * (r - l + 1);
	}
}

ll get(int k){
	ll sum = 0;
	int pos = 0, idx = 0;
	for(int i = LOG; i >= 0; i--){
		if(pos + (1 << i) <= num + 1 && idx + bit[pos + (1 << i)].se <= k){
			pos += (1 << i);
			sum += bit[pos].fi;
			idx += bit[pos].se;
		}
	}
	pos++;
	if(idx < k){
		assert(k - idx <= posSeg[pos].se - posSeg[pos].fi + 1);
		sum += calc(posSeg[pos].fi, posSeg[pos].fi + k - idx - 1);
	}
	return sum;
}

void inp(){
    cin >> q;
    for(int i = 1; i <= q; i++) cin >> que[i].t >> que[i].x >> que[i].y;
}

int getID(int x){
	return lower_bound(all(vecEnd), x) - vecEnd.begin();
}

vi getSegment(int l, int r, int x){
	vi ans;
	int id = getID(l - 1) + 1;
	while(id < m && vecEnd[id] <= r){
		seg[id] = make_pair(vecEnd[id - 1] + 1, vecEnd[id]);
		ans.pb(id);
		id++;
	}
	int pref = x, nxtprev = nxt[x];
	for(int id : ans){
		// pre[id] = pref;
		nxt[pref] = id;
		pref = id;
	}
	nxt[pref] = nxtprev;
	// if(nxtprev != -1) pre[nxtprev] = pref;
	return ans;
}

void proc(){
	int cur = 1;
    for(int i = 1; i <= q; i++){
    	if(que[i].t == 1){
    		vecEnd.pb(cur + que[i].y - 1);
    		vecEnd.pb(que[i].x);
    		cur += que[i].y;
    	}
    	else if(que[i].t == 2) vecEnd.pb(que[i].x);
    }
    vecEnd.pb(0);
    sort(all(vecEnd));
    vecEnd.erase(unique(all(vecEnd)), vecEnd.end());
    m = len(vecEnd);

    for(int i = 0; i < m; i++){
    	// pre[i] = -1;
    	nxt[i] = -1;
    }

    cur = 1;
    for(int i = 1; i <= q; i++){
 		if(que[i].t == 1){
 			int id = getID(que[i].x);
 			vi tmp = getSegment(cur, cur + que[i].y - 1, id);
 			cur += que[i].y;
 		}
    }
    int p = 0;
    while(p != -1){
    	pos[p] = ++num;
    	p = nxt[p];
    }
    update(pos[0], 0, 0, 1);
    cur = 1;
    for(int i = 1; i <= q; i++){
    	if(que[i].t == 1){
    		int id = getID(que[i].x);
 			vi tmp = getSegment(cur, cur + que[i].y - 1, id);
 			for(int id : tmp) update(pos[id], seg[id].fi, seg[id].se, 1);
 			cur += que[i].y;
    	}
    	else if(que[i].t == 2){
    		int idx = getID(que[i].x), st = idx;
    		idx = nxt[idx];
    		while(que[i].y > 0){
    			auto &[l, r] = seg[idx];
    			if(que[i].y < r - l + 1){
    				update(pos[idx], l, r, -1);
    				l += que[i].y;
    				update(pos[idx], l, r, 1);
    				que[i].y = 0;
    			}
    			else{
    				update(pos[idx], l, r, -1);
    				que[i].y -= (r - l + 1);
    				idx = nxt[idx];
    			}
    		}
    		nxt[st] = idx;
    		// if(idx != -1) pre[idx] = st;
    	}
    	else cout << get(que[i].y) - get(que[i].x - 1) << endl;
    }
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
