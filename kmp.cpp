#include <bits/stdc++.h>
using namespace std;

#define fasty ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl '\n'
#define forinc(x, a, b) for (int x = a; x <= b; x++)

string t, s;
vector<int> pi;
vector<vector<int>> f, nxt;
int n, m;

void precalc() {
    // KMP tiền xử lý pi[] bắt đầu từ index 1
    // pi[i] là độ dài tiền tố dài nhất cũng là hậu tố của t[1...i]
    forinc(i, 2, m) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j + 1])
            j = pi[j];
        if (t[i] == t[j + 1])
            j++;
        pi[i] = j;
    }

    // Xây dựng Automaton nxt[trạng thái hiện tại][ký tự tiếp theo]
    forinc(i, 0, m) {
        for (int c = 0; c < 26; c++) {
            if (i < m && t[i + 1] == 'a' + c)
                nxt[i][c] = i + 1;
            else if (i > 0)
                nxt[i][c] = nxt[pi[i]][c];
            else
                nxt[i][c] = 0;
        }
    }
}

int main() {
    fasty;

    if (!(cin >> s >> t)) return 0;

    n = s.size();
    m = t.size();

    // Chèn ký tự vào đầu để bắt đầu từ index 1
    s = " " + s;
    t = " " + t;

    if (m > n) {
        cout << 0;
        return 0;
    }

    pi.assign(m + 1, 0);
    nxt.assign(m + 1, vector<int>(26, 0));
    f.assign(n + 1, vector<int>(m + 1, -1e9)); // -1e9 đại diện cho trạng thái chưa đến được

    precalc();

    f[0][0] = 0;
    forinc(i, 0, n - 1) {
        forinc(j, 0, m) {
            if (f[i][j] < 0) continue;

            for (int c = 0; c < 26; c++) {
                // Kiểm tra ký tự tại s[i+1] vì i đang chạy từ 0 đến n-1
                if (s[i + 1] == '?' || s[i + 1] - 'a' == c) {
                    int nj = nxt[j][c];
                    // Nếu nj == m nghĩa là ta vừa khớp thêm một xâu t
                    f[i + 1][nj] = max(f[i + 1][nj], f[i][j] + (nj == m));
                }
            }
        }
    }

    int res = 0;
    forinc(j, 0, m) res = max(res, f[n][j]);
    cout << res;

    return 0;
}
