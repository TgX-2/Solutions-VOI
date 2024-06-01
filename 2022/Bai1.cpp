/*-----------------------------
        Author : TgX.2
        10Ti - K28 - CHV
-----------------------------*/

#pragma GCC optimize("O3")
#pragma GCC optimize("O1")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,mmx,abm")
 
#include<bits/stdc++.h>
using namespace std;
 
static struct FastInput {
    static constexpr int BUF_SIZE = 1 << 20;
    char buf[BUF_SIZE];
    size_t chars_read = 0;
    size_t buf_pos = 0;
    FILE *in = stdin;
    char cur = 0;
    
        inline char get_char() {
        if (buf_pos >= chars_read) {
        chars_read = fread(buf, 1, BUF_SIZE, in);
        buf_pos = 0;
        buf[0] = (chars_read == 0 ? -1 : buf[0]);
        }
        return cur = buf[buf_pos++];
    }
    
    inline void tie(int) {}
    
    inline explicit operator bool() {
        return cur != -1;
    }
    
    inline static bool is_blank(char c) {
        return c <= ' ';
    }
    
    inline bool skip_blanks() {
        while (is_blank(cur) && cur != -1) {
        get_char();
        }
        return cur != -1;
    }
    
    inline FastInput& operator>>(char& c) {
        skip_blanks();
        c = cur;
        return *this;
    }
    
    inline FastInput& operator>>(string& s) {
        if (skip_blanks()) {
        s.clear();
        do {
            s += cur;
        } while (!is_blank(get_char()));
        }
        return *this;
    }
    
    template <typename T>
    inline FastInput& read_integer(T& n) {
        // unsafe, doesn't check that characters are actually digits
        n = 0;
        if (skip_blanks()) {
        int sign = +1;
        if (cur == '-') {
            sign = -1;
            get_char();
        }
        do {
            n += n + (n << 3) + cur - '0';
        } while (!is_blank(get_char()));
        n *= sign;
        }
        return *this;
    }
    
    template <typename T>
    inline typename enable_if<is_integral<T>::value, FastInput&>::type operator>>(T& n) {
        return read_integer(n);
    }
    
    #if !defined(_WIN32) | defined(_WIN64)
    inline FastInput& operator>>(__int128& n) {
        return read_integer(n);
    }
    #endif
    
    template <typename T>
    inline typename enable_if<is_floating_point<T>::value, FastInput&>::type operator>>(T& n) {
        // not sure if really fast, for compatibility only
        n = 0;
        if (skip_blanks()) {
        string s;
        (*this) >> s;
        sscanf(s.c_str(), "%lf", &n);
        }
        return *this;
    }
    } fast_input;
    
    #define cin fast_input
    
    static struct FastOutput {
    static constexpr int BUF_SIZE = 1 << 20;
    char buf[BUF_SIZE];
    size_t buf_pos = 0;
    static constexpr int TMP_SIZE = 1 << 20;
    char tmp[TMP_SIZE];
    FILE *out = stdout;
    
    inline void put_char(char c) {
        buf[buf_pos++] = c;
        if (buf_pos == BUF_SIZE) {
        fwrite(buf, 1, buf_pos, out);
        buf_pos = 0;
        }
    }
    
    ~FastOutput() {
        fwrite(buf, 1, buf_pos, out);
    }
    
    inline FastOutput& operator<<(char c) {
        put_char(c);
        return *this;
    }
    
    inline FastOutput& operator<<(const char* s) {
        while (*s) {
        put_char(*s++);
        }
        return *this;
    }
    
    inline FastOutput& operator<<(const string& s) {
        for (int i = 0; i < (int) s.size(); i++) {
        put_char(s[i]);
        }
        return *this;
    }
    
    template <typename T>
    inline char* integer_to_string(T n) {
        char* p = tmp + TMP_SIZE - 1;
        if (n == 0) {
        *--p = '0';
        } else {
        bool is_negative = false;
        if (n < 0) {
            is_negative = true;
            n = -n;
        }
        while (n > 0) {
            *--p = (char) ('0' + n % 10);
            n /= 10;
        }
        if (is_negative) {
            *--p = '-';
        }
        }
        return p;
    }
    
    template <typename T>
    inline typename enable_if<is_integral<T>::value, char*>::type stringify(T n) {
        return integer_to_string(n);
    }
    
    #if !defined(_WIN32) || defined(_WIN64)
    inline char* stringify(__int128 n) {
        return integer_to_string(n);
    }
    #endif
    
    template <typename T>
    inline typename enable_if<is_floating_point<T>::value, char*>::type stringify(T n) {
        sprintf(tmp, "%.17f", n);
        return tmp;
    }
    
    template <typename T>
    inline FastOutput& operator<<(const T& n) {
        auto p = stringify(n);
        for (; *p != 0; p++) {
        put_char(*p);
        }
        return *this;
    }
} fast_output;
 
#define cout fast_output
#define endl '\n'

#define     FOR(i,a,b) for(int i=(a), _b=(b);i<=_b;++i)
#define    FORD(i,a,b) for(int i=(a), _b=(b);i>=_b;--i)
#define   FORSq(i,a,b) for(int i=(a), _b=(b);i*i<=_b;++i)
#define  FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c);i<=_b;i+=_c)
#define     FORSt(i,s) for(int i=0, _s=(int)(s.size());i<_s;++i)

#define             fi first
#define             se second
#define             pb push_back
#define             mp make_pair
#define             pp pop_back()
#define             eb emplace_back
#define            ers erase
#define            ins insert
#define            emp empty()
#define            rvs reverse

#define       BIT(x,i) (((x)>>(i))&1)
#define        MASK(i) (1LL<<(i))
#define      CNTBIT(x) __builtin_popcountll(x)
#define      ODDBIT(x) __builtin_parityll(x)
#define    FIRSTBIT(x) __builtin_ctzll(x)

#define         len(x) (int)((x).size())
#define         all(x) (x).begin(), (x).end()
#define      alln(x,n) (x)+1, (x)+1+(n)

#define             ci const int
#define             cs const string
#define            cll const long long
#define           cull const unsigned long long
#define              _ <<" "<<
#define             __ << "\n"
#define            ___ << " "
#define           ____ << "\t"

#define        dbn(n) cout << #n << " : " << n __ 
#define        dbp(n) cout << #n << ".fi : " << (n).fi << " | " << #n << ".se : " << (n).se __ 
#define    dba(a,l,r) FOR(i,(l),(r)) cout << #a << "[" << i << "] : " << (a)[i] __
#define        dbv(a) for(auto x:(a)) cout << x ___ 
#define       dbvp(a) for(auto x:(a)) dbp(x)

#define         file "pair"
#define ______________TgX______________ signed main()
#define          int long long

using    namespace std;
using    namespace std::chrono;
typedef  long long ll;
typedef  unsigned long long ull;
typedef  string st;
typedef  pair<int,int> pii;
typedef  pair<ll,ll> pll;

void fastio() {
    if (fopen(file".inp", "r")) {
        freopen(file".inp", "r", stdin);
        freopen(file".out", "w", stdout);
    }        
    ios_base::sync_with_stdio(0);
    cin.tie(0);  
}

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a>b) a=b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a<b) a=b; else return 0; return 1;}
/*-----------------------------*/

ci maxn = 2e3+7;
int n,d, a[maxn];
set<int> sum;
vector<pii> pos;

struct _pair {
    int s, i, j;
} dtbn[maxn*maxn];

int f(int sum, int start) {
    bool check[maxn];
    memset(check, 0, sizeof check);
    int _i = start, cnt = 0;
    while (dtbn[_i].s == sum) {
        if (!check[dtbn[_i].i] && !check[dtbn[_i].j]) {
            check[dtbn[_i].i] = check[dtbn[_i].j] = 1;
            cnt++;
        }
        _i++;
    }
    return cnt;
}

void sub1() {
    int x = 0;
    FOR(i,1,n-1) FOR(j,i+1,n) {
        dtbn[++x].s = a[i] + a[j];
        dtbn[x].i   = i;
        dtbn[x].j   = j;
    }
    sort(alln(dtbn,x), [&](const _pair& x, const _pair& y) {
        if (x.s == y.s) {
            if (x.i == y.i) return (x.j > y.j);
            else return (x.i < y.i);
        } else return (x.s < y.s);
    });

    int cursum = -1;
    FOR(i,1,x) {
        if (dtbn[i].s != cursum) {
            cursum = dtbn[i].s;
            pos.pb({cursum, i});
        }
    }
    int ans = INT_MIN;
    for(auto x:pos) {
        maxi(ans, f(x.fi, x.se));
    }
    cout << ans;

}

void sub2() {
    int ans = INT_MIN;
    FOR(i,1,n-1) FOR(j,i+1,n) sum.ins(a[i]+a[j]);
    for(auto x:sum) {
        int l = 1, r = n, cnt = 0;
        while (l < r) {
            if (a[l]+a[r] == x || a[l]+a[r] == x+1) {
                cnt++;
                l++;
                r--;
            } else if (a[l]+a[r] > x+1) r--;
            else if (a[l]+a[r] < x) l++; 
            maxi(ans, cnt);
        }
    }
    cout << ans;
}

void process() {    
    cin >> n >> d;
    FOR(i,1,n) cin >> a[i];
    sort(alln(a,n));

    if (d==0) return sub1(), void();
    else return sub2(), void();
}


/*-----------------------------*/
______________TgX______________ {
    auto start = high_resolution_clock::now();
    fastio();
    process();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cerr << "Time: " << duration.count() << " ms" << endl;  
}


/*==============================+
|             INPUT             |
--------------------------------|

================================+
|            OUTPUT             |
--------------------------------|

===============================*/
