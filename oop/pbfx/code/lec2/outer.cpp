#include <iostream>

using namespace std;

class Outer{
    public:
        Outer(int x): x(x){}
        struct Inner{
            void display(Outer& outer){cout << outer.x << endl;}
        };
        Inner inner;
    private:
        int x;
};

int main(){
    Outer outer(10);
    outer.inner.display(outer);
    return 0;
}