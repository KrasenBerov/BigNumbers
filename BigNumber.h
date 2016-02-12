#ifndef BIGNUMBER_H_
#define BIGNUMBER_H_
#include <iostream>
#include <string>
using namespace std;
class BigNumber {
private:
    string big_number;
    int whichSystem;
private:
    //  FIXING FUNCTIONS
    void removeFrontZeroes();
    void addZerosInfront(int);
    void addSymbolInfront(string);
    void removeNegativeSign();
    void removeFirstSymbol();
    //  OTHER
    bool isPossitive();
    int length(); // SIZE OF THE NUMBER
    bool isDecimal();
    //  TRANSFORMATIONS
    string intToString(int);
    int charToInt(char);
    void oppositeBigNumber();
    void decimalToHexidecimal();
    void hexidecimalToDecimal();
    // ARITHMETICS
    BigNumber addPositiveBigNumber(BigNumber);
    BigNumber subsractPositiveBigNumber(BigNumber);
    BigNumber multiplyByPositiveBigNumber(BigNumber);
    BigNumber divideByPositiveBigNumber(BigNumber);
    void multByTen(int);
    BigNumber BNpow(int);
public:
    // CONSTRUCTORS
    BigNumber(int);
    BigNumber();
    BigNumber(string);
    // OPERATORS
        // COMPARISSON
    bool operator==(BigNumber);
    bool operator!=(BigNumber);
    bool operator>=(BigNumber);
    bool operator<=(BigNumber);
    bool operator<(BigNumber);
    bool operator>(BigNumber);
        // ARITHMETICS
    BigNumber operator+(BigNumber);
    BigNumber operator-(BigNumber);
    BigNumber operator*(BigNumber);
    BigNumber operator/(BigNumber);
    BigNumber operator%(BigNumber);

    BigNumber operator+=(BigNumber);
    BigNumber operator-=(BigNumber);
    BigNumber operator*=(BigNumber);
    BigNumber operator/=(BigNumber);
    BigNumber operator%=(BigNumber);
        // INPUT / OUTPUT
    friend ostream & operator<<(ostream & ,const BigNumber &);
    friend istream & operator>>(istream & , BigNumber &);
        // []
    int operator[](int);
};
#endif // BIGNUMBER_H_
