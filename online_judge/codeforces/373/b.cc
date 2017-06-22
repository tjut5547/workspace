#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100005;

bool flag[N];

int main(int argc, char **argv)
{
    int len; cin >> len;
    string a; cin >> a;
    int even = 0, odd = 0;
    memset (flag, 0, sizeof(flag));
    for (int i = 0; i < len; ++i) {
        if (i % 2 == 0) {
            if (a[i] != 'r') {
                flag[i] = 1;
                even++;
            }
            else flag[i] = 0;
        } else {
            if (a[i] != 'b') {
                flag[i] = 1;
                odd++;
            }
            else flag[i] = 0;
        }
    }
    int ans_r = min(even, odd) + abs(even - odd);
    
    even = 0, odd = 0;
    memset (flag, 0, sizeof(flag));
    for (int i = 0; i < len; ++i) {
        if (i % 2 == 0) {
            if (a[i] != 'b'){
                flag[i] = 1;
                even++;
            }
            else flag[i] = 0;
        } else {
            if (a[i] != 'r') {
                flag[i] = 1;
                odd++;
            }
            else flag[i] = 0;
        }
    }
    int ans_b = min(even, odd) + abs(even - odd);
    //cout << ans_b << " " << ans_r << endl;
    cout << min(ans_b, ans_r) << endl;
    return 0;
}