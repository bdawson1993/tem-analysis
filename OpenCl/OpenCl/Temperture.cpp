#include "pch.h"
#include "Temperture.h"





void Temperture::ReadFile(string name)
{
	ifstream dataFile;
	dataFile.open(name, std::ifstream::in);

	//read file
	std::string line;
	while (getline(dataFile, line))
	{
		//split line using iterator
		istringstream splitStream(line);
		vector<string> splitLine((istream_iterator<string>(splitStream)),
			istream_iterator<string>());

		//add data to vectors
		stationName.push_back(splitLine[0]);
		year.push_back(splitLine[1]);
		month.push_back(splitLine[2]);
		day.push_back(splitLine[3]);
		time.push_back(splitLine[4]);
		airTemp.push_back(stoi(splitLine[5]));


	}
	cout << " Loaded " << stationName.size() << " Records" << endl;

	dataFile.close();
}

vector<string> Temperture::StationName()
{
	return stationName;
}

vector<string> Temperture::Year()
{
	return year;
}

vector<string> Temperture::Month()
{
	return month;
}

vector<string> Temperture::Day()
{
	return day;
}

vector<string> Temperture::Time()
{
	return time;
}

vector<int> Temperture::AirTemp()
{
	return airTemp;
}

void Temperture::Table(int index)
{
	cout << stationName[index] << " " << year[index] << " " << month[index] << " " << day[index]
		<< " " << time[index] << " " << airTemp[index] << endl;
}
