/*
 * Name: Mubasshir Karim
 * File: HotdogStand.hpp
 * WSU ID: G498M939
 * Assignment: 4
 * Description: We will simulate a very basic hotdog stand empire.
 */

#ifndef HOTDOGSTAND_HPP
#define HOTDOGSTAND_HPP

#include <iostream>
#include <random>

#include "Money.hpp"

namespace MyAwesomeBusiness
{
//HotdogStand Class
class HotdogStand
{
public:
    HotdogStand();
    HotdogStand(double val);
    HotdogStand(Money amount);
    const Money getCash() const;
    const Money getPrice() const;
    int getDailyDogsSold() const;
    void replenishSupplies();
    void payWorker();
    void dailyReset();
    const Money getStandRevenue() const;
    void setPrice(double price);
    void sellHotdog();
    static int getNumStands();
    static int getTotalHotdogsSold();
    static const Money getTotalRevenue();
private:
    Money standMoney; //A Money object that will represent how much money the stand has made
    Money dogPrice; //A Money object that will represent the price of a hotdog
    int dailySold;  //An integer that will describe how many hotdogs a stand has sold in a single day
    int standSold; //An integer that will describe how many cumulative hotdogs a stand has sold
    Money hourlyWage; //A money object representing the hourly wage of your stand employee
    static const int hoursWorked;   //A constant that represents how many hours your employee works in a day, initialized to 8
    int dogSupply;  //An integer that represents your hotdog supply
    int maxDogs;    //An integer that represents the maximum amount of hotdogs you are allowed to have
    Money wholeCost;    //A money object that represents the wholesale cost of a hotdog
    static int numStands; //A static integer that represents the total number of Hotdogstand objects
    static int totDogSold;  //A static integer that represents the total number of hotdogs sold
    static Money totRev;    //A static Money object that represents total revenue for all HotdogStand objects  
};
}
#endif