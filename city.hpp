#ifndef CITY_HPP_INCLUDED
#define CITY_HPP_INCLUDED

#include <iostream>
#include <string>

class City {
  std::string name;
  std::string country;
  int population;

 public:
  City();
  City(const City&);

  City& operator=(const City&);

  void setName(const std::string&);
  void setCountry(const std::string&);
  void setPopulation(const int&);

  std::string getName() const;
  std::string getCountry() const;
  int getPopulation() const;

  std::string toString() const;

  bool operator==(const City&) const;
  bool operator!=(const City&) const;
  bool operator<(const City&) const;
  bool operator<=(const City&) const;
  bool operator>(const City&) const;
  bool operator>=(const City&) const;

  friend std::istream& operator>>(std::istream&, City&);
  friend std::ostream& operator<<(std::ostream&, const City&);
};

#endif  // CITY_HPP_INCLUDED
