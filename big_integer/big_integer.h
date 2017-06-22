#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

class big_integer : public std::string {
public:
    big_integer (string num) : big_number(num) {}
    big_integer () : big_number("0") {}
    // big_integer (const big_integer &num) {
    //     big_number = num.big_number;
    // }

    const std::string get_big_number() const { return big_number; }
    void set_big_number(string num) { big_number = num; }

    friend big_integer operator+ (const big_integer &num1, const big_integer &num2);
    friend big_integer operator+ (const long long &num1, const big_integer &num2);
    friend big_integer operator+ (const big_integer &num1, const long long &num2);

    friend big_integer operator- (const big_integer &num1, const big_integer &num2);
    friend big_integer operator- (const long long &num1, const big_integer &num2);
    friend big_integer operator- (const big_integer &num1, const long long &num2);

    friend big_integer operator* (const big_integer &num1, const big_integer &num2);
    friend big_integer operator* (const long long &num1, const big_integer &num2);
    friend big_integer operator* (const big_integer &num1, const long long &num2);

    friend big_integer operator/ (const big_integer &num1, const big_integer &num2);
    friend big_integer operator/ (const long long &num1, const big_integer &num2);
    friend big_integer operator/ (const big_integer &num1, const long long &num2);

    friend big_integer operator% (const big_integer &num1, const big_integer &num2);
    friend big_integer operator% (const long long &num1, const big_integer &num2);
    friend big_integer operator% (const big_integer &num1, const long long &num2);

    friend bool operator< (const big_integer &num1, const big_integer &num2);
    friend bool operator< (const long long &num1, const big_integer &num2);
    friend bool operator< (const big_integer &num1, const long long &num2);

    friend bool operator> (const big_integer &num1, const big_integer &num2);
    friend bool operator> (const long long &num1, const big_integer &num2);
    friend bool operator> (const big_integer &num1, const long long &num2);

    friend bool operator==(const big_integer &num1, const big_integer &num2);
    friend bool operator==(const big_integer &num1, const long long &num2);
    friend bool operator==(const long long &num1, const big_integer &num2);

    friend bool operator>=(const big_integer &num1, const big_integer &num2);
    friend bool operator>=(const long long &num1, const big_integer &num2);
    friend bool operator>=(const big_integer &num1, const long long &num2);

    friend bool operator<=(const big_integer &num1, const big_integer &num2);
    friend bool operator<=(const long long &num1, const big_integer &num2);
    friend bool operator<=(const big_integer &num1, const long long &num2);

    friend bool operator!=(const big_integer &num1, const big_integer &num2);
    friend bool operator!=(const long long &num1, const big_integer &num2);
    friend bool operator!=(const big_integer &num1, const long long &num2);

    friend ostream &operator<<(ostream &out, const big_integer &num){
        return (out << num.big_number);
    }

    friend istream &operator>>(istream &in, big_integer &num) {
        return (in >> num.big_number);
    }

    big_integer& operator= (const big_integer &num);
    big_integer& operator= (const long long &num);
    big_integer& operator= (const string &num);

    friend int partition(big_integer num[], int left, int right);
    friend void big_integer_sort (big_integer num[], int start, int end);
private:
    std::string big_number;
};