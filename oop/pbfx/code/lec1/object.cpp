#include <iostream>

using namespace std;

class Example
{
   private:
    char c = 'A';
    int i = 0x12345678;
    char d = 'B';
};

int main()
{
    Example e;
    cout << "Size of Example: " << sizeof(e) << " bytes" << endl;
    cout << "Hexadecimal representation:" << endl;
    char* p = (char*)&e;  // 将对象地址转换为 char*，以字节为单位访问
    for (int i = 0; i < (int)sizeof(e); i++) {
        // %02x 表示：十六进制输出，至少2位，不足补0
        printf("%02x", (p[i] & 0xFF));  // 使用 & 0xFF 确保输出为无符号值
    }
    printf("\n");
    return 0;
}