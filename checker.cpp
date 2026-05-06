//source:

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l, ll r) {
    return l + rng() % (r - l + 1);
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int nTest = 1; nTest <= 100; ++nTest) {
        cerr << "Test #" << nTest << ":\n";

        ofstream cout("task.inp");

        int a = rnd(0, 10), c = rnd(0, 10), k = rnd(1, 10), m = rnd(1, 1e6), n = rnd(1, 5);
        cout << a << " " << c << " " << k << " " << m << " " << n << "\n";
        for (int i = 0; i < n; ++i) cout << rnd(0, 1);

        cout.close();

        // COMPARE
        system("trau.exe"); system("bits.exe");
        if (system("fc task.out task.ans")) exit(0);

        //CUSTOM CHECKER
        // system("task.exe");
        // if (system("check.exe")) exit(0);
    }
}
