CXX = g++
CXXFLAGS = -Wall -std=c++14
SRC = main.o Money.o HotdogStand.o BusinessFunctions.o
EXE = hw04

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ main.cpp

Money.o: Money.cpp Money.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ Money.cpp

HotdogStand.o: HotdogStand.cpp HotdogStand.hpp	
	$(CXX) $(CXXFLAGS) -c -o $@ HotdogStand.cpp

BusinessFunctions.o: BusinessFunctions.cpp BusinessFunctions.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ BusinessFunctions.cpp

.PHONY: clean
clean:
	rm -f *.o $(EXE)