#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::cout << s;
    return 0;
}
#include <string>

std::string s1 = "Chuoi co \"ngoac kep\"";
std::string s2 = R"(Chuoi co "ngoac kep")";
#include <iostream>
#include <tuple>
#include <string>

int main() {
    // Khai báo và khởi tạo
    std::tuple<int, double, std::string> t = {1, 2.5, "test"};

    // Truy xuất bằng std::get (yêu cầu index là hằng số)
    int a = std::get<0>(t);

    // Sửa giá trị
    std::get<1>(t) = 3.14;

    // Truy xuất bằng C++17 Structured Binding
    auto [x, y, z] = t;
}
struct CustomCompare {
    bool operator()(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) const {
        // Ưu tiên so sánh phần tử thứ 2 (index 1) trước
        if (std::get<1>(a) != std::get<1>(b)) {
            return std::get<1>(a) < std::get<1>(b);
        }
        // Nếu bằng, so sánh phần tử thứ 1 (index 0)
        return std::get<0>(a) < std::get<0>(b);
    }
};
#include <queue>
#include <vector>
#include <tuple>

int main() {
    // 1. Max Heap mặc định (Phần tử lớn nhất ở đỉnh)
    std::priority_queue<std::tuple<int, int>> max_heap;
    max_heap.push({1, 5});
    max_heap.push({2, 3});
    // top() là {2, 3}

    // 2. Min Heap mặc định (Phần tử nhỏ nhất ở đỉnh)
    std::priority_queue<
        std::tuple<int, int>,
        std::vector<std::tuple<int, int>>,
        std::greater<std::tuple<int, int>>
    > min_heap;
    min_heap.push({1, 5});
    min_heap.push({2, 3});
    // top() là {1, 5}

    // 3. Heap với Custom Comparator
    // Lưu ý: Đối với priority_queue, Comparator trả về true tức là phần tử a đứng SAU phần tử b.
    std::priority_queue<
        std::tuple<int, int, int>,
        std::vector<std::tuple<int, int, int>>,
        CustomCompare
    > custom_heap;
}



#include <iostream>
#include <compare>

struct Point {
    int x;
    int y;
    int z;

    // Tự động sinh toán tử so sánh
    auto operator<=>(const Point&) const = default;
};

int main() {
    Point p1{1, 2, 3};
    Point p2{1, 2, 4};
    Point p3{1, 2, 3};

    std::cout << (p1 < p2) << '\n';  // 1 (true) do z: 3 < 4
    std::cout << (p1 == p3) << '\n'; // 1 (true)
    std::cout << (p2 >= p1) << '\n'; // 1 (true)

    return 0;
}

#include <compare>
#include <string>

struct Student {
    int id;
    std::string name;

    // Chỉ so sánh theo ID, bỏ qua name
    std::strong_ordering operator<=>(const Student& other) const {
        return id <=> other.id;
    }

    // Bắt buộc phải tự viết operator== khi không dùng = default
    bool operator==(const Student& other) const {
        return id == other.id;
    }
};
