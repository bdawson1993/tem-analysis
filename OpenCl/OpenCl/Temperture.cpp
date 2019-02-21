#include "pch.h"
#include "Temperture.h"

void Temperture::ReadFile(string name)
{
	ifstream dataFile;
	dataFile.open(name, ifstream::in);

	char line = dataFile.get();
	while (dataFile.good())
	{
		cout << line;
		line = dataFile.get();

		cout << line;
	}
	dataFile.close();


}
