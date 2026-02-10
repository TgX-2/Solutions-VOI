/*-----------------------------
        Author : TgX.2
       12Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>
using namespace std;

#ifdef TGX
#include "debug.h"
#else 
#define debug(...)
#endif

#define FOR(i, a, b)       for (int i = (a), _b = (b); i <= _b; i += 1)
#define FORD(i, a, b)      for (int i = (a), _b = (b); i >= _b; i -= 1)

#define fi                 first
#define se                 second
#define pb                 push_back
#define len(x)             (int)((x).size())
#define all(x)             (x).begin(), (x).end()

#define _                  << " " <<
#define __                 << "\n"
#define ___                << " "

#define ______________TgX______________ main()
#define int                long long

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if (a > b) a = b; else return 0; return 1;}

template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if (a < b) a = b; else return 0; return 1;}
/*-----------------------------*/

const int maxn = 2e5 + 7;
int n, q, a[maxn];

const long long mod1 = 1e9 + 7;
const long long mod2 = 1e9 + 9;
const long long base = 100003;


namespace sub2 {
    int rev[maxn];
    int hasha[maxn], hashb[maxn];
    int revhasha[maxn], revhashb[maxn];
    int powa[maxn], powb[maxn];

    void rabinkarp() {
        FOR(i, 1, n) {
            int j = n - i + 1;
            rev[i] = a[j];
        }


        powa[0] = powb[0] = 1;
        FOR(i, 1, n) {
            powa[i] = (powa[i - 1] * base) % mod1;
            powb[i] = (powb[i - 1] * base) % mod2;
        }

        FOR(i, 1, n) {
            hasha[i] = (hasha[i - 1] * base + a[i]) % mod1;
            hashb[i] = (hashb[i - 1] * base + a[i]) % mod2;
        }

        FOR(i, 1, n) {
            revhasha[i] = (revhasha[i - 1] * base + rev[i]) % mod1;
            revhashb[i] = (revhashb[i - 1] * base + rev[i]) % mod2;
        }
    }

    inline int geta(int l, int r) {
        return (hasha[r] - hasha[l - 1] * powa[r - l + 1] + mod1 * mod1) % mod1;
    }

    inline int getb(int l, int r) {
        return (hashb[r] - hashb[l - 1] * powb[r - l + 1] + mod2 * mod2) % mod2;
    }

    inline int getarev(int l, int r) {
        return (revhasha[r] - revhasha[l - 1] * powa[r - l + 1] + mod1 * mod1) % mod1;
    }

    inline int getbrev(int l, int r) {
        return (revhashb[r] - revhashb[l - 1] * powb[r - l + 1] + mod2 * mod2) % mod2;
    }

    pair<int,int> merge(
        const pair<int,int> &L,
        const pair<int,int> &M,
        const pair<int,int> &R,
        int lenM, int lenR
    ) {
        int a = (
            (L.first * powa[lenM + lenR] % mod1
            + M.first * powa[lenR] % mod1
            + R.first) % mod1
        );

        int b = (
            (L.second * powb[lenM + lenR] % mod2
            + M.second * powb[lenR] % mod2
            + R.second) % mod2
        );

        return {a, b};
    }

    pair<int,int> getrev(const int &ll, const int &rr, const int &l, const int &r) {
        int lenL = l - ll;
        int lenM = r - l + 1;
        int lenR = rr - r;

        auto L = (lenL > 0) ? make_pair(geta(ll, l-1), getb(ll, l-1)) : make_pair(0LL,0LL);
        auto R = (lenR > 0) ? make_pair(geta(r+1, rr), getb(r+1, rr)) : make_pair(0LL,0LL);

        int u = n - r + 1;
        int v = n - l + 1;
        auto M = make_pair(getarev(u, v), getbrev(u, v));

        return merge(L, M, R, lenM, lenR);
    }
        



    int get(const int &l, const int &r) {
        vector<pair<int, int>> sans;
        sans.pb({geta(l, r), getb(l, r)});

        FOR(i, l, r - 1) {
            FOR(j, i + 1, r) {
                // if (geta(i, j) == getarev(n - j + 1, n - i + 1) and
                //     getb(i, j) == getbrev(n - j + 1, n - i + 1))
                //     continue;
                pair<int, int> tar = getrev(l, r, i, j);
                sans.pb(tar);
            }
        }

        sort(all(sans));
        sans.erase(unique(all(sans)), sans.end());
        return len(sans);    
    }

    void sol() {
        rabinkarp();

        int x; cin >> x;
        cout << max(get(1, x - 1), get(x + 1, n));
    }
};


namespace sub3 {
    int get(int l, int r) {
        unordered_map<int, int> col;

        int ans = 1;
        FOR(i, l, r) {
            ans += ((i - l) - col[a[i]]);
            col[a[i]]++;
        }
        return ans;
    }

    void sol()  {
        int x; cin >> x;
        cout << max(get(1, x - 1), get(x + 1, n));
    }
};

const int block_sz = 700;

namespace sub4 {
    struct query {
        int l, r, id;
        bool operator < (const query &other) const {
            int block_a = l / block_sz;
            int block_b = other.l / block_sz;
            if (block_a != block_b) return block_a < block_b;
            return ((block_a & 1) ? (r > other.r) : (r < other.r));
        }
    };

    vector<query> qq;

    int ans[maxn << 1];
    int lenn = 0;
    int anss = 1;
    int cnt[maxn];
    // unordered_map<int, int> cnt;

    inline void add(int pos) {
        anss += (lenn - cnt[a[pos]]);
        cnt[a[pos]]++;
        lenn++;
    }

    inline void del(int pos) {
        lenn--;
        cnt[a[pos]]--;
        anss -= (lenn - cnt[a[pos]]);
    }

    set<pair<int, int>> st;
    vector<int> events[maxn << 1];
    int m;
    map<pair<int,int>, int> comp;

    void sol() {
        st.insert({1, n});
        int idx = 0;
        qq.pb({1, n, ++idx});
        comp[{1, n}] = idx;   // ⭐ BẮT BUỘC
        events[0].pb(idx);


        int time = 0;

        while (q--) {
            int x; 
            cin >> x;
            ++time;

            auto it = st.upper_bound({x, (int)1e18});
            --it;

            int l = it->first;
            int r = it->second;
            int par = comp[{l, r}]; 

            st.erase(it);
            events[time].pb(-par);

            if (l <= x - 1) {
                qq.pb({l, x - 1, ++idx});
                st.insert({l, x - 1});
                comp[{l, x - 1}] = idx;
                events[time].pb(idx);
            }

            if (x + 1 <= r) {
                qq.pb({x + 1, r, ++idx});
                st.insert({x + 1, r});
                comp[{x + 1, r}] = idx;
                events[time].pb(idx);
            }
        }


        sort(all(qq));

        int l = 1, r = 0;
        for(const query &val : qq) {
            while(l > val.l) add(--l);
            while(r < val.r) add(++r);
            while(l < val.l) del(l++);
            while(r > val.r) del(r--);
            ans[val.id] = anss;
        }

        multiset<int> cur;

        for (const int &id : events[0]) cur.insert(ans[id]);

        FOR(t, 1, time) {
            for (const int &e : events[t]) {
                if (e < 0) {
                    auto it = cur.find(ans[-e]);
                    if (it != cur.end()) cur.erase(it);
                } else cur.insert(ans[e]);
            }
            cout << *cur.rbegin() __ ;
        }

    }
};

void process() {
    cin >> n >> q;
    vector<int> val;
    FOR(i, 1, n) {
        cin >> a[i];
        val.pb(a[i]);
    }

    sort(all(val));
    val.erase(unique(all(val)), val.end());
    FOR(i, 1, n) a[i] = lower_bound(all(val), a[i]) - val.begin() + 1;

    if (n <= 2000 and q == 1) sub2::sol();
    else if (q == 1) sub3::sol();
    else sub4::sol();
}



/*-----------------------------*/
______________TgX______________ {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);  
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    } else {
        freopen("tet.inp", "r", stdin);
        freopen("tet.out", "w", stdout);
    }
    process();
    cerr << "Time: " << 1.0 * clock() / CLOCKS_PER_SEC __ ;
}


/*==============================+
|INPUT                          |
--------------------------------|
khi lay dia x di thi chi co doan thuoc x thay doi dap an, va thuong la giam.

khi nao 2 xau dao = nhau

1 2 3 2 1
= n * (n + 1) / 2 - so luong xau palin, dung roi
================================+
|OUTPUT                         |
--------------------------------|
7 1
4 1 3 1 3 2 1
2

===============================*/
