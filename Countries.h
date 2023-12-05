#ifndef COUNTRIES_H
#define COUNTRIES_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct Country {
	string name;
	double happiness = 0;
	int ranking = 0;
};

class CountryList
{
public:


	CountryList(string filepath);
	Country searchCountries(string countryName);
	void displayList();

private:
	Country noMatch;
	vector<Country> countryHappinessList;

};
#endif
