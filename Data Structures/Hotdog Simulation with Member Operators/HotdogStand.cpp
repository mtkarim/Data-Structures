/*
 * Name: Mubasshir Karim
 * File: HotdogStand.cpp
 * WSU ID: G498M939
 * Assignment: 4
 * Description: We will simulate a very basic hotdog stand empire.
 */

#include <iostream>
#include <cmath>

#include "HotdogStand.hpp"

namespace MyAwesomeBusiness
{
int HotdogStand::totDogSold = 0;
int HotdogStand::numStands = 0;
Money HotdogStand::totRev = 0.00;
const int HotdogStand::hoursWorked = 8;
//HotdogStand Class Functions
HotdogStand::HotdogStand()
{
    dogPrice = 3.50;
    dailySold = 0;
    standSold = 0;
    hourlyWage = 7.25;
    dogSupply = 60;
    maxDogs = 60;
    wholeCost = 0.15;
    standMoney = dogPrice * 
    numStands++;
}
HotdogStand::HotdogStand(double val)
{
    dogPrice = val;
    dailySold = 0;
    standSold = 0;
    if (dogPrice > 3.50)
    {
        hourlyWage = 8.00;
        dogSupply = 30;
        wholeCost = 0.50;
    }
    else
    {
        hourlyWage = 7.25;
        dogSupply = 60;
        wholeCost = 0.15;
    }

    maxDogs = dogSupply;
    standMoney = -1;
    numStands++;
}
HotdogStand::HotdogStand(Money amount)
{
    dogPrice = amount;
    dailySold = 0;
    standSold = 0;

    if (dogPrice > 3.50)
    {
        hourlyWage = 8.00;
        dogSupply = 30;
        wholeCost = 0.50;
    }
    else
    {
        hourlyWage = 7.25;
        dogSupply = 60;
        wholeCost = 0.15;
    }

    maxDogs = dogSupply;
    standMoney = -1;
    numStands++;
}
const Money HotdogStand::getCash() const
{
    return standMoney;
}
const Money HotdogStand::getPrice() const
{
    return dogPrice;
}
int HotdogStand::getDailyDogsSold() const
{
    return dailySold;
}
void HotdogStand::replenishSupplies()
{
    dogSupply = dailySold;
    Money totStock = dogSupply * wholeCost;
    standMoney = standMoney - totStock;
}
void HotdogStand::payWorker()
{
    Money hourPay = hoursWorked * hourlyWage;
    standMoney = standMoney - hourPay;
}
void HotdogStand::dailyReset()
{
    dailySold = 0;
}
const Money HotdogStand::getStandRevenue() const
{
    double standRev = (dogPrice.getPennies() * dailySold);
    Money rev(standRev);
    return rev;
}
void HotdogStand::setPrice(double price)
{
    dogPrice = price;
}
void HotdogStand::sellHotdog()
{
    dailySold++;
    standSold++;
}
int HotdogStand::getNumStands()
{
    return numStands;
}
int HotdogStand::getTotalHotdogsSold()
{
    return totDogSold;
}
const Money HotdogStand::getTotalRevenue()
{
    return totRev;
}
}