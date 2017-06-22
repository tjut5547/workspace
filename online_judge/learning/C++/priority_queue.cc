#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

//template <class T, class Container = vector<T>,
//class Compare = less<typename Container::value_type> > class priority_queue;

int main(int argc, char **argv)
{
	priority_queue<int> p;
	int n, num;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i) {
			cin >> num;
			p.push(num);
		}

		while (!p.empty()) {
			cout << p.top() << " ";
			p.pop();
		}
		cout << endl;
	}
	return 0;
}