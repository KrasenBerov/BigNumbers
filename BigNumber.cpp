#include "BigNumber.h"
#include <algorithm>
using namespace std;
//CONSTRUCTOR
BigNumber::BigNumber()
{
    big_number = "";
    whichSystem = 10;
}
BigNumber::BigNumber(int n)
{
    if(n == 0)
        big_number = "0";
    else
        if( n > 0)
            while( n != 0)
            {
                addSymbolInfront(intToString(n%10));
                n /= 10;
            }
        else
        {
            n *= -1;
            while( n != 0)
            {
                addSymbolInfront(intToString(n%10));
                n /= 10;
            }
            addSymbolInfront("-");
        }
    whichSystem = 10;
}
BigNumber::BigNumber(string _string)
{
    big_number = _string;
    whichSystem = 10;
}
// FIXING FUNCTIONS
void BigNumber::removeFrontZeroes()
{
    while((*this)[0] == 0 && length() > 1)
        (*this).removeFirstSymbol();
}
void BigNumber::addZerosInfront(int n)
{
    for( int i = 0 ; i < n ; i ++)
        addSymbolInfront("0");
}
void BigNumber::addSymbolInfront(string c)
{
    big_number.insert(0 , c);
}
void BigNumber::removeFirstSymbol()
{
    big_number.erase(0 , 1);
}
void BigNumber::removeNegativeSign()
{
    while(!isPossitive())
        removeFirstSymbol();
}
// OTHER
bool BigNumber::isPossitive()
{
    if(big_number.at(0) == '-') return false;
    return true;
}
int BigNumber::length()
{
    if(!isPossitive())
        return big_number.length() - 1;
    return big_number.length();
}
bool BigNumber::isDecimal()
{
    if(length() > 1)
    {
        if(big_number.at(1) == 'x')
            return false;
        else
            return true;
    }
    return true;
}
// TRANSFORMATION
string BigNumber::intToString(int i)
{
    if(i == 0) return "0";
    if(i == 1) return "1";
    if(i == 2) return "2";
    if(i == 3) return "3";
    if(i == 4) return "4";
    if(i == 5) return "5";
    if(i == 6) return "6";
    if(i == 7) return "7";
    if(i == 8) return "8";
    if(i == 9) return "9";
    if(i == 10) return "A";
    if(i == 11) return "B";
    if(i == 12) return "C";
    if(i == 13) return "D";
    if(i == 14) return "E";
    if(i == 15) return "F";
    return "";
}
int BigNumber::charToInt(char c)
{
    if(c >= '0' && c <= '9')
        return (int)(c - '0');
    if(c == 'A') return 10;
    if(c == 'B') return 11;
    if(c == 'C') return 12;
    if(c == 'D') return 13;
    if(c == 'E') return 14;
    if(c == 'F') return 15;
}
void BigNumber::oppositeBigNumber()
{
    if(isPossitive())
        addSymbolInfront("-");
    else
        removeNegativeSign();
}
void BigNumber::decimalToHexidecimal()
{
    BigNumber tmp = (*this);
    string result;
    while((tmp) != (BigNumber(0)))
    {
        string tmp_result = (tmp % BigNumber(16)).big_number;
        if(tmp_result == "10") tmp_result = "A";
        if(tmp_result == "11") tmp_result = "B";
        if(tmp_result == "12") tmp_result = "C";
        if(tmp_result == "13") tmp_result = "D";
        if(tmp_result == "14") tmp_result = "E";
        if(tmp_result == "15") tmp_result = "F";
        result.append(tmp_result);
        tmp /= BigNumber(16);
    }
    reverse(result.begin() , result.end());
    big_number = "0x";
    big_number.append(result);
}
void BigNumber::hexidecimalToDecimal()
{
    BigNumber result(0);
    for (int i = 0 ; (length() - i - 1) > 1 ; i++)//WHILE BIGGER THAN 0x...
        result += (BigNumber(16).BNpow(i)) * BigNumber(charToInt(big_number.at(length() - i - 1)));
    (*this) = result;
    whichSystem = 16;
}
// ARITHMETICS
BigNumber BigNumber::addPositiveBigNumber(BigNumber b)
{
    BigNumber minBN;
    BigNumber maxBN;
    BigNumber result;
    if(*this > b)
    {
        minBN = b;
        maxBN = *this;
    }
    else
    {
        minBN = *this;
        maxBN = b;
    }
    minBN.addZerosInfront(maxBN.length() - minBN.length());
    /*
        1 + 1 = 2 : plusOne = 0;
        5 + 5 = 0 : plusOne = 1;
    */
    int plusOne = 0;
    int i = 0;
    while(i < maxBN.length())
    {
        int temp = plusOne + maxBN[maxBN.length() - 1 - i] + minBN[minBN.length() - 1 - i];
        if(temp > 9)
        {
            temp %= 10;
            plusOne = 1;
        }
        else
            plusOne = 0;
        result.addSymbolInfront(intToString(temp));
        i++;
    }
    if(plusOne == 1)
        result.addSymbolInfront("1");
    result.removeFrontZeroes();
    return result;
}
BigNumber BigNumber::subsractPositiveBigNumber(BigNumber b)
{
    BigNumber minBN;
    BigNumber maxBN;
    BigNumber result;
    bool isNegative;
    if(*this >= b)
    {
        minBN = b;
        maxBN = *this;
        isNegative = false;
    }
    else
    {
        minBN = *this;
        maxBN = b;
        isNegative = true;
    }
    minBN.addZerosInfront(maxBN.length() - minBN.length());
    int minusOne = 0; // SIMILAR TO PLUSONE
    int i = 0;
    while(i < maxBN.length())
    {
        int temp = 10 + maxBN[maxBN.length()- 1 - i] - minusOne - minBN[minBN.length()- 1 - i];
        if(temp > 9)
            minusOne = 0;
        else
            minusOne = 1;
        temp %= 10;
        result.addSymbolInfront(intToString(temp));
        i++;
    }
    result.removeFrontZeroes();
    if(isNegative)
        result.addSymbolInfront("-");
    return result;
}
BigNumber BigNumber::multiplyByPositiveBigNumber(BigNumber b)
{

    BigNumber result("0");
    BigNumber bn1 = *this;
    BigNumber bn2 = b;
    BigNumber temp;
    for ( int i = 0 ; i < bn1.length() ; i ++)
    {
        temp.big_number = "0";
        for (int j = 0 ; j < bn1[bn1.length() - i - 1] ; j ++)
            temp += bn2;
        temp.multByTen(i);
        result += temp;
    }
    return result;
}
BigNumber BigNumber::divideByPositiveBigNumber(BigNumber b)
{
    if(b[0] == 0) return NULL;
    BigNumber result;
    BigNumber currentDividend(0);
    int i = 0;  // THE POSITION OF THE CURRENT DIGIT OF THE DIVIDEND
    while(i < length())
    {
        while(currentDividend <= b)
        {
            if(i < length())
            {
                currentDividend.multByTen(1);
                result.multByTen(1);
                currentDividend += (BigNumber((*this)[i]));
            }
            else
            {
                result.removeFrontZeroes();
                return result;
            }
            i++;
        }
        int digit;
        for(digit = 0 ; digit < 10 ; digit ++)
            if((b * BigNumber(digit)) > currentDividend)
                break;
        digit--;
        result += BigNumber(intToString(digit));
        currentDividend = (currentDividend - (BigNumber(intToString(digit)) * b));
    }
    result.removeFrontZeroes();
    result.removeFrontZeroes();
    return result;
}
void BigNumber::multByTen(int i)
{
    for ( int k = 0 ; k < i ; k ++)
        big_number.append("0");
}
BigNumber BigNumber::BNpow(int n)
{
    BigNumber result(1);
    for (int i = 0 ; i < n ; i++)
        result *= (*this);
    return result;
}
//OPERATORS FOR COMPARISSON
bool BigNumber::operator==(BigNumber b)
{
    removeFrontZeroes();
    b.removeFrontZeroes();
    if((*this)[0] == 0 && !isPossitive())
        removeNegativeSign();
    if(b[0] == 0 && !b.isPossitive())
    {
        removeNegativeSign();
    }
    if(big_number == b.big_number) return true;
    return false;
}
bool BigNumber::operator!=(BigNumber b)
{
    if(*this == b) return false;
    return true;
}
bool BigNumber::operator>=(BigNumber b)
{
    if(*this == b || *this > b) return true;
    return false;
}
bool BigNumber::operator<=(BigNumber b)
{
    if(*this == b || *this < b) return true;
    return false;
}
bool BigNumber::operator>(BigNumber  b)
{
    removeFrontZeroes();
    b.removeFrontZeroes();
    if((*this)[0] == 0 && !isPossitive())
        removeNegativeSign();
    if(b[0] == 0 && !b.isPossitive())
        removeNegativeSign();
    if(*this == b ) return false;
    if(isPossitive() && !b.isPossitive()) return true;
    if(!isPossitive() && b.isPossitive()) return false;
    if(isPossitive() && b.isPossitive()) {
        if(length() > b.length()) return true;
        if(length() < b.length()) return false;
        if(big_number.length() == b.big_number.length()) {
            for ( int i = 0 ; i < length() ; i ++ ) {
                if((*this)[i] > b[i]) return true;
                if((*this)[i] < b[i]) return false;
            }
        }
    }
    // IT WONT REACH HERE , BUT I DONT LIKE THE WARNING
    return true;
}
bool BigNumber::operator<(BigNumber b)
{
    if(*this > b) return false;
    return true;
}
//OPERATORS FOR ARITHMETICS
BigNumber BigNumber::operator+(BigNumber b)
{
    if(isPossitive() && b.isPossitive())
        return addPositiveBigNumber(b);
    if(isPossitive() && !b.isPossitive())
    {
        b.oppositeBigNumber();
        return *this - b;
    }
    if(!isPossitive() && b.isPossitive())
    {
        oppositeBigNumber();
        return b - (*this);
    }
    if(!isPossitive() && !b.isPossitive())
    {
        oppositeBigNumber();
        b.oppositeBigNumber();
        BigNumber temp = ((*this) + b);
        temp.oppositeBigNumber();
        return temp;
    }
}
BigNumber BigNumber::operator-(BigNumber b)
{
    if(isPossitive() && b.isPossitive())
        return subsractPositiveBigNumber(b);
    if(isPossitive() && !b.isPossitive())
    {

        b.oppositeBigNumber();
        return *this + b;
    }
    if(!isPossitive() && b.isPossitive())
    {
        oppositeBigNumber();
        BigNumber temp = ((*this) + b);
        temp.oppositeBigNumber();
        return temp;
    }
    if(!isPossitive() && !b.isPossitive())
    {

        oppositeBigNumber();
        b.oppositeBigNumber();
        return b - (*this);
    }
}
BigNumber BigNumber::operator*(BigNumber b)
{
    if(isPossitive() && b.isPossitive())
        return multiplyByPositiveBigNumber(b);
    if((isPossitive() && !b.isPossitive()) || (!isPossitive() && b.isPossitive()))
    {
        removeNegativeSign();
        b.removeNegativeSign();
        BigNumber temp = ((*this) * b);
        temp.oppositeBigNumber();
        if(temp[0] == 0)
            temp.removeNegativeSign();
        return temp;
    }
    if(!isPossitive() && !b.isPossitive())
    {
        removeNegativeSign();
        b.removeNegativeSign();
        return (*this) * b;
    }
}
BigNumber BigNumber::operator/(BigNumber b)
{
    if(isPossitive() && b.isPossitive())
        return divideByPositiveBigNumber(b);
    if((isPossitive() && !b.isPossitive()) || (!isPossitive() && b.isPossitive()))
    {
        removeNegativeSign();
        b.removeNegativeSign();
        BigNumber temp = ((*this) / b);
        temp.oppositeBigNumber();
        if(temp[0] == 0)
            temp.removeNegativeSign();
        return temp;
    }
    if(!isPossitive() && !b.isPossitive())
    {
        removeNegativeSign();
        b.removeNegativeSign();
        return (*this) / b;
    }
}
BigNumber BigNumber::operator%(BigNumber b)
{
    BigNumber result = (*this - (b * (*this / b)));
    return result;
}
BigNumber BigNumber::operator+=(BigNumber b)
{
    return (*this) = ((*this) + b);
}
BigNumber BigNumber::operator-=(BigNumber b)
{
    return (*this) = ((*this) - b);
}
BigNumber BigNumber::operator*=(BigNumber b)
{
    return (*this) = ((*this) * b);
}
BigNumber BigNumber::operator/=(BigNumber b)
{
    return (*this) = ((*this) / b);
}
BigNumber BigNumber::operator%=(BigNumber b)
{
    return (*this) = ((*this) % b);
}

//OPERATORS FOR INPUT/OUTPUT
istream& operator>>(istream& in , BigNumber & b)
{
    in >> b.big_number;
    if(b.isDecimal())
        b.whichSystem = 10;
    else
        b.whichSystem = 16;
    if(b.whichSystem == 16)
        b.hexidecimalToDecimal();
    return in;
}
ostream& operator<<(ostream & out , const BigNumber & b)
{
    BigNumber tmp = b;
    if(b.whichSystem == 16)
        tmp.decimalToHexidecimal();
    out << tmp.big_number;
    return out;
}
//OPERATOR []
int BigNumber::operator[](int i)
{
    if(isPossitive())
        return charToInt(big_number.at(i));
    int k;
    for(k = 0 ; big_number.at(k) == '-' ; k++)
        {}
    return charToInt(big_number.at(i + k));
}

