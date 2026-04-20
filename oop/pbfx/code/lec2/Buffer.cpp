#include <iostream>

using namespace std;

class Buffer {
public:
    Buffer(int size=0):size(size) {
        data=new int[size];
    }

    Buffer(const Buffer& other):size(other.size) {
        data=new int[size];
        for(int i=0;i<size;i++){
            data[i]=other.data[i];
        }
    }
    
    ~Buffer() {
        delete[] data;  // 析构函数：释放资源
        cout << "Deconstructor" << endl;
    }

    int* data;
    int size;
};

int main(){
    Buffer m1;
    Buffer m2 = m1;
    return 0;
}