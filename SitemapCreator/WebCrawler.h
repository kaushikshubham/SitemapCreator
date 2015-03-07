#pragma once
#include<iostream>
#include<cctype>

#include"HttpDownload.h"
#include"LinkQueue.h"
#include"URLClass.h"
#include"WriteToFile.h"

using std::cout;
using std::cin;
using std::endl;

class WebCrawler
{
	string webSiteName;
	string webPageDownloaded;
	vector<string> ListOfURLs;

	HttpDownload httpDownload;
	LinkQueue linkQueue;
	WriteToFile writeToFile;

	void removeExtras();
	void getAllUrlsFromWebPage();
	bool WebCrawler::isUrlValid(string&);

public:
	WebCrawler();
	~WebCrawler();
	void crawl();
};

