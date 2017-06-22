#include <cstdio>
#include "big_integer.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    int n;
    big_integer num[100000];
    big_integer a, b;
    // while (cin >> a >> b) {
    //     if (a >= b) printf("%s\n", "a >= b");
    //     else printf("%s\n", "a < b");
    // }
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            num[i] = -i * i + 6 * i;
            cout << num[i] << "\t";
        }
        cout << endl;
        big_integer_sort(num, 0, n - 1);
        for (int i = 0; i < n; ++i) {
            cout << num[i] << "\t";
        }
        cout << endl;
    }
    return 0;
}