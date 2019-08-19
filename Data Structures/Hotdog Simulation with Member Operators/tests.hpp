#ifndef UGLYTESTING_HPP
#define UGLYTESTING_HPP

#include <sstream>
#include <string>

template <typename T>
bool IS_EQUAL(T val, T testVal)
{
    return val == testVal;
}

bool EXPECT_TRUE(bool test)
{
    return test == true;
}

bool EXPECT_FALSE(bool test)
{
    return test == false;
}

#endif