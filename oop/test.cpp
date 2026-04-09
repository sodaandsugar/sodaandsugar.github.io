#include <iostream>
using namespace std;

struct Y {
    float f;
    int i;
    // 只有带参构造，无默认构造
    Y(int a) { i = a; f = 0; cout << "构造 Y(" << a << ")\n"; }
};

int main() {
    // ✅ 全初始化：每个元素都有构造参数，完美运行
    Y y1[] = { Y(1), Y(2) };
    return 0;
}