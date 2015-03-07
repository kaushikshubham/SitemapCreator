#include "WriteToFile.h"

WriteToFile::WriteToFile(){}
WriteToFile::~WriteToFile(){}

void WriteToFile::writeToTextFile(std::vector<URLClass> listOfUrl){
	std::ofstream outputFile("Links.txt");
	if (outputFile){
		for each (URLClass urlClassObj in listOfUrl)
			outputFile << urlClassObj.url << "\n";
		outputFile.close();
	}
}