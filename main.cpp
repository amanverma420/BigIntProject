#include <iostream>
#include "BigInt.h"

int main() {
    BigInt a("123456789123456789");
    BigInt b("987654321987654321");

    std::cout << "Addition: ";
    (a + b).print();

    std::cout << "Subtraction: ";
    (b - a).print();

    std::cout << "Multiplication: ";
    (a * BigInt("2")).print();

    std::cout << "Division: ";
    (b / BigInt("12345")).print();

    std::cout << "Division by large number (should be 0): ";
    (a / BigInt("999999999999999999999")).print();

    return 0;
}
