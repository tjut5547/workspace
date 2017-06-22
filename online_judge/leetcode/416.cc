#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define MAX(a, b) (a > b ? a : b)

class solution{
public:
    solution()
    {
        scanf ("%d %d", &n, &v);
        value = (int *) malloc (n * sizeof(int));
        price = (int *) malloc (n * sizeof(int));
        memset (value, 0, sizeof (value));
        memset (price, 0, sizeof (price));

        for (int i = 0; i < n; ++i) scanf("%d", value + i);
        for (int i = 0; i < n; ++i) scanf("%d", price + i);

        sum = (int **) malloc (n * sizeof(int*));
        for (int i = 0; i < n; ++i) {
            sum[i] = (int *) malloc ((v + 1) * sizeof(int));
            memset (sum[i], 0, sizeof((v + 1) * sizeof(int)));
        }
    }

    void solve()
    {
        for (int i = 0; i <= v; ++i) {
            if (i >= price[0]) {
                sum[0][i] = value[0];
            }
        }

        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j < n; ++j) {
                if (i < price[j]) continue;
                sum[j][i] = MAX(sum[j - 1][i], sum[j - 1][i - price[j]] + value[j]);
            }
        }
        for (int j = 0; j < n; ++j){
            for (int i = 0; i <= v; ++i) {
                cout << sum[j][i] << "\t";
            }
            cout << endl;
        }
        cout << "sum[n - 1][v] = " << sum[n - 1][v] << endl;
    }

private:
    int *value, *price;
    int **sum;
    int n, v;
};

int main(int argc, char **argv)
{
    solution sol;
    sol.solve();
    return 0;
}