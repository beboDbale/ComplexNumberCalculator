// FCAI – Programming 1 – 2022 - Assignment 2
// Program Name: Complex Numbers Calculator.cpp
// Last Modification Date: 3/25/2022
// Author: Belal Ahmed Eid
// Purpose: This program takes two complex numbers from user and performs operations (+, -, *, /) on them

#include <iostream>
#include <string>
#include <regex> // regular expression --> library to match string with determined pattern

using namespace std;

// ----- Global Variables -----
float real1, real2, imaginary1, imaginary2;
float sum1, sum2;
float sub1, sub2;
float multiply1, multiply2;
float real_numerator, imaginary_numerator, denominator, quotient1, quotient2;
string operation, complex;

// ---------- Functions ----------
bool validateComplexNumber(string &str);

void parseFirstComplex(string &str, float &real, float &imaginary);

void parseSecondComplex(string &str, float &real, float &imaginary);

void extract_operation(string &str, string &sign);

void addition();

void subtraction();

void multiplication();

void division();



int main() {
    cout << "Please enter a valid complex number in format (x+yi) * (x-yi) (please, take care of spaces): \n";
    cout << "e.g: (-3-1i) - (6-0i):\n";
    getline(cin, complex);
    // clear the buffer before taking new line
    cin.clear();
    cin.sync();

    while (!validateComplexNumber(complex)) {
        cout << "Invalid operand or missing brackets. Try again." << endl;
        getline(cin, complex);
        cin.clear();
        cin.sync();
    }

    parseFirstComplex(complex, real1, imaginary1);
    parseSecondComplex(complex, real2, imaginary2);
    extract_operation(complex, operation);

    if (operation == "+")addition();
    else if (operation == "-")subtraction();
    else if (operation == "*")multiplication();
    else if (operation == "/")division();
}

// Function to validate input
bool validateComplexNumber(string &str) {
    // regex pattern to compare it with the input from user
    regex valid_complex(
            "[(][-+]?[0-9]*\\.?[0-9]+[-+][0-9]*\\.?[0-9]+[i][)][ \t\r\n\f][-+*/][ \t\r\n\f][(][-+]?[0-9]*\\.?[0-9]+[-+][0-9]*\\.?[0-9]+[i][)]");
    // matching input with fixed pattern
    return regex_match(str, valid_complex);
}

// function to extract first real number and first imaginary number
void parseFirstComplex(string &str, float &real, float &imaginary) {
    // find returns -1 if character isn't found
    int minusPosition = str.find('-');
    int plusPosition = str.find('+');
    int position_i = str.find('i');
    int signPosition = 0;
    bool found = false;

    // detect if there is a minus before first real number and remove it
    if (minusPosition == 1) {
        // remove minus sign '-' at position 1
        str.erase(str.begin() + 1);
        minusPosition = str.find('-');
        found = true;
    }

    // if there are both signs +/- in the whole input we determine the index of first one using min function
    if (minusPosition > 0 && plusPosition > 0) {
        signPosition = min(plusPosition, minusPosition);
    }
    // if there is just one sign of +/- we determine the index of first one using max function
    else if (minusPosition == -1 || plusPosition == -1) {
        signPosition = max(plusPosition, minusPosition);
    }

    // take real number between left bracket and sign
    real = stof(str.substr(1, signPosition));
    if (found) {
        // if it was negative number we return the negative sign that we removed before
        real = real * -1;
    }
    // take imaginary number between sign and i
    imaginary = stof(str.substr(signPosition, position_i));
}

// function to extract second real number and second imaginary number
void parseSecondComplex(string &str, float &real, float &imaginary) {

    int signPosition = 0;
    int plusPosition = str.rfind('+');
    int minusPosition = str.rfind('-');
    int position_i = str.rfind('i');
    int secondOpeningBracketPosition = str.rfind('(');

    // find the index of operator in second complex number
    signPosition = max(minusPosition, plusPosition);

    // take real number between second opening bracket and sign
    real = stof(str.substr(secondOpeningBracketPosition + 1, signPosition));
    // take imaginary number between sign and i
    imaginary = stof(str.substr(signPosition, position_i));
}

// function to extract the operator +, -, * or /
void extract_operation(string &str, string &sign) {
    int firstClosingBracket = str.find(')');
    sign = str.at(firstClosingBracket + 2);
}

// function to add numbers
void addition() {
    // real part
    sum1 = real1 + real2;
    // imaginary part
    sum2 = imaginary1 + imaginary2;
    if (sum1 == 0 && sum2 == 0) {
        cout << 0 << "\n";
    }
    else if (sum1 == 0) {
        cout << sum2 << "i" << "\n";
    }
    else if (sum2 == 0) {
        cout << " = " << sum1 << "\n";
    }
    else if (sum2 > 0) {
        cout << " = (" << sum1 << "+" << sum2 << "i" << ")" << "\n";
    }
    else {
        cout << " = (" << sum1 << sum2 << "i" << ")" << "\n";
    }
}

// function to subtract numbers
void subtraction() {
    // real part
    sub1 = real1 - real2;
    // imaginary part
    sub2 = imaginary1 - imaginary2;
    if (sub1 == 0 && sub2 == 0) {
        cout << 0 << "\n";
    }
    else if (sub1 == 0) {
        cout << sub2 << "i" << "\n";
    }
    else if (sub2 == 0) {
        cout << " = " << sub1 << "\n";
    }
    else if (sub2 > 0) {
        cout << " = (" << sub1 << "+" << sub2 << "i" << ")\n";
    }
    else {
        cout << " = (" << sub1 << sub2 << "i" << ")\n";
    }
}

// function to multiply numbers
void multiplication() {
    // real part (note: i*i = -1)
    multiply1 = (real1 * real2) + (imaginary1 * imaginary2 * -1);
    // imaginary part
    multiply2 = (real1 * imaginary2) + (real2 * imaginary1);
    if (multiply1 == 0 && multiply2 == 0) {
        cout << 0 << "\n";
    }
    else if (multiply1 == 0) {
        cout << multiply2 << "i\n";
    }
    else if (multiply2 == 0) {
        cout << " = " << multiply1 << "\n";
    }
    else if (multiply2 > 0) {
        cout << "= (" << multiply1 << "+" << multiply2 << "i" << ")\n";
    }
    else {
        cout << "= (" << multiply1 << multiply2 << "i" << ")\n";
    }
}

// function to divide numbers
void division() {
    // we multiply the whole number [(x+yi)/(n-mi)] to complex conjugate [(n+mi)/(n+mi)]
    real_numerator = real1 * real2 + imaginary1 * imaginary2;
    imaginary_numerator = real1 * -1 * imaginary2 + real2 * imaginary1;

    denominator = real2 * real2 + imaginary2 * imaginary2;

    quotient1 = real_numerator / denominator;
    quotient2 = imaginary_numerator / denominator;
    if (quotient2 > 0) {
        cout << "(" << quotient1 << "+" << quotient2 << "i)" << endl;
    }
    else if (quotient2 < 0) {
        cout << "(" << quotient1 << quotient2 << "i)" << endl;
    }
    else { cout << quotient1; }
}