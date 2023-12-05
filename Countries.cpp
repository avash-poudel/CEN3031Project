#include "Countries.h"


CountryList::CountryList(string filepath)
{
	noMatch.name = "This country was not found";
	noMatch.happiness = 0.0;
	noMatch.ranking = 0;

	ifstream csv(filepath);
	if (!csv.is_open())
	{
		throw new runtime_error("Could not open CSV file stated");

	}
	else
	{

		string line;
		getline(csv, line);
		while (getline(csv, line))
		{
			Country newCountry;
			istringstream stream(line);


			getline(stream, newCountry.name, ',');
			//Name of country in lower case

			string happiness_str;
			getline(stream, happiness_str, ',');
			newCountry.happiness = stod(happiness_str);
			//Turns happiness string into int input for country

			string ranking_str;
			getline(stream, ranking_str, ',');
			newCountry.ranking = stoi(ranking_str);


			countryHappinessList.push_back(newCountry);



		}
		csv.close();
	}
}

Country CountryList::searchCountries(string countryName)
{
	for (Country curr_country : countryHappinessList)
	{
		string lowercurrCountry = "";
		string lowersearchCountry = "";
		for (char letter : curr_country.name)
		{
			lowercurrCountry.push_back(tolower(letter));
		}
		for (char letter : countryName)
		{
			lowersearchCountry.push_back(tolower(letter));
		}

		if (lowercurrCountry == lowersearchCountry)
		{
			return curr_country;
		}

	}
	return noMatch;
}

void CountryList::displayList()
{
	for (Country curr_country : countryHappinessList)
	{
		cout << curr_country.name << " Happiness: " << curr_country.happiness << " Ranking " << curr_country.ranking << endl;
	}

}
