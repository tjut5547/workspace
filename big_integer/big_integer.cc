#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// three '+'
big_integer operator+(const big_integer &num1, const big_integer &num2) {

    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);


    if (num1_sign == '-' && num2_sign == '+') {
        big_integer _num2, _num1 = big_integer(a.substr(1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer(b.substr(1, b.size() - 1));
        else _num2 = num2;
        return _num2 - _num1;
    } else if (num1_sign == '+' && num2_sign == '-') {
        big_integer _num1, _num2 = big_integer(b.substr(1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer(a.substr(1, a.size() - 1));
        else _num1 = num1;
        return _num1 - _num2;
    } else if (num1_sign == '-' && num2_sign == '-'){
        big_integer _num1 = big_integer (a.substr (1, a.size() - 1));
        big_integer _num2 = big_integer (b.substr (1, b.size() - 1));
        return big_integer('-' + (_num2 + _num1).big_number);
    } else {
        big_integer _num1, _num2;
        if (a[0] == '+') {
            _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') _num2 = big_integer(b.substr(1, b.size() - 1));
            else _num2 = num2;
            return _num2 + _num1;
        } else {
            _num1 = num1;
            if (b[0] == '+') {
                _num2 = big_integer(b.substr(1, b.size() - 1));
                return _num1 + _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    if (a.size() < b.size()) {
        string tmp = a;
        a = b;
        b = tmp;
    }

    int len1 = a.size();
    int len2 = b.size();
    int flag = 0, flag_high = 0;

    for (int i = len1 - 1, j = len2 - 1; i >= 0 && j >= 0; --i, --j) {
        int  tmp = a[i] - '0' + b[j] - '0';
        a[i] = (tmp % 10 + '0');
        flag = tmp >= 10 ? 1 : 0;
        for (int index = i - 1; index >= 0 && flag; --index) {
            tmp = a[index] + 1 - '0';
            a[index] = (tmp % 10 + '0');
            flag = tmp >= 10 ? 1 : 0;
        }
        if (flag) {
            flag_high = 1;
        }
    }
    if (flag_high) {
        if (ans_sign == '+') a = "1" + a;
        else {
            a = "1" + a;
            a = '-' + a;
        }
    } else {
        if (ans_sign == '-') a = '-' + a;
    }
    big_integer c(a);
    return c;
}

big_integer operator+(const long long &num1, const big_integer &num2) {
    char p[10000]; sprintf (p, "%lld", num1);
    string tmp(p);
    return big_integer(tmp) + num2;
}

big_integer operator+(const big_integer &num1, const long long &num2) {
    char p[10000]; sprintf (p, "%lld", num2);
    string  tmp(p);
    return big_integer(tmp) + num1;
}

//three '-'
big_integer operator-(const big_integer &num1, const big_integer &num2) {

    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);

    if (num1_sign == '-' && num2_sign == '+') {
        big_integer _num2, _num1 = big_integer(a.substr(1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer(b.substr(1, b.size() - 1));
        else _num2 = num2;
        return big_integer("-" + (_num1 + _num2).big_number);
    } else if (num1_sign == '+' && num2_sign == '-') {
        big_integer _num1, _num2 = big_integer(b.substr(1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer(a.substr(1, a.size() - 1));
        else _num1 = num1;
        return _num1 + _num2;
    } else if (num1_sign == '-' && num2_sign == '-'){
        big_integer _num1 = big_integer (a.substr (1, a.size() - 1));
        big_integer _num2 = big_integer (b.substr (1, b.size() - 1));
        return _num2 - _num1;
    } else {
        if (a[0] == '+') {
            big_integer _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') {
                big_integer _num2 = big_integer(b.substr(1, b.size() - 1));
                return _num1 - _num2;
            } else {
                return _num1 - num2; 
            }
        } else {
            if (b[0] == '+') {
                big_integer _num2 = big_integer (b.substr (1, b.size() - 1));
                return num1 - _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    bool _flag = 0;
    if (num1 == num2) return big_integer("0");
    if (num1 < num2) {
        string tmp = a;
        a = b;
        b = tmp;
        _flag = 1;
    }
    std::string::size_type len1 = a.size();
    std::string::size_type len2 = b.size();
    std::string::size_type i, j, index;

    for (i = len1, j = len2; i > 0 && j > 0; --i, --j) {
        if (a[i - 1] >= b[j - 1]) {
            a[i - 1] = a[i - 1] - b[j - 1] + '0';
        } else {
            int flag = 1;
            a[i - 1] = a[i - 1] - b[j - 1] + 10 + '0';
            for (index = i - 1; index > 0 && flag; --index) {
                int tmp = (a[index - 1] - '1' + 10) % 10;
                if (a[index - 1] == '0') {
                    a[index - 1] = tmp + '0';
                } else {
                    a[index - 1] = tmp + '0';
                    flag = 0;
                }
            }
        }
    }
    for (index = 0; index < a.size(); ++index) {
        if (a[index] != '0')
            break;
    }
    if (index == a.size()) index--;
    a = a.substr(index, a.size() - index);
    if (_flag) return '-' + a;
    return a;
}

big_integer operator-(const long long &num1, const big_integer &num2) {
    char p[10000]; sprintf (p, "%lld", num1);
    string tmp(p);
    return big_integer(tmp) - num2;
}

big_integer operator-(const big_integer &num1, const long long &num2) {
    char p[10000]; sprintf (p, "%lld", num2);
    string tmp(p);
    return num1 - big_integer(tmp);
}

// three '*'
big_integer operator*(const big_integer &num1, const big_integer &num2) {
    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);

    big_integer _num1, _num2;
    if (num1_sign == '-' && num2_sign == '-') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        _num2 = big_integer (b.substr (1, b.size() - 1));
        return _num1 * _num2;
    } else if (num1_sign == '-' && num2_sign == '+') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer (b.substr (1, b.size() - 1));
        else _num2 = num2;
        return big_integer('-' + (_num1 * _num2).big_number);
    } else if (num1_sign == '+' && num2_sign == '-') {
        _num2 = big_integer (b.substr (1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer (a.substr (1, a.size() - 1));
        else _num1 = num1;
        return big_integer('-' + (_num1 * _num2).big_number);
    } else {
        if (a[0] == '+') {
            _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
            } else {
                _num2 = num2;
            }
            return _num1 * _num2;
        } else {
            _num1 = num1;
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
                return _num1 * _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    if (a == "0" || b == "0") {
        return big_integer ("0");
    }

    if (num1 < num2) {
        string tmp = a;
        a = b;
        b = tmp;
    }

    int i, j, index, len1 = a.size(), len2 = b.size();
    string ans(len1 + len2 - 1, '0');
    vector<int> ans_int(len1 + len2 - 1, 0);
    for (i = len1 - 1; i >= 0; --i) {
        for (j = len2 - 1; j >= 0; --j) {
            ans_int[i + j] += (a[i] - '0') * (b[j] - '0');
            //cout << "i + j = " << i + j << "\tans_int[i + j] = " << ans_int[i + j] << endl;
        }
    }
    int flag = 0;
    for (int i = ans_int.size() - 1; i >= 0; --i) {
        int tmp = ans_int[i];
        ans_int[i] = (tmp + flag) % 10;
        flag = (tmp+ flag) / 10;
    }

    for (int i = 0; i < ans_int.size(); ++i) ans[i] += ans_int[i];
    if (flag > 0) {
        char first = flag + '0';
        return big_integer (first + ans);
    }
    del_pre_zero(ans);
    return big_integer(ans);
}

big_integer operator*(const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return num2 * big_integer(string(p));
}

big_integer operator*(const big_integer &num1, const long long &num2) {
    char p[10000];
    sprintf (p, "%lld", num2);
    return    num1 * big_integer(string(p));
}

//three '/'
big_integer operator/(const big_integer &num1, const big_integer &num2) {
    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);

    big_integer _num1, _num2;
    if (num1_sign == '-' && num2_sign == '-') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        _num2 = big_integer (b.substr (1, b.size() - 1));
        return _num1 / _num2;
    } else if (num1_sign == '-' && num2_sign == '+') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer (b.substr (1, b.size() - 1));
        else _num2 = num2;
        return big_integer('-' + (_num1 / _num2).big_number);
    } else if (num1_sign == '+' && num2_sign == '-') {
        _num2 = big_integer (b.substr (1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer (a.substr (1, a.size() - 1));
        else _num1 = num1;
        return big_integer('-' + (_num1 / _num2).big_number);
    } else {
        if (a[0] == '+') {
            _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
            } else {
                _num2 = num2;
            }
            return _num1 / _num2;
        } else {
            _num1 = num1;
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
                return _num1 / _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    if (a == "0" || b == "0") {
        printf("RUNTIME ERROR\n");
        return big_integer ("0");
    }

    big_integer ans("0"), answer("0");
    big_integer a_copy(a), b_copy(b);
    while (a_copy >= b_copy) {
        ans = 0;
        while (a_copy >= b_copy) {
            if (ans == 0) {
                ans = 1;
            } else {
                ans = ans + ans;
            }
            if (b_copy + b_copy > a_copy) break;
            b_copy = b_copy + b_copy;
        }
        a_copy = a_copy - b_copy;
        answer = answer + ans;
        b_copy = b;
    }
    return answer;
}

big_integer operator/(const big_integer &num1, const long long &num2) {
    char p[10000]; sprintf(p, "%lld", num2);
    string tmp(p);
    return num1 / big_integer(tmp);
}

big_integer operator/(const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf(p, "%lld", num1);
    return num2 * (big_integer(string(p)));
}

//three '%'
big_integer operator%(const big_integer &num1, const big_integer &num2) {
    big_integer num = num1 / num2;
    return num1 - (num * num2);
}

big_integer operator%(const big_integer &num1, const long long &num2) {
    char tmp[10000];
    sprintf (tmp, "%lld", num2);
    return  num1 % big_integer(string(tmp));
}

big_integer operator%(const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return big_integer(string(p)) % num2;
}

//three '>'
bool operator> (const big_integer &num1, const big_integer &num2) {
    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign = get_num_sign(a);
    char num2_sign = get_num_sign(b);

    if (num1_sign == '+' && num2_sign == '+') {
        if (a[0] == '+') {
            a = a.substr(1, a.size() - 1);
            if (b[0] == '+') {
                b = b.substr(1, b.size() - 1);
            }
            return big_integer(a) > big_integer(b);
        } else {
            if(b[0] == '+') {
                b = b.substr(1, b.size() - 1);
                return big_integer(a) > big_integer(b);
            }
        }
    } else if (num1_sign == '+' && num2_sign == '-') {
        if (num1 == num2) return false;
        else return true;
    } else if (num1_sign == '-' && num2_sign == '+') {
        return false;
    } else {
        a = a.substr(1, a.size() - 1);
        b = b.substr(1, b.size() - 1);
        a = del_pre_zero(a);
        b = del_pre_zero(b);
        if (a == b) return false;
        else return !(big_integer(a) > big_integer(b));
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);
    
    if (a.size() > b.size()) return true;
    else if (a.size() < b.size()) return false;
    else {
        for (int i = 0; i < a.size(); ++i) {
            if(a[i] > b[i]) return true;
            else if (a[i] < b[i]) return false;
        }
        return false;
    }
}

bool operator> (const big_integer &num1, const long long &num2) {
    char p[10000];
    sprintf (p, "%lld", num2);
    return num1 > (big_integer(string(p)));
}

bool operator> (const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return big_integer(string(p)) > num2;
}

// three '<'
bool operator< (const big_integer &num1, const big_integer &num2) {
    return !(num1 >= num2);
}

bool operator< (const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return big_integer(string(p)) <  num2;
}

bool operator< (const big_integer &num1, const long long &num2) {
    char p[10000];
    sprintf (p, "%lld", num2);
    return num1 < big_integer(string(p));
}

//three '=='
bool operator== (const big_integer &num1, const big_integer &num2) {
    if (num1.big_number == num2.big_number) {
        return true;
    }
    string a = num1.big_number;
    string b = num2.big_number;

    char num1_sign = get_num_sign(a);
    char num2_sign = get_num_sign(b);

    if(num1_sign == '+' && num2_sign == '-') {
        if (a[0] == '+') a = a.substr(1, a.size() - 1);
        b = b.substr(1, b.size() - 1);
        a = del_pre_zero(a);
        b = del_pre_zero(b);

        if (a == b && a == "0") return true;
        return false;
    } else if (num1_sign == '-' && num2_sign == '+') {
        if (b[0] == '+') b = b.substr(1, b.size() - 1);
        a = a.substr(1, a.size() - 1);
        a = del_pre_zero(a);
        b = del_pre_zero(b);
        if (a == b && a == "0") return true;
        return false;
    } else if (num1_sign == '+' && num2_sign == '+') {
        if (a[0] == '+') a = a.substr(1, a.size() - 1);
        if (b[0] == '+') b = b.substr(1, b.size() - 1);
        a = del_pre_zero(a);
        b = del_pre_zero(b);

        //cout << a << " " << b << endl;
        if (a == b) return true;
        return false;
    } else {
        a = a.substr(1, a.size() - 1);
        b = b.substr(1, b.size() - 1);
        a = del_pre_zero(a);
        b = del_pre_zero(b);
        //cout << a << " " << b << endl;
        if (a == b) return true;
        return false;
    }
}

bool operator== (const big_integer &num1, const long long &num2) {
    char p[10000], index;
    sprintf (p, "%lld", num2);
    return num1 == (big_integer(string(p)));
}

bool operator== (const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return big_integer(string(p)) == num2;
}

//three '!='
bool operator!= (const big_integer &num1, const big_integer &num2) {
    if (num1 == num2) return false;
    return true;
}

bool operator!= (const big_integer &num1, const long long &num2) {
    return !(num1 == num2);
}
 
bool operator!= (const long long &num1, const big_integer &num2) {
    return !(num1 == num2);
}

//three '>='
bool operator>= (const big_integer &num1, const big_integer &num2) {
    if (num1 == num2) return true;
    //cout << "fuck" << endl;
    if (num1 > num2) return true;
    return false;
}

bool operator>= (const big_integer &num1, const long long &num2) {
    return !(num1 < num2);
}

bool operator>= (const long long &num1, const big_integer &num2) {
    return !(num1 < num2);
}

//three '<='
bool operator<= (const big_integer &num1, const big_integer &num2) {
    if (num2 == num1 || num1 < num2) return true;
    return false;
}

bool operator<= (const long long &num1, const big_integer &num2) {
    return !(num1 > num2);
}

bool operator<= (const big_integer &num1, const long long &num2) {
    return !(num1 > num2);
}

// three '='
big_integer& big_integer::operator= (const big_integer &num) {
    if (this == &num) {
        return *this;
    }
    big_number = num.big_number;
    return *this;
}

big_integer& big_integer::operator= (const long long &num) {
    char p[10000];
    sprintf (p, "%lld", num);
    string tmp(p);
    big_number = tmp;
    return *this;
}

big_integer& big_integer::operator= (const string &num) {
    big_number = num;
    return *this;
}


int partition(big_integer num[], int left, int right) {
    big_integer tmp = num[left];
    while (left < right) {
        for ( ; right > left && num[right] >= tmp; right--);
        num[left] = num[right];
        for ( ; right > left && num[left] <= tmp; left++);
        num[right] = num[left];
    }
    num[left] = tmp;
    return left;
}

void big_integer_sort (big_integer num[], int start, int end) {
    if (start <= end) {
        int index = partition (num, start, end);
        big_integer_sort(num, start, (index - 1));
        big_integer_sort(num, (index + 1), end);
    }
}