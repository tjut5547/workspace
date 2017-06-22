#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

char get_num_sign (string a) {
    if (a[0] == '-') {
        return '-';
    } else {
        return '+';
    }
}

std::string del_pre_zero (const string &a) {
    int i;
    for (i = 0; i < a.size(); ++i) {
        if (a[i] != '0')
            break;
    }
    if (i == a.size()) i--;
    return a.substr(i, a.size() - i);
}
