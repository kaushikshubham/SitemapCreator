#include "WebCrawler.h"
WebCrawler::WebCrawler(){}
WebCrawler::~WebCrawler(){}
bool WebCrawler::isUrlValid(string &url){
	if (url.find(webSiteName) != string::npos){
		int index = 0;
		while (!isalnum(url[index]))
			index++;
		if (index > 0)
			url = url.substr(index, url.size());
		return true;
	}
	else
		return false;
}
void WebCrawler::getAllUrlsFromWebPage(){
	string output;
	size_t found;
	while (webPageDownloaded.size() > NULL){
		found = webPageDownloaded.find("href=\"");
		if (found == string::npos)
			break;
		webPageDownloaded = webPageDownloaded.substr(found + 5);
		found = webPageDownloaded.find("\"");
		if (found == string::npos)
			break;
		else if (found == NULL || found == 1){
			webPageDownloaded = webPageDownloaded.substr(found + 1, webPageDownloaded.size());
			found = webPageDownloaded.find("\"");
			if (found == string::npos)
				break;
		}
		output = webPageDownloaded.substr(NULL, found);

		if (isUrlValid(output))
			ListOfURLs.push_back(output);
		webPageDownloaded = webPageDownloaded.substr(found + 1);
	}
}
void WebCrawler::crawl(){
	URLClass *urlclassObj = new URLClass();
	cout << "Enter the website name : ";
	getline(cin, webSiteName);
	removeExtras();
	vector<string> tempWebsiteName = { webSiteName };
	linkQueue.add(tempWebsiteName);
	tempWebsiteName.clear();
	linkQueue.getNextElement(*urlclassObj);
	cout << "Url received from queue : " << urlclassObj->url << endl;
	do{
		webPageDownloaded = httpDownload.Download(urlclassObj->url);
		if (webPageDownloaded.size() != NULL){
			getAllUrlsFromWebPage();
			cout << "No. of urls adding : " << ListOfURLs.size() << endl;
			if (ListOfURLs.size() > NULL)
				linkQueue.add(ListOfURLs);
		}
		linkQueue.getNextElement(*urlclassObj);
		cout << "Url received from queue : " << urlclassObj->url << endl;
	} while (!(urlclassObj->url).empty());
	writeToFile.writeToTextFile(linkQueue.crawledUrlList);
	delete urlclassObj;
}
void WebCrawler::removeExtras(){
	size_t found;
	found = webSiteName.find("://");
	if (found != std::string::npos)
		webSiteName.replace(NULL, found + 3, "");
	found = webSiteName.find("www.");
	if (found != std::string::npos && found == NULL)
		webSiteName.replace(NULL, found + 4, "");
	found = webSiteName.find("/");
	if (found != std::string::npos && found != NULL)
		webSiteName = webSiteName.substr(NULL, found);
	cout << "WebSite name is " << webSiteName << endl;
}