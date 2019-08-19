#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "HotdogStand.hpp"
#include "BusinessFunctions.hpp"
#include "test_interface.hpp"

int main()
{
	namespace MAB = MyAwesomeBusiness;
	
	std::vector<MAB::HotdogStand> franchises;

	int stands;
	int fancyStands;
	MAB::Money fancyPrice;
	int days;

	do {
		std::cout << "Welcome!\nHow many hotdog stands do you own? ";
		std::cin >> stands;
	} while(stands < 0);
	std::cout << "How many of these sell classy hotdogs? ";
	std::cin >> fancyStands;
	if (fancyStands <= stands && fancyStands > 0) {
		std::cout << "How much does a classy hotdog cost? ";
		std::cin >> fancyPrice;

		if (fancyPrice == MAB::Money()) {
			fancyStands = 0;
		}
	}
	do {
		std::cout << "How many days will you simulate? ";
		std::cin >> days;
	} while(days <= 0);

	// Create vector
	for (int i = 0; i < stands; i++) {
		if (i < stands - fancyStands) {
			franchises.emplace_back();
		} else {
			franchises.emplace_back(fancyPrice);
		}
	}

	MAB::runSimulation(franchises, days);
	std::cout << "\n\n";
	runTests();

	return 0;
}