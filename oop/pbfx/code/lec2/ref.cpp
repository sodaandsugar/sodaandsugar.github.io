#include <iostream>

using namespace std;

int main(){
    int x = 100;
    auto& y = x;
    y = 200;
    cout << "x:" << x << " y:" << y << endl;
    return 0;
}