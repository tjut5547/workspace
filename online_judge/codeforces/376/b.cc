#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define MAX(a, b) (a > b ? a : b)

const int N = 200000;

int a[N];

int main()
{
    int n; cin >> n;
    for (int  i = 0; i < n; ++i) {
        scanf("%d", a + i);
        if (a[i] % 2 == 0 && a[i] != 0) {
            a[i] = 2;
        } else if (a[i] % 2 == 1){
            a[i] = 1;
        }
    }

    bool flag = 0;
    bool ans_flag = 1;
    for (int i = 0; i < n; ++i) {
        if (flag) {
            a[i]--;
            if (a[i] < 0) {
                ans_flag = 0;
                break;
            } else if (a[i] == 0) {
                flag = 0;
            } else {
                flag = 1;
            }
        } else {
            if (a[i] == 1) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
    }
    if (flag == 1) ans_flag = 0;

    if (ans_flag == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}