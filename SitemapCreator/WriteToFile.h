#pragma once

#include<fstream>
#include<vector>

#include"URLClass.h"

class WriteToFile
{
public:
	WriteToFile();
	~WriteToFile();
	void writeToTextFile(std::vector<URLClass>);
};

