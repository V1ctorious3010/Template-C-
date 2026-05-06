#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 50005;
long long tree[4 * MAXN];
long long lazy_node[4 * MAXN];

// Đẩy giá trị lazy xuống các nút con
void push(int node) {
    if (lazy_node[node] != 0) {
        tree[2 * node] += lazy_node[node];
        lazy_node[2 * node] += lazy_node[node];

        tree[2 * node + 1] += lazy_node[node];
        lazy_node[2 * node + 1] += lazy_node[node];

        lazy_node[node] = 0;
    }
}

// Cập nhật cộng thêm val vào đoạn [l, r]
void update(int node, int start, int end, int l, int r, long long val) {
    if (start > r || end < l) return;

    if (start >= l && end <= r) {
        tree[node] += val;
        lazy_node[node] += val;
        return;
    }

    push(node);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);

    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

// Truy vấn giá trị lớn nhất trong đoạn [l, r]
long long query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return -1e18; // Trả về số rất nhỏ nếu nằm ngoài đoạn

    if (start >= l && end <= r) return tree[node];

    push(node);
    int mid = (start + end) / 2;
    long long p1 = query(2 * node, start, mid, l, r);
    long long p2 = query(2 * node + 1, mid + 1, end, l, r);

    return max(p1, p2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    while (m--) {
        int type, x, y;
        cin >> type >> x >> y;

        if (type == 0) {
            long long v;
            cin >> v;
            update(1, 1, n, x, y, v);
        } else if (type == 1) {
            cout << query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}
