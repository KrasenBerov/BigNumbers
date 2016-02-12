#include <iostream>
#include <string>
#include <cmath>
#include "BigNumber.h"

using namespace std;
int main()
{
    BigNumber b1;
    BigNumber b2;
    cin >> b1;
    cin >> b2;
    cout << b1 << endl << b2 << endl;
    cout << "+ " << (b1 + b2) << endl;
    cout << "- " << (b1 - b2) << endl;
    cout << "* " << (b1 * b2) << endl;
    cout << "/ " << (b1 / b2) << endl;
    cout << "% " << (b1 % b2) << endl;
    BigNumber b3;
    BigNumber b4;
    cin >> b3;
    cin >> b4;
    cout << "== " << (b3 == b4) << endl;
    cout << ">= " << (b3 >= b4) << endl;
    cout << "<= " << (b3 <= b4) << endl;
    cout << "> " << (b3 > b4) << endl;
    cout << "< " << (b3 < b4) << endl;
    cout << "!= " << (b3 != b4) << endl;
    BigNumber b5;
    cin >> b5;
    cout << "which index do you want to see ?";
    int n;
    cin >> n;
    cout << b5[n];
    return 0;
}
