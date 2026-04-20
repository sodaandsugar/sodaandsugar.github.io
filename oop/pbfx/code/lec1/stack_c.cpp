#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 定义结构体
typedef struct
{
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack* s)
{
    s->top = -1;
}

// 判断栈是否为空
bool isEmpty(Stack* s)
{
    return s->top == -1;
}

// 判断栈是否满
bool isFull(Stack* s)
{
    return s->top == MAX_SIZE - 1;
}

// 入栈
void push(Stack* s, int value)
{
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->data[++s->top] = value;
}

// 出栈
int pop(Stack* s)
{
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;  // 返回-1表示栈空
    }
    return s->data[s->top--];
}

int main()
{
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Popped value: %d\n", pop(&s));  // 输出30
    printf("Popped value: %d\n", pop(&s));  // 输出20
    printf("Popped value: %d\n", pop(&s));  // 输出10
    printf("Popped value: %d\n", pop(&s));  // 输出-1，栈空

    return 0;
}