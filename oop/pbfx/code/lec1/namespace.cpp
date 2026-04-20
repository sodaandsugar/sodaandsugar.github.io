#include <iostream>
using namespace std;

int value = 10;

namespace ThirdParty {
int value = 20;
}

int main()
{
    cout << ThirdParty::value << endl;
    cout << value << endl;
}