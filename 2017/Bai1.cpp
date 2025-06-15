#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, sta, k;
unordered_map<int, int> f;

int fib(int n) {
    if (f.count(n)) return f[n];
    int x = n / 2;
    if (n % 2 == 0) 
        return f[n] = (fib(x) * fib(x) % k + 2 * fib(x) * fib(x - 1) % k) % k;
    else 
        return f[n] = (fib(x) * fib(x) % k + fib(x + 1) * fib(x + 1) % k) % k;
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    int t; cin >> t;
    while(t--) {
        cin >> n >> sta >> k; 
        f.clear();
        f[0] = 0;
        f[1] = f[2] = 1;

        int sum = 0;
        unordered_map<int, int> m;

        int a = fib(sta);
        sum = (sum + a) % k;
        m[sum] = sta;

        int b = fib(sta + 1);
        sum = (sum + b) % k;
        m[sum] = sta + 1;

        int l = 0, r = 0;

        for(int i = sta + 2; i <= sta + n - 1; i++) {
            int c = (a + b) % k;
            a = b; 
            b = c;

            sum = (sum + c) % k;
            if (m.count(sum)) {
                l = m[sum] + 1;
                r = i;
                break;
            }

            m[sum] = i;
        }

        cout << (r - l + 1) << " ";
        for(int i = l; i <= r; i++) cout << i << " ";
        cout << "\n";
    }

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}