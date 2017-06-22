#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define MIN(a, b) (a < b ? a : b)

const int N = 200005;

int c[N], l[N], r[N];

int dfs(const int m, int c[], int start)
{
    if (start == m + 1) return 0;

    for (int i = start; i <= m; ++i) {
        if (c[l[i]] != c[r[i]]) {
            int tmp = c[l[i]];
            c[l[i]] = c[r[i]];
            int one = dfs(m, c, i + 1) + 1;
            c[l[i]] = tmp;
            c[r[i]] = c[l[i]];
            int two = dfs(m, c, i + 1) + 1;
            return MIN(one, two);
        } else {
            return dfs(m, c, i + 1);
        }
    }
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
    }

    for (int i = 1; i <= m; ++i) {
        scanf ("%d %d", l + i, r + i);
    }

    int ans = dfs(n, c, 1);
    cout << ans << endl;

    

    // for (int i = 0; i < n; ++i) {
    //     ans[i] = count[i].error
    // }
    return 0;
}