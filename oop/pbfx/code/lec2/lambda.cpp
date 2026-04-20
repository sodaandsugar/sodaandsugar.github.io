#include <iostream>

using namespace std;

int main(){
    int x=1;
    auto f=[x](){cout << x << endl;};
    
    f();
    auto g=[&x]{x++;};
    g();
    cout << x << endl;
    return 0;
}