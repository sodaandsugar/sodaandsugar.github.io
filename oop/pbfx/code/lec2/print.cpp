# include <iostream>

using namespace std;

void print(int i) {cout << "Integer" << endl;}
void print(long l) {cout << "Long" << endl;}
void print(float f) {cout << "Float" << endl;}
void print(double f) {cout << "Double" << endl;}
void print(int i, double f) {cout << "Integer & Double" << endl;}

int main(){
    print(1);
    return 0;
}