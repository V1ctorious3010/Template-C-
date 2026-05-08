#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Sử dụng map để lưu trữ kết quả các đoạn con (memoization)
// Hoặc dùng mảng 2 chiều dp[301][301] để tối ưu tốc độ
long long dp[301][301];
const int MOD = 1000000;

bool is_pair(char a, char b) {
    if (a == 'A' && b == 'U') return true;
    if (a == 'U' && b == 'A') return true;
    if (a == 'C' && b == 'G') return true;
    if (a == 'G' && b == 'C') return true;
    return false;
}

long long count_matchings(int i, int j, const string& s) {
    // Trường hợp cơ sở: đoạn rỗng
    if (i > j) return 1;

    // Nếu đã tính toán rồi thì trả về luôn
    if (dp[i][j] != -1) return dp[i][j];

    long long res = 0;

    // Cố định s[i], tìm s[k] để ghép cặp
    // k bắt đầu từ i+1 và nhảy bước 2 để đảm bảo đoạn (i+1, k-1) có độ dài chẵn
    for (int k = i + 1; k <= j; k += 2) {
        if (is_pair(s[i], s[k])) {
            long long left = count_matchings(i + 1, k - 1, s);
            long long right = count_matchings(k + 1, j, s);
            res = (res + (left * right)) % MOD;
        }
    }

    return dp[i][j] = res;
}

int main() {
    string line, s = "";
    // Đọc dữ liệu (bỏ qua dòng tiêu đề FASTA >Rosalind_...)
    getline(cin, line);
    while (getline(cin, line)) {
        s += line;
    }

    int n = s.length();

    // Khởi tạo mảng dp với giá trị -1
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = -1;
        }
    }

    cout << count_matchings(0, n - 1, s) << endl;

    return 0;
}
