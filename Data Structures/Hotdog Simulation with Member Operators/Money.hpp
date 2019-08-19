/*
 * Name: Mubasshir Karim
 * File: money.hpp
 * WSU ID: G498M939
 * Assignment: 4
 * Description: We will simulate a very basic hotdog stand empire.
 */

#ifndef MONEY_HPP
#define MONEY_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <stdio.h>

using std::istream;
using std::ostream;

namespace MyAwesomeBusiness
{
//Money Class
class Money
{

public:
    Money();
    Money(int dol, int cen);
    Money(int dol);
    Money(double value);
    int getPennies() const;
    int getDollars() const;
    int getCents() const;
    bool isNegative() const;
    //--------------------------- Member Operators --------------------------------
    const Money operator -()const;
    Money& operator ++();
	const Money operator ++(int);
	Money& operator --();
    const Money operator --(int);
    //---------------------------- Friend Operators -------------------------------
    friend const Money operator +(const Money& amount1, const Money& amount2);
    friend const Money operator *(const Money& amount1, int amount2);
    friend const Money operator *(int amount1, const Money& amount2);
    friend const Money operator *(const Money& amount1, double amount2);
    friend const Money operator *(double amount1, const Money& amount2);
    friend bool operator <(const Money& amount1, const Money& amount2);
    friend bool operator <=(const Money& amount1, const Money& amount2);
    friend bool operator >(const Money& amount1, const Money& amount2);
    friend bool operator >=(const Money& amount1, const Money& amount2);
    friend bool operator ==(const Money& amount1, const Money& amount2);
    friend bool operator !=(const Money& amount1, const Money& amount2);
    friend std::ostream& operator << (std::ostream& outStream, const Money& amount);
    friend std::istream& operator >> (std::istream& inStream, Money& amount);
private:
    int dollars;
    int cents;
};
//------------------------ Non-Member/Non-Friend Operator ---------------------------
int operator -(const Money& amount1, const Money& amount2);
}
#endif