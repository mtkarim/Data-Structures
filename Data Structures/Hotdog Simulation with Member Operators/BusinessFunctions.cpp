/*
 * Name: Mubasshir Karim
 * File: BusinessFunctions.cpp
 * WSU ID: G498M939
 * Assignment: 4
 * Description: We will simulate a very basic hotdog stand empire.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>

#include "Money.hpp"
#include "HotdogStand.hpp"
#include "BusinessFunctions.hpp"

using std::cout;
using std::endl;
using std::setw;

int stands, ownstands;
int classydog = 0;
double classyprice;
namespace MyAwesomeBusiness
{
    void runSimulation(std::vector<HotdogStand> &franchises, int days)
    {
        std::random_device rd;  //random device
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> uni(20,60);  //regular hotdogs
        std::uniform_int_distribution<int> unid(1,30);  //classy hotdogs
        uni(generator);
        unid(generator);

    for (int i = 0; i < days; i++)
    {
        for (unsigned int j = 0; j < franchises.size(); j++)
        {
            franchises[j].sellHotdog();
            Money m;
            m = (franchises[j].getPrice());
            int u = m.getPennies();
            if (u <= 3.50)
            {
                for (int isales = uni(generator); isales != 0; isales--)
                {
                    franchises[j].setPrice(3.50);
                    franchises[j].sellHotdog();
                }
            }
            else
            {
                for (int isales = unid(generator); isales != 0; isales--)
                {
                    franchises[j].sellHotdog();
                }
            }

            franchises[i].dailyReset();
            printRundown(franchises);
            cout << endl;
        }
        Money n;
        for (unsigned int x = 0; x < franchises.size(); x++)
        {
            n = (franchises[x].getStandRevenue() + n);
        }

        int l;
        for (unsigned int y = 0; y < franchises.size(); y++)
        {
            l = (franchises[y].getDailyDogsSold() + l);
        }

        Money o;
        for (unsigned int z = 0; z < franchises.size(); z++)
        {
            o = (franchises[z].getCash() + o);
        }

        cout << "TOTALS" << setw(7) << i << setw(12) << n;
        cout << setw(12) << o << endl;
        cout << "# of Stands: " << franchises.size() << endl;
    }
    }
    void printRundown(const std::vector<HotdogStand> &franchises)
    {
        double sales = 0;
        Money price = 0.00;
        Money rev, m;
        //setting width for 'stand', 'sales', 'price', 'revenue'
        cout << endl << setw(5) << "Stand" << setw(8) << "Sales" << setw(8) << "Price" << setw(12) << "Revenue" << setw(17) << "Remaining Cash\n";
        cout << "=====" << setw(8) << "=====" << setw(8) << "=====" << setw(13) << "========" << setw(17) << "===============\n";

        for (unsigned int i = 0; i < franchises.size(); i++)    //loop for stands
        {
            sales = franchises[i].getDailyDogsSold();
            price = franchises[i].getPrice();
            m = (franchises[i].getCash());

            Money rev;
            rev = franchises[i].getStandRevenue();
            cout << setw(5) << i+1 << setw(8) << sales << setw(4) << price;
            cout << setw(8) << rev;
            cout << setw(10) << m << endl;
        }

    }
}
