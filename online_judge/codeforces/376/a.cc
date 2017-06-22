#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define MIN(a, b) (a < b ? a : b)

int main()
{
    int ans = 0;
    string a; cin >> a;
    char current = 'a';
    for (int i = 0; i < a.size(); ++i) {
        ans += MIN((a[i] - current + 26) % 26, (current - a[i] + 26) % 26);
        current = a[i];
    }
    cout << ans << endl;
    return 0;
}
