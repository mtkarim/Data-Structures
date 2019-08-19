#ifndef TEST_INTERFACE_HPP
#define TEST_INTERFACE_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>
#include "tests.hpp"
#include "Money.hpp"
#include "HotdogStand.hpp"

void TEST_INSERTION(bool sign);
void TEST_EXTRACTION(bool dSign);

void runTests()
{
    using std::cout;
    using std::left;
    using std::setw;
    using std::endl;
    namespace MAB = MyAwesomeBusiness;

    char prev = cout.fill('.');
    cout << "Money Class Tests\n";
    cout << setw(40) << left << "Negative (+ -> -)" << (IS_EQUAL(-550, (-(MAB::Money(5.50)).getPennies()))) << endl;
    cout << setw(40) << left << "Negative (- -> +)" << (IS_EQUAL(550, (-(MAB::Money(-5.50)).getPennies()))) << endl;
    cout << setw(40) << left << "Equality (T)" << (EXPECT_TRUE((MAB::Money(6) == MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Equality (F)" << (EXPECT_FALSE((MAB::Money(6) == MAB::Money(2)))) << endl;
    cout << setw(40) << left << "Prefix++" << (IS_EQUAL(MAB::Money(6), ++(MAB::Money(5)))) << endl;
    cout << setw(40) << left << "Postfix++" << (IS_EQUAL(MAB::Money(5), (MAB::Money(5))++)) << endl;
    cout << setw(40) << left << "Prefix--" << (IS_EQUAL(MAB::Money(6), --(MAB::Money(7)))) << endl;
    cout << setw(40) << left << "Postfix--" << (IS_EQUAL(MAB::Money(6), (MAB::Money(6))--)) << endl;
    cout << setw(40) << left << "Addition" << (IS_EQUAL(MAB::Money(7), (MAB::Money(2.5) + MAB::Money(4, 50)))) << endl;
    cout << setw(40) << left << "Multiplication (Money x int)" << (IS_EQUAL(MAB::Money(11), (MAB::Money(2.75) * 4))) << endl;
    cout << setw(40) << left << "Multiplication (int x Money)" << (IS_EQUAL(MAB::Money(11), (4 * MAB::Money(2.75))))  << endl;
    cout << setw(40) << left << "Multiplication (Money x double)" << (IS_EQUAL(MAB::Money(2.75), (MAB::Money(11) * 0.25))) << endl;
    cout << setw(40) << left << "Multiplication (double x Money)" << (IS_EQUAL(MAB::Money(2.75), (0.25 * MAB::Money(11)))) << endl;
    cout << setw(40) << left << "Less Than (T)" << (EXPECT_TRUE((MAB::Money(1) < MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Less Than (F)" << (EXPECT_FALSE((MAB::Money(10) < MAB::Money(2)))) << endl;
    cout << setw(40) << left << "Less Than (F, ==)" << (EXPECT_FALSE((MAB::Money(2) < MAB::Money(2)))) << endl;
    cout << setw(40) << left << "Less Than or Equal (T)" << (EXPECT_TRUE((MAB::Money(6) <= MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Less Than or Equal (T, ==)" << (EXPECT_TRUE((MAB::Money(6) <= MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Less Than or Equal (F)" << (EXPECT_FALSE((MAB::Money(6) <= MAB::Money(2)))) << endl;
    cout << setw(40) << left << "Greater Than (T)" << (EXPECT_TRUE((MAB::Money(6) > MAB::Money(4)))) << endl;
    cout << setw(40) << left << "Greater Than (F)" << (EXPECT_FALSE((MAB::Money(2) > MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Greater Than (F, ==)" << (EXPECT_FALSE((MAB::Money(6) > MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Greater Than or Equal (T)" << (EXPECT_TRUE((MAB::Money(6) >= MAB::Money(5)))) << endl;
    cout << setw(40) << left << "Greater Than or Equal (T, ==)" << (EXPECT_TRUE((MAB::Money(6) >= MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Greater Than or Equal (F)" << (EXPECT_FALSE((MAB::Money(2) >= MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Inequality (T)" << (EXPECT_TRUE((MAB::Money(2) != MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Inequality (F)" << (EXPECT_FALSE((MAB::Money(6) != MAB::Money(6)))) << endl;
    cout << setw(40) << left << "Insertion (<<, +)"; (TEST_INSERTION(true)); std::cout << endl;
    cout << setw(40) << left << "Insertion (<<, -)"; (TEST_INSERTION(false)); std::cout << endl;
    cout << setw(40) << left << "Extraction (>>, $)"; (TEST_EXTRACTION(true)); std::cout << endl;
    cout << setw(40) << left << "Extraction (>>)"; (TEST_EXTRACTION(false)); std::cout << endl;

    cout.fill(prev);
}


void TEST_INSERTION(bool sign)
{
    namespace MAB = MyAwesomeBusiness;
    std::stringstream ss;
    std::string str;

    if (sign) {
        MAB::Money money(5, 75);
        ss << money;
        str = ss.str();
        std::cout << (IS_EQUAL(std::string("$5.75"), str));
    } else {
        MAB::Money money(-5, -75);
        ss << money;
        str = ss.str();
        std::cout << (IS_EQUAL(std::string("($5.75)"), str));
    }
    ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void TEST_EXTRACTION(bool dSign)
{
    namespace MAB = MyAwesomeBusiness;
    std::stringstream ss;
    std::string str;

    if (dSign)
        ss << "$5.75";
    else
        ss << "5.75";
    
    MAB::Money money;
    ss >> money;
    std::cout << (IS_EQUAL(575, money.getPennies()));
}

#endif
