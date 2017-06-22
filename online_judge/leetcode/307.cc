#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class NumArray {
public:
    NumArray(vector<int> &nums) {
        for (int i = 0; i <= nums.size(); ++i){
            count.push_back(0);
            num.push_back(0);
        }
        for (int i = 0; i < nums.size(); ++i) {
            update(i, nums[i]);
        }
        num = nums;
    }

    void update(int i, int val) {
        int index = i + 1;
        int length = count.size();
        while (index < length) {
            count[index] = count[index] - num[i] + val;
            index = index + (index & (-index));
        }
        num[i] = val;
    }

    int sumRange(int i, int j)
    {
        int index = j + 1;
        int ans = 0;
        while (index > 0) {
            ans += count[index];
            index = index - (index & (-index));
        }

        index = i;
        while (index > 0) {
            ans -= count[index];
            index = index - (index & (-index));
        }
        return ans;
    }

    void print_count()
    {
        for (int i = 0; i < count.size(); ++i) {
            cout << "count" << i << " = " << count[i] << "  ";
        }
        cout << endl;
    }
private:
    vector<int> count;
    vector<int> num;
};

int main()
{
#ifndef ONLINEJUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    vector<int> num;
    while (cin >> n) {
        int m;
        for (int i = 0; i < n; ++i) {
            cin >> m;
            num.push_back(m);
            cout << m << " ";
        }
        cout << endl;

        NumArray ans(num);

        ans.print_count();

        string cmd;
        while (cin >> cmd) {
            if (cmd == "sumRange") {
                int left, right;
                cin >> left >> right;
                cout << "sumRange" << "\t" << left << "\t" << right << endl;
                cout << "ans = " << ans.sumRange(left, right) << endl;
            } else {
                int i, val; cin >> i >> val;
                cout << "update" << "\t" << i << "\t" << val << endl;
                ans.update(i, val);
                ans.print_count();
            }
        }
    }
    return 0;
}