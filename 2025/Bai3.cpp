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
#define plx pair<ll, int>
#define vi vector<int>
#define vvi vector<vi>
#define all(a) (a).begin(), (a).end()
#define len(x) ((int)(x).size())
#define pb push_back
#define endl '\n'
#define ub(x, i) upper_bound(all(x), i) - x.begin()
#define lb(x, i) lower_bound(all(x), i) - x.begin()

#define name "pnum"

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a < b) a = b; else return 0; return 1;}

const int mod = 1e9+7;
const int inf = 1e9+9;
const ll oo = 1e18l+7;
const int M = 5e5+6;
const int N = 1e3+6;
const int LOG = 31 - __builtin_clz(N);

int k, T;
int m, a[N], cnt[16];

void add(int &x, const int &y){
    x += y;
    if(x >= mod) x -= mod;
}

void sub(int &x, const int &y){
    x -= y;
    if(x < 0) x += mod;
}

void inp(){
    cin >> k >> T;
}

int check(){
    memset(cnt, 0, sizeof cnt);
    cnt[0]++;
    cnt[a[m]]++;
    int cur = a[m];
    for (int i = m - 1; i >= 1; i--){
        if((a[i] + a[i + 1]) % 5 == 0) return 0;
        cur ^= a[i];
        cnt[cur]++;
    }
    int res = 0;
    for (int i = 0; i < 16; i++) res += cnt[i] * (cnt[i] - 1) / 2;
    return res;
}

namespace query1{
    int dp[1002][18][5][2];
    // w = 16 chua mo, w = 17 dong

    int calc(int id, int w, int mod5, bool st, bool o){
        if(id == 0) return (w == 0 || w == 17);
        if(dp[id][w][mod5][st] != -1 && !o) return dp[id][w][mod5][st];

        int res = 0;
        int d = (o) ? a[id] : 9;
        for(int i = 0; i <= d; i++){
            int nw = (i == d) ? o : false;
            if(!st && i == 0){
                add(res, calc(id - 1, w, mod5, false, nw));
                continue;
            }
            if((mod5 + i) % 5 == 0 && st) continue;
            int du = (i >= 5 ? i - 5 : i);
            if(w < 16){
                add(res, calc(id - 1, w ^ i, du, true, nw));
                if(w == 0) add(res, calc(id - 1, 17, du, true, nw));
            }
            else if(w == 16){
                add(res, calc(id - 1, 16, du, true, nw));
                add(res, calc(id - 1, i, du, true, nw));
            }
            else add(res, calc(id - 1, 17, du, true, nw));
        }
        if(!o) return dp[id][w][mod5][st] = res;
        return res;
    }

    int get(const string &s){
        m = len(s);
        for(int i = 0; i < m; i++) a[m - i] = s[i] - '0';
        return calc(m, 16, 0, false, true);
    }

    void solve(){
        memset(dp, -1, sizeof dp);
        while(T--){
            string l, r; cin >> l >> r;
            int ans = (get(r) - get(l) + mod) % mod;
            add(ans, check());
            cout << ans << endl;
        }
    }
}

namespace query2{
    int dp[1002][18][18][5][2];
    // w = 16 chua mo, w = 17 dong

    int calc(int id, int w, int w2, int mod5, bool st, bool o){
        if(id == 0) return ((w == 0 || w == 17) && (w2 == 0 || w2 == 17));
        if(dp[id][w][w2][mod5][st] != -1 && !o) return dp[id][w][w2][mod5][st];

        int res = 0;
        int d = (o) ? a[id] : 9;
        for(int i = 0; i <= d; i++){
            int nw = (i == d) ? o : false;
            if(!st && i == 0){
                add(res, calc(id - 1, w, w, mod5, false, nw));
                continue;
            }
            if((mod5 + i) % 5 == 0 && st) continue;
            int du = (i >= 5 ? i - 5 : i), xor1 = w ^ i, xor2 = w2 ^ i;
            if(w < 16){
                if(w2 < 16){
                    add(res, calc(id - 1, xor1, xor2, du, true, nw));
                    if(w2 == 0) add(res, calc(id - 1, xor1, 17, du, true, nw));
                    if(w == 0){
                        add(res, calc(id - 1, 17, xor2, du, true, nw));
                        if(w2 == 0) add(res, calc(id - 1, 17, 17, du, true, nw));
                    }
                }
                else if(w2 == 16){
                    add(res, calc(id - 1, xor1, 16, du, true, nw));
                    add(res, calc(id - 1, xor1, i, du, true, nw));
                    if(w == 0){
                        add(res, calc(id - 1, 17, 16, du, true, nw));
                        add(res, calc(id - 1, 17, i, du, true, nw));
                    }
                }
                else{
                    add(res, calc(id - 1, xor1, 17, du, true, nw));
                    if(w == 0) add(res, calc(id - 1, 17, 17, du, true, nw));
                }
            }
            else if(w == 16){
                if(w2 < 16){
                    add(res, calc(id - 1, 16, xor2, du, true, nw));
                    add(res, calc(id - 1, i, xor2, du, true, nw));
                    if(w2 == 0){
                        add(res, calc(id - 1, 16, 17, du, true, nw));
                        add(res, calc(id - 1, i, 17, du, true, nw));
                    }
                }
                else if(w2 == 16){
                    add(res, calc(id - 1, 16, 16, du, true, nw));
                    add(res, calc(id - 1, 16, i, du, true, nw));
                    add(res, calc(id - 1, i, 16, du, true, nw));
                    add(res, calc(id - 1, i, i, du, true, nw));
                }
                else{
                    add(res, calc(id - 1, 16, 17, du, true, nw));
                    add(res, calc(id - 1, i, 17, du, true, nw));
                }
            }
            else{
                if(w2 < 16){
                    add(res, calc(id - 1, 17, xor2, du, true, nw));
                    if(w2 == 0) add(res, calc(id - 1, 17, 17, du, true, nw));
                }
                else if(w2 == 16){
                    add(res, calc(id - 1, 17, 16, du, true, nw));
                    add(res, calc(id - 1, 17, i, du, true, nw));
                }
                else add(res, calc(id - 1, 17, 17, du, true, nw));
            }
        }
        if(!o) return dp[id][w][w2][mod5][st] = res;
        return res;
    }

    int get(const string &s){
        m = len(s);
        for(int i = 0; i < m; i++) a[m - i] = s[i] - '0';
        return calc(m, 16, 16, 0, false, true);
    }

    bool kt(const string &l, const string &r){
        if(len(r) - len(l) > 0) return 0;
        if(l[0] != '1') return 0;
        for(int i = 1; i < len(l); i++) if(l[i] != '0') return 0;
        for(char c : r) if(c != '9') return 0;
        return 1;
    }

    void solve(){
        memset(dp, -1, sizeof dp);
        while(T--){
            string l, r; cin >> l >> r;
            if(kt(l, r)){
                int ans = -get(l);
                ans = (ans + get(l + "0") + mod) % mod;
                if(l == "10") add(ans, 1);
                if(r == "9") sub(ans, 1);
                cout << ans << endl;
            }
            else{
                int ans = (get(r) - get(l) + mod) % mod, tmp = check();
                add(ans, 1LL * tmp * tmp % mod);
                cout << ans << endl;
            }
        }
    }
}

void proc(){
    if(k == 1){
        query1::solve();
        return;
    }
    query2::solve();
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
