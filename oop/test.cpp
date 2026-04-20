#include <iostream>
using namespace std;

// 基类
class A {
public:
    A() {
        cout << "执行A的构造函数 -> 调用f()：";
        f();  // 构造函数中调用虚函数
        cout << endl;
    }
    virtual void f() {
        cout << "A::f()";
    }
};

// 派生类，继承A
class B : public A {
public:
    B() {
        cout << "执行B的构造函数 -> 调用f()：";
        f();  // 构造函数中调用虚函数
        cout << endl;
    }
    // 重写基类虚函数
    void f() override {
        cout << "B::f()";
    }
};

int main() {
    cout << "===== 创建派生类对象 B obj =====" << endl;
    B obj;  // 核心：创建B的对象
    return 0;
}