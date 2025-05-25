#include <iostream>
#include <vector>
#include <string>

class BigInt
{
private:
    std::vector<int> digits;
    bool isNegative;

    void trimLeadingZeros();
    BigInt subtract(const BigInt &other) const;

public:
    BigInt();
    BigInt(const std::string &num);

    void print() const;

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator/(const BigInt &other) const;

    bool operator==(const BigInt &other) const;

    BigInt absValue() const;
    int compareMagnitude(const BigInt &other) const;
};
