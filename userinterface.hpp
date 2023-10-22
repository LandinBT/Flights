#ifndef USERINTERFACE_HPP_INCLUDED
#define USERINTERFACE_HPP_INCLUDED

/// ClearScreen
#ifdef _WIN32
#define CLEAR "cls"  // Windows
#else
#define CLEAR "clear"  // Unix/Linnux
#endif

/// Libraries
#include <exception>
#include <iostream>
#include <string>

#include "city.hpp"
#include "graph.hpp"

using std::cout, std::cin, std::endl;

class UserInterface {
  Graph<City>* citiesPtr;

  void addCity();
  void addFlight();

  void deleteCity();
  void deleteFlight();

  void showFlightsList();
  void showFlightsMatrix();

  void deleteAll();

  void save();
  void load();

  void enterToContinue();
  // void loading();

 public:
  UserInterface();
  ~UserInterface();
};

#endif  // USERINTERFACE_HPP_INCLUDED
