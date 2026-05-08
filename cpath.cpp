#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 200005; // Tối đa H + W

long long fact[MAX], invFact[MAX];

// Tính a^b % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Tính nghịch đảo modulo
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Tiền xử lý giai thừa và nghịch đảo giai thừa
void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[MAX - 1] = modInverse(fact[MAX - 1]);
    for (int i = MAX - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// Tính tổ hợp chập nCr % MOD
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// Số đường đi không xét vật cản từ (r1, c1) đến (r2, c2)
long long ways(int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) return 0;
    return nCr((r2 - r1) + (c2 - c1), r2 - r1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int H, W, N;
    if (!(cin >> H >> W >> N)) return 0;

    vector<pair<int, int>> obstacles(N);
    for (int i = 0; i < N; i++) {
        cin >> obstacles[i].first >> obstacles[i].second;
    }

    // Thêm đích đến như một vật cản cuối cùng
    obstacles.push_back({H, W});

    // Sắp xếp các vật cản theo hàng, sau đó theo cột
    sort(obstacles.begin(), obstacles.end());

    vector<long long> dp(N + 1);

    for (int i = 0; i <= N; i++) {
        // Số đường đi từ (1, 1) đến vật cản i
        dp[i] = ways(1, 1, obstacles[i].first, obstacles[i].second);

        // Trừ đi các đường đi đã chạm vật cản j trước khi đến i
        for (int j = 0; j < i; j++) {
            if (obstacles[j].second <= obstacles[i].second) {
                long long invalid = (dp[j] * ways(obstacles[j].first, obstacles[j].second, obstacles[i].first, obstacles[i].second)) % MOD;
                dp[i] = (dp[i] - invalid + MOD) % MOD;
            }
        }
    }

    // Kết quả là số đường đi hợp lệ đến vật cản N (chính là đích đến H, W)
    cout << dp[N] << "\n";

    return 0;
}
/*
 * Bài toán: Y - Grid 2 (AtCoder)
 * - Đếm số lượng đường đi hợp lệ từ ô (1, 1) đến ô (H, W) trên lưới.
 * - Chỉ được phép di chuyển sang phải hoặc xuống dưới.
 * - Không được đi qua N ô bị chặn (tọa độ r_i, c_i).
 * - Giới hạn: H, W <= 10^5; N <= 3000.
 * - Kết quả đầu ra lấy modulo 10^9 + 7.
 * - Phương pháp giải: Tổ hợp chập + Quy hoạch động O(N^2).
 */
