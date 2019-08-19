/*
 * Name: Mubasshir Karim
 * File: BusinessFunctions.hpp
 * WSU ID: G498M939
 * Assignment: 4
 * Description: We will simulate a very basic hotdog stand empire.
 */

#ifndef BUSINESSFUNCTIONS_HPP
#define BUSINESSFUNCTIONS_HPP

#include <vector>

#include "Money.hpp"
#include "HotdogStand.hpp"

namespace MyAwesomeBusiness
{
    void runSimulation(std::vector<HotdogStand> &franchises, int days);
    void printRundown(const std::vector<HotdogStand> &franchises);
}
#endif