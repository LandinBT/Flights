#include "city.hpp"

City::City() {}

City::City(const City& c)
    : name(c.name), country(c.country), population(c.population) {}

City& City::operator=(const City& c) {
  name = c.name;
  country = c.country;
  population = c.population;

  return *this;
}

void City::setName(const std::string& n) { name = n; }

void City::setCountry(const std::string& c) { country = c; }

void City::setPopulation(const unsLong& p) { population = p; }

std::string City::getName() const { return name; }

std::string City::getCountry() const { return country; }

typename City::unsLong City::getPopulation() const { return population; }

std::string City::toString() const {
  return name + " | " + country + " | " + std::to_string(population);
}

bool City::operator==(const City& c) const {
  return toString() == c.toString();
}

bool City::operator!=(const City& c) const { return !(*this == c); }

bool City::operator<(const City& c) const { return toString() < c.toString(); }

bool City::operator<=(const City& c) const { return *this < c or *this == c; }

bool City::operator>(const City& c) const { return !(*this <= c); }

bool City::operator>=(const City& c) const { return !(*this < c); }

std::istream& operator>>(std::istream& is, City& c) {
  std::string str;

  std::getline(is, c.name, '|');
  std::getline(is, c.country, '|');
  std::getline(is, str, '*');
  c.population = stoi(str);

  return is;
}

std::ostream& operator<<(std::ostream& os, const City& c) {
  return os << c.name << '|' << c.country << '|' << c.population << '*';
}
