#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findDuplicate(const vector<int>& nums) {
        int len = nums.size();
        int cal[32]; memset (cal, 0, sizeof(cal));
        
        for (int i = 0; i < len; ++i) {
            int index = 0;
            while (index < 32){
                if (nums[i] & (1 << index)) {
                    cal[index++]++;
                }
            }
        }

        for (int i = 0; i < len; ++i) {
            cout << cal[i] << "\t";
        }
        cout << endl;
        return sum - len * (len + 1) / 2;
    }
};

int main(int argc, char **argv)
{
    return 0;
}