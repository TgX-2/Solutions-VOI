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

const int maxn = 107;
const int base1 = 311;
const int base2 = 331;
const int base12 = 311 * 331;

int n, m;
char a[maxn][maxn], b[maxn][maxn];
int powa[maxn], powb[maxn];
int hasha[maxn][maxn], hashb[maxn][maxn];

void rabinkarp() {
    FOR(i, 1, n) FOR(j, 1, m) {
        hasha[i][j] = hasha[i - 1][j] * base1
                    + hasha[i][j - 1] * base2
                    - hasha[i - 1][j - 1] * base12 + (a[i][j] - 'a' + 1);
        hashb[i][j] = hashb[i - 1][j] * base1
                    + hashb[i][j - 1] * base2
                    - hashb[i - 1][j - 1] * base12 + (b[i][j] - 'a' + 1);
    }
}

int geta(int x1, int y1, int x2, int y2) {
    return hasha[x2][y2]
         - hasha[x1 - 1][y2] * powa[x2 - x1 + 1] 
         - hasha[x2][y1 - 1] * powb[y2 - y1 + 1]
         + hasha[x1 - 1][y1 - 1] * powa[x2 - x1 + 1] * powb[y2 - y1 + 1];
}

int getb(int x1, int y1, int x2, int y2) {
    return hashb[x2][y2]
         - hashb[x1 - 1][y2] * powa[x2 - x1 + 1]  
         - hashb[x2][y1 - 1] * powb[y2 - y1 + 1] 
         + hashb[x1 - 1][y1 - 1] * powa[x2 - x1 + 1] * powb[y2 - y1 + 1];
}

bool check(int h, int w) {
    unordered_set<int> s;
    FOR(i, 1, n - h + 1) FOR(j, 1, m - w + 1) {
        int x = geta(i, j, i + h - 1, j + w - 1);
        s.insert(x);
    }

    FOR(i, 1, n - h + 1) FOR(j, 1, m - w + 1) {
        int x = getb(i, j, i + h - 1, j + w - 1);
        if (s.find(x) != s.end()) return 1;
    }
    return 0;
}


void process() {
    cin >> n >> m;
    FOR(i, 1, n) FOR(j, 1, m) cin >> a[i][j];
    FOR(i, 1, n) FOR(j, 1, m) cin >> b[i][j];

    rabinkarp();

    int ans = 0;
    int w = m;
    FOR(h, 1, n) {
        while(check(h, w) == 0) w--;
        maxi(ans, h * w);
    }

    cout << ans __ ;
}




/*-----------------------------*/
______________TgX______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    powa[0] = powb[0] = 1;
    FOR(i, 1, 101) {
        powa[i] = powa[i - 1] * base1;
        powb[i] = powb[i - 1] * base2;
    }

    int t; cin >> t;
    while(t--) process();
    cerr << "Time: " << 1.0 * clock() / CLOCKS_PER_SEC << " s." __ ;
}


/*==============================+
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|

===============================*/
