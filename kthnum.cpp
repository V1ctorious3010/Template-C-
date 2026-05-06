#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

struct Node {
    int count;
    int left, right;
} tree[MAXN * 20];

int root[MAXN], a[MAXN];
vector<int> vals;
int node_cnt = 0;

// Xây dựng cây rỗng ban đầu
int build(int l, int r) {
    int id = ++node_cnt;
    tree[id].count = 0;
    if (l == r) return id;
    int mid = l + (r - l) / 2;
    tree[id].left = build(l, mid);
    tree[id].right = build(mid + 1, r);
    return id;
}

// Cập nhật giá trị vào phiên bản mới
int update(int prev_id, int l, int r, int val) {
    int id = ++node_cnt;
    tree[id] = tree[prev_id];
    tree[id].count++;

    if (l == r) return id;

    int mid = l + (r - l) / 2;
    if (val <= mid) {
        tree[id].left = update(tree[prev_id].left, l, mid, val);
    } else {
        tree[id].right = update(tree[prev_id].right, mid + 1, r, val);
    }
    return id;
}

// Truy vấn số nhỏ thứ k trong đoạn [L, R]
int query(int left_id, int right_id, int l, int r, int k) {
    if (l == r) return l;

    // Số lượng phần tử nằm ở nhánh trái trong đoạn [L, R]
    int count_left = tree[tree[right_id].left].count - tree[tree[left_id].left].count;
    int mid = l + (r - l) / 2;

    if (count_left >= k) {
        return query(tree[left_id].left, tree[right_id].left, l, mid, k);
    } else {
        return query(tree[left_id].right, tree[right_id].right, mid + 1, r, k - count_left);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        vals.push_back(a[i]);
    }

    // Rời rạc hóa
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    // Cây phiên bản 0
    root[0] = build(1, vals.size());

    // Xây dựng các phiên bản cây tương ứng với từng tiền tố
    for (int i = 1; i <= n; ++i) {
        int pos = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
        root[i] = update(root[i - 1], 1, vals.size(), pos);
    }

    // Xử lý truy vấn
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int pos = query(root[l - 1], root[r], 1, vals.size(), k);
        cout << vals[pos - 1] << '\n';
    }

    return 0;
}
