#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 6;

int n;
int a[N];
int L[N], R[N];
int dp[N], trace[N];

void initialize() {
    vector<int> S;
    for (int i = 1; i <= n; ++i) {
        L[i] = i;
        while (!S.empty() && S.back() > i - a[i])
	    L[i] = min(L[i], L[S.back()]), S.pop_back();
        S.push_back(i);
    }
    S.clear();
    for (int i = n; i >= 1; --i) {
        R[i] = i;
        while (!S.empty() && S.back() < i + a[i])
	    R[i] = max(R[i], R[S.back()]), S.pop_back();
        S.push_back(i);
    }
}

void solve() {
    for (int i = 1; i <= n; ++i) dp[i] = i, trace[i] = -i;
    vector<int> S;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] > dp[L[i] - 1] + 1) dp[i] = dp[L[i] - 1] + 1, trace[i] = -(L[i]);
        while (!S.empty() && R[S.back()] < i) S.pop_back();
        if (!S.empty() && dp[i] > dp[S.back() - 1] + 1) {
            dp[i] = dp[S.back() - 1] + 1;
            trace[i] = S.back();
        }
        if (S.empty() || (dp[S.back() - 1] > dp[i - 1])) S.push_back(i);
    }
    cout << dp[n] << endl;
    for (int i = n; i; i = abs(trace[i]) - 1)
	cout << (trace[i] < 0 ? -i : trace[i]) << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    initialize();
    solve();
    return 0;
}
