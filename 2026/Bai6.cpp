/*-----------------------------
        Author : TgX.2
       12Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>
using   namespace std;

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

template<typename T1, typename T2> 
bool mini(T1 &a, T2 b)
    {if (a > b) a = b; else return 0; return 1;}

template<typename T1, typename T2> 
bool maxi(T1 &a, T2 b)
    {if (a < b) a = b; else return 0; return 1;}
/*-----------------------------*/

const int maxn = 1000;
const double InitTemp = 1000000000;
double ansa = 1000000000, cura = 1000000000;
vector<pair<double, double>> ansb, curb;
vector<pair<int, int>> ansc, curc;

int hailam;
double ln;

double fff(double x) {
    if (x > 360.0) {
        x -= 360.0;
    }
    return x;
}

struct val {
    int u, v;
    double w;

    val(int u = 0, int v = 0, double w = 0.0) : u(u), v(v), w(w) {};
    bool operator<(const val &other) const {
        return w < other.w;
    };
};

vector<val> edge;
struct dosu {
    int n, child[maxn], par[maxn];

    dosu(int _n = 0) : n(_n) {}

    void init() {
        FOR(i, 1, n) {
            par[i] = i;
            child[i] = 1;
        }
    }

    int find(int u) {
        return (par[u] == u ? u : par[u] = find(par[u]));
    }

    bool merge(int u, int v) {
        int a = find(u);
        int b = find(v);
        if (a == b) return 0;
        if (child[a] < child[b]) swap(a, b);
        par[b] = a;
        child[a] += child[b];
        return 1;
    }
};

double dist(const pair<double, double> &a, const pair<double, double> &b) {
    double dx = a.fi - b.fi;
    double dy = a.se - b.se;
    return sqrt(dx * dx + dy * dy);
}

double cal() {
    edge.clear();
    curc.clear();

    FOR(i, 0, len(curb) - 2) {
        FOR(j, i + 1, len(curb) - 1) {
            edge.pb(val(i, j, dist(curb[i], curb[j])));
        }
    }
    sort(all(edge));

    double ans = 0.0;
    dosu dsu(len(edge) + 7);
    dsu.init();
    for(const val &valu : edge) {
        if (dsu.merge(valu.u, valu.v)) {
            curc.pb({valu.u, valu.v});
            ans += valu.w;
        }
    }
    return ans;
}

#define pi acos(-1)
pair<double, double> decac(const double &r, const double &a) {
    double x = r * cos(a * pi * 1.0 / 180);
    double y = r * sin(a * pi * 1.0 / 180);
    return {x, y};
}


double rand_double(double l, double r) {
    return l + (r - l) * (double)rand() / RAND_MAX;
}

pair<double, double> get(double R) {
    double theta = rand_double(0, 2 * pi);
    double u = rand_double(0, 1);
    double r = R * sqrt(u);

    double x = r * cos(theta);
    double y = r * sin(theta);
    return {x, y};
}


double calP(double pre, double cur, double temp) {
    return exp((pre - cur) / temp);
}

bool isValid(double pre, double cur, double temp) {
    if (cur < pre) return 1; 
    int x = 1 + rand();
    int y = 1 + rand();
    x %= y;
    return (x * 1.0 / y <= calP(pre, cur, temp));
}

int getint(int l, int r) {
    return l + rand() % (r - l + 1);
}


void SA(double temp) {
    vector<pair<double, double>> tmp;
    FOR(i, 1, hailam) {
        tmp.pb(curb.back());
        curb.pop_back();
    }

    double delta = rand_double(0.1, 50.0);

    FOR(i, 1, hailam) {
        double x = tmp[i - 1].fi, y = tmp[i - 1].se;
        vector<pair<double, double>> valid;
        valid.pb({x, y});
        double xx, yy;
        FOR(j, 0, 1) FOR(k, 0, 1) {
            if (j == 0) xx = x + delta;
            else xx = x - delta;
            if (k == 0) yy = y + delta;
            else yy = y - delta;
            if (dist({0, 0}, {xx, yy}) <= 100.0) valid.pb({xx, yy}); 
        }
        int idx = getint(0, 1000) % len(valid);
        curb.pb(valid[idx]);
    }

    double nxt = cal();
    if (isValid(cura, nxt, temp)) {
        cura = nxt;
        if (nxt < ansa) {
            ansa = nxt;
            ansb = curb;
            ansc = curc;
        }
    } else {
        FOR(i, 1, hailam) curb.pop_back();
        while(len(tmp)) {
            curb.pb(tmp.back());
            tmp.pop_back();
        }
    }
}




void process() {
    int n; cin >> n;

    if (n == 3) ln = 0.99999;
    else ln = 0.9999;

    FOR(i, 1, n) {
        int a; cin >> a;
        curb.pb(decac(100.0, a));
    }

    hailam = n - 2;

    FOR(i, 1, hailam) {
        pair<double, double> xxx = get(100.0);
        curb.pb(xxx);
    }

    ansa = cal();
    ansb = curb;
    ansc = curc;
    double curTemp = InitTemp;
    while(clock() * 1.0 / CLOCKS_PER_SEC < 2.93) {
        SA(curTemp);
        curTemp *= ln;
    }

    cout << hailam __ ;
    FOR(i, n, n + hailam - 1) cout << ansb[i].fi _ ansb[i].se __ ;
    for(const pair<int, int> &valu : ansc) cout << (valu.fi + 1) _ (valu.se + 1) __ ;
}




/*-----------------------------*/
______________TgX______________ {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    } else {
        freopen("camp.inp", "r", stdin);
        freopen("camp.out", "w", stdout);
    }
    cout << fixed << setprecision(4);
    process();
    cerr << "Time: " << 1.0 * clock() / CLOCKS_PER_SEC << " s." __ ;
}


/*==============================+
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|
-35.2998 -25.7231
26.2881 -53.1193
-42.5969 41.5661
457.435


===============================*/
