#include <iostream>

using namespace std;

void printSum(int a, int b=10){
    cout << a+b << endl;
}

int main(){
    printSum(5); // 输出15
    printSum(5, 5); // 输出10
    return 0;
}