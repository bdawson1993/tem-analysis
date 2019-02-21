#include "pch.h"
#include "Temperture.h"

void Temperture::ReadFile(string name)
{
	ifstream dataFile;
	dataFile.open(name, ifstream::in);

	string line;
	
	while (getline(dataFile, line))
	{
		//split line using iterator
		istringstream splitStream(line);
		vector<string> splitLine((istream_iterator<string>(splitStream)),
			istream_iterator<string>());

		stationName.push_back(splitLine[0]);
		year.push_back(splitLine[1]);
		month.push_back(splitLine[2]);
		day.push_back(splitLine[3]);
		time.push_back(splitLine[4]);
		airTemp.push_back(stoi(splitLine[5]));


	}
}
