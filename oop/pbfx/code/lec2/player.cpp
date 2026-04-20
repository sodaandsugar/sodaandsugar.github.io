#include <iostream>

using namespace std;

class Player {
public:
    Player()=default; // 提示编译器生成默认构造函数
    Player(int score):score(score){
        cout << "Constructor" << endl;
    }
    int score;
};

int main(){
    Player p;
    cout << p.score << endl;
    return 0;
}