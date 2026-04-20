#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    for (int i = 0; i < (int)nums.size(); i++) {
        cout << i << " ";
    }
    cout << endl;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    for (auto num : nums) {
        cout << num << " ";
    }
    return 0;
}