#ifndef USERINTERFACE_HPP_INCLUDED
#define USERINTERFACE_HPP_INCLUDED

///ClearScreen
#ifdef _WIN32
#define CLEAR "cls" // Windows
#else
#define CLEAR "clear"   // Unix/Linnux
#endif

///Libraries
#include <iostream>
#include <string>

#include "graph.hpp"
#include "city.hpp"

using std::cout, std::cin, std::endl;

class UserInterface {
    Graph<City> cities;

    void addCity();
    void addFlight();

    void deleteCity();
    void deleteFlight();

    void showFlightsList();
    void showFlightsMatrix();

    void save();
    void load();

    void enterToContinue();
    //void loading();

public:
    UserInterface();
};

#endif // USERINTERFACE_HPP_INCLUDED
