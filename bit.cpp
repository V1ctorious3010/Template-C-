//source:

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;
vector<int> adj[N];
int it, st[N], ed[N], sz[N], parent[N];

struct BinaryIndexedTree {
    int bit[N];

    void up(int x, int val) {
        while (x < N) {
            bit[x] += val;
            x += x & (-x);
        }
    }

    int get(int x) {
        int ret = 0;
        while (x) {
            ret += bit[x];
            x -= x & (-x);
        }
        return ret;
    }

    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
} bit;

int p1, p2, p3;

void dfs(int x, int par = 0) {
    sz[x] = 1; st[x] = ++it; parent[x] = par;
    for (int i : adj[x]) if (i != par) {
        dfs(i, x);
        sz[x] += sz[i];
    }
    ed[x] = it;
    // cerr << x << " " << sz[x] << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    if (fopen("p3tree.inp", "r")) {
        freopen("p3tree.inp", "r", stdin);
        freopen("p3tree.out", "w", stdout);
    }

    #ifdef LOCAL_MACHINE
        if (fopen("task.inp", "r")) {
            freopen("task.inp", "r", stdin);
            freopen("task.out", "w", stdout);
        }
    #endif

    int n; cin >> n;
    cin >> p1 >> p2 >> p3;
    bool swap = 0;
    if (p2 == 1) p2 = 3, swap = 1;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        if (swap) x = n - x + 1, y = n - y + 1;
        adj[x].push_back(y); adj[y].push_back(x);
    }
    dfs(1);
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        int sum_sm = 0, sum_la = 0;
        for (int j : adj[i]) if (j != parent[i]) {
            int si = bit.get(st[j], ed[j]), li = sz[j] - si;
            int so = i - 1 - bit.get(st[i], ed[i]), lo = n - sz[i] - so;
            if (p2 == 3) res += 1LL * si * (sum_sm + so);
            else res += 1LL * li * (so + sum_sm) + 1LL * si * (lo + sum_la);
            sum_sm += si, sum_la += li;
        }
        bit.up(st[i], 1);
    }
    cout << res << "\n";
}

// ඞඞඞඞඞ you sus
