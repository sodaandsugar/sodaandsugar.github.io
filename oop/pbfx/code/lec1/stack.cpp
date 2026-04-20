#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

class Stack
{
   private:
    int data[MAX_SIZE];
    int top;

   public:
    // 构造函数
    Stack() : top(-1) {};

    // 判断栈是否为空
    bool isEmpty() const
    {
        return top == -1;
    }

    // 判断栈是否满
    bool isFull() const
    {
        return top == MAX_SIZE - 1;
    }

    // 入栈
    void push(int value)
    {
        if (isFull()) {
            cout << "Stack overflow!" << endl;
            return;  // 或者抛出异常
        }
        data[++top] = value;
    }

    // 出栈
    int pop()
    {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1;  // 或者抛出异常
        }
        return data[top--];
    }
};

int main()
{
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Popped value: " << s.pop() << endl;  // 输出30
    cout << "Popped value: " << s.pop() << endl;  // 输出20
    cout << "Popped value: " << s.pop() << endl;  // 输出10
    cout << "Popped value: " << s.pop() << endl;  // 输出-1，栈空

    return 0;
}