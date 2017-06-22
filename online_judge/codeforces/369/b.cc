#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 505;

long long Map[N][N];

void print(int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << Map[i][j] << " ";
		}
		cout << endl;
	}
}

long long solve()
{
	int n; cin >> n;
	if (n == 1) return 1;
	long long equal_sum = 0, fill_sum = 0, equal_flag = 1;
	long long sum = 0, flag = 1, hhhhhh = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf ("%I64d", Map[i] + j);
			sum += Map[i][j];

			if (Map[i][j] == 0) flag = 0;	
		}

		if (!flag) equal_flag = 0, flag = 1;

		if (equal_flag) {
			if (equal_sum) {
				if (sum != equal_sum)
					hhhhhh = 1;
			} else {
				equal_sum = sum;
			}
		} else {
			fill_sum = sum;
			equal_flag = 1;
		}
		sum = 0;
	}

	if (n == 1) return 1;
	if (hhhhhh) return -1;

	long long fill = equal_sum - fill_sum;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j){
			if (Map[i][j] == 0)
				Map[i][j] = fill;
		}
	}
	//print(n);

	long long diag = 0, sec_diag = 0;
	for (int i = 0; i < n; ++i){
		diag += Map[i][i];
		sec_diag += Map[i][n - i - 1];	
	}

	long long col_sum = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) col_sum += Map[j][i];

		if (col_sum != equal_sum) return -1;
		col_sum = 0;
	}

	if (diag == sec_diag && diag == equal_sum)
		return fill > 0 ? fill : -1;
	else return -1;
}

int main(int argc, char **argv)
{
	cout << solve() << endl;
	return 0;
} 