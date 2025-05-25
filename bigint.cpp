#include "bigint.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Constructor: default
BigInt::BigInt() {
    digits.push_back(0);
    isNegative = false;
}

// Constructor: from string
BigInt::BigInt(const string &num) {
    isNegative = false;
    digits.clear();

    int start = 0;
    if (num[0] == '-') {
        isNegative = true;
        start = 1;
    }

    while (start < num.size() && num[start] == '0') {
        start++;
    }

    if (start == num.size()) {
        digits.push_back(0);
        isNegative = false;
        return;
    }

    for (int i = num.length() - 1; i >= start; i--) {
        digits.push_back(num[i] - '0');
    }
}

// Removing leading zeros
void BigInt::trimLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

// Print the number
void BigInt::print() const {
    if (isNegative && !(digits.size() == 1 && digits[0] == 0)) {
        cout << "-";
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        cout << digits[i];
    }
    cout << "\n";
}

// Compare magnitudes
int BigInt::compareMagnitude(const BigInt &other) const {
    if (digits.size() > other.digits.size()) return 1;
    if (digits.size() < other.digits.size()) return -1;
    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] > other.digits[i]) return 1;
        if (digits[i] < other.digits[i]) return -1;
    }
    return 0;
}

// Absolute value
BigInt BigInt::absValue() const {
    BigInt temp = *this;
    temp.isNegative = false;
    return temp;
}

// Subtract helper
BigInt BigInt::subtract(const BigInt &other) const {
    BigInt result;
    result.digits.clear();
    int borrow = 0;
    for (int i = 0; i < digits.size(); i++) {
        int d1 = digits[i] - borrow;
        int d2 = i < other.digits.size() ? other.digits[i] : 0;
        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(d1 - d2);
    }
    result.trimLeadingZeros();
    return result;
}

// Addition
BigInt BigInt::operator+(const BigInt &other) const {
    if (isNegative == other.isNegative) {
        BigInt result;
        result.isNegative = isNegative;
        int carry = 0;
        int maxLen = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
        for (int i = 0; i < maxLen || carry; i++) {
            int d1 = i < digits.size() ? digits[i] : 0;
            int d2 = i < other.digits.size() ? other.digits[i] : 0;
            int sum = d1 + d2 + carry;
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        return result;
    } else {
        if (isNegative) {
            return other - absValue();
        } else {
            return *this - other.absValue();
        }
    }
}

// Subtraction
BigInt BigInt::operator-(const BigInt &other) const {
    if (!isNegative && !other.isNegative) {
        if (compareMagnitude(other) >= 0) {
            return subtract(other);
        } else {
            BigInt result = other.subtract(*this);
            result.isNegative = true;
            return result;
        }
    } else if (isNegative && other.isNegative) {
        return other.absValue() - absValue();
    } else if (isNegative && !other.isNegative) {
        BigInt result = absValue() + other;
        result.isNegative = true;
        return result;
    } else {
        return *this + other.absValue();
    }
}

// Multiplication
BigInt BigInt::operator*(const BigInt &other) const {
    BigInt result;
    int n = digits.size();
    int m = other.digits.size();
    result.digits = vector<int>(n + m, 0);
    result.isNegative = (isNegative != other.isNegative);

    for (int i = 0; i < n; i++) {
        int carry = 0;
        for (int j = 0; j < m || carry; j++) {
            int d2 = (j < m) ? other.digits[j] : 0;
            int sum = result.digits[i + j] + digits[i] * d2 + carry;
            result.digits[i + j] = sum % 10;
            carry = sum / 10;
        }
    }

    result.trimLeadingZeros();
    return result;
}

// Division
BigInt BigInt::operator/(const BigInt &other) const {
    if (other == BigInt("0")) {
        cout << "Error: Division by zero.\n";
        return BigInt("0");
    }

    BigInt dividend = absValue();
    BigInt divisor = other.absValue();
    BigInt result;
    result.digits = vector<int>(dividend.digits.size(), 0);
    BigInt remainder;

    for (int i = dividend.digits.size() - 1; i >= 0; i--) {
        remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
        remainder.trimLeadingZeros();

        int count = 0;
        while (remainder.compareMagnitude(divisor) >= 0) {
            remainder = remainder.subtract(divisor);
            count++;
        }
        result.digits[i] = count;
    }

    result.trimLeadingZeros();
    result.isNegative = (isNegative != other.isNegative);
    return result;
}

// Equality function
bool BigInt::operator==(const BigInt &other) const {
    return isNegative == other.isNegative && digits == other.digits;
}
