#pragma once

#include<string>
#include<vector>

#include"URLClass.h"

using std::vector;
using std::string;

class LinkQueue
{
	vector<URLClass> childUrlList;
	vector<URLClass> parentUrlList;
	vector<URLClass> badUrlList;

public:
	vector<URLClass> crawledUrlList;

	LinkQueue();
	~LinkQueue();
	void addBadLink(string);
	void add(vector<string>);
	void getNextElement(URLClass&);
};

