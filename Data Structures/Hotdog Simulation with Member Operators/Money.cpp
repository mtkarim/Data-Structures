/*
 * Name: Mubasshir Karim
 * File: Money.cpp
 * WSU ID: G498M939
 * Assignment: 4
 * Description: We will simulate a very basic hotdog stand empire.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <stdio.h>

#include "Money.hpp"

using std::istream;
using std::ostream;
using std::cout;
using std::cin;

namespace MyAwesomeBusiness
{
//Money Constructors
 Money::Money()

     :dollars(0)
     ,cents(0)
{}
Money::Money(int dol, int cen)

	:dollars(dol)
	,cents(cen)
{}
Money::Money(int dol)

	:dollars(dol)
	,cents (0)
{}
Money::Money(double value)
{
	dollars = value;
	cents = (value * 100 - dollars *100);
}
//Money Class Functions
int Money::getPennies() const
{
	int pennies = (dollars * 100) +	cents;
    return pennies;
}
bool Money::isNegative() const
{
   if ((dollars < 0)|| (cents < 0))
    {
	   return true;
    }
	else
    {
		return false;
	}
}
//member functions
const Money Money::operator-()const
{
	Money negative(-dollars, -cents);
	return negative;
}
Money& Money::operator++()	//prefix(++)
{
	++dollars;
	return *this;
}
const Money Money::operator++(int)	//postfix(++)
{
	Money m = *this;
	++(*this);
	return m;
}
Money& Money::operator-- ()	//prefix(--)
{
	--dollars;
	return *this;
}
const Money Money::operator-- (int)	//postfix(++)
{
	Money m = *this;
	--(*this);
	return m;
}
//friend functions
const Money operator +(const Money& amount1, const Money& amount2)
{
	int dollarSum = amount1.dollars + amount2.dollars;
    int centSum = amount1.cents + amount2.cents;
    if (centSum >= 100)
    {
        dollarSum += 1;
        centSum -= 100;
    }
    if (centSum <= -100)
    {
        dollarSum -= 1;
        centSum += 100;
    }
    Money sum(dollarSum, centSum);
    return sum;
}
const Money operator *(const Money& amount1, double amount2)
{
	double productDol = amount1.dollars * amount2;
	double productCen = amount1.cents * amount2;
	double totCents = productCen + 100 * productDol;
	double totDollars = totCents/100;

	int dolProd = std::floor (totDollars);
	double dolla = totDollars - dolProd;
	int cenProd = std::round(dolla * 100);

	Money result(dolProd, cenProd);
	return result;
}
const Money operator *(const double amount1, const Money& amount2)
{
	return amount2*amount1;
}
const Money operator *(const Money& amount1, int amount2)
{
	return amount1*static_cast<double> (amount2);
}
const Money operator *(int amount1, const Money& amount2)
{
	return amount2 * amount1;
}
bool operator <(const Money& amount1, const Money& amount2)
{
	return (amount1.getPennies() < amount2.getPennies());
}
bool operator <=(const Money& amount1, const Money& amount2)
{
	return ((amount1.dollars <= amount2.dollars) && (amount1.cents <= amount2.cents));
}
bool operator >(const Money& amount1, const Money& amount2)
{
	return ((amount1.getPennies()) > (amount2.getPennies()));
}
bool operator >=(const Money& amount1, const Money& amount2)
{
	return ((amount1.dollars >= amount2.dollars) && (amount1.cents >= amount2.cents));
}
bool operator ==(const Money& amount1, const Money& amount2)
{
	return ((amount1.dollars == amount2.dollars) && (amount1.cents == amount2.cents));
}
bool operator !=(const Money& amount1, const Money& amount2)
{
	return (amount1.getPennies() != amount2.getPennies());
}
//Non-Member/Non-Friend functions
int operator -(const Money& amount1, const Money& amount2)
{
	return (amount1.getPennies()-amount2.getPennies());
}
std::ostream& operator << (std::ostream& outStream, const Money& amount)
{
	int dollAbs = abs(amount.dollars);
    int cenAbs = abs(amount.cents);

    if ((amount.cents < 10 && amount.cents >= 0) || (amount.cents > -10 && amount.cents <= 0))
    {
        outStream << "($)" << dollAbs;
    }
    else
    {
        outStream << "$" << dollAbs;
    }
    if (cenAbs >= 10)
    {
        outStream << "." << cenAbs;
    }
    else
    {
        outStream << "." << "0" << cenAbs << ")";
    }
    return outStream;
}
std::istream& operator >> (std::istream& inStream, Money& amount)
{
    std::string input;
    inStream >> input;
    double val;

    if (input[0] == '$')
    {
        input = input.erase(0,1);
        val = std::stod(input);
    }
    else
    {
        val = std::stod(input);
    }
    amount = val;
    return inStream;
}
}