#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100;

int num[N];

int main()
{
    int n; cin >> n;

    for (int i = 0; i < n; ++i) scanf("%d", num + i);

    if (n == 1) {
        if (num[0] == 0) {
            cout << "UP" << endl;
        } else if (num[0] == 15) {
            cout << "DOWN" << endl;
        } else {
            cout << "-1" << endl;
        }
    } else {
        if (num[n - 1] == 15) {
            cout << "DOWN" << endl;
        } else if (num[n - 1] == 0) {
            cout << "UP" << endl;
        } else if (num[n - 1] > num[n - 2]) {
            cout << "UP" << endl;
        } else {
            cout << "DOWN" << endl;
        }
    }
    return 0;
}