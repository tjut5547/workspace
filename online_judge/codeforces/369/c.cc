#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 105;

int color[N][N];
int c[N];

void get_value(int a[], int n)
{
	int sum = 1;
	for (int i = 1; i < n; ++i){
		if (a[i] != a[i - 1])
			sum++;
	}
	return sum;
}

int main()
{
	int n, m, k;
	while (scanf ("%d %d %d", &n, &m, &k) != EOF) {
		for (int i = 0; i < n; ++i) scanf ("%d", a + i);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf ("%d", color[i] + j);
			}
		}

		for (int i = 0; i < n; ++i)
	}
	return 0;
}