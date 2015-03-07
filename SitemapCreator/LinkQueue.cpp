#include "LinkQueue.h"

LinkQueue::LinkQueue(){}
LinkQueue::~LinkQueue(){}

void LinkQueue::add(vector<string> UrlList){
	if (!childUrlList.empty()){
		bool isPresentInCrawledList;
		for (vector<string>::iterator iterForNewList = UrlList.begin(); iterForNewList != UrlList.end(); ++iterForNewList){
			isPresentInCrawledList = false;
			for (vector<URLClass>::iterator iterForChildList = childUrlList.begin(); iterForChildList != childUrlList.end(); ++iterForChildList){
				if ((*iterForNewList).compare(iterForChildList->url) == NULL){
					isPresentInCrawledList = true;
					break;
				}
			}
			if (isPresentInCrawledList){
				URLClass urlClass(*iterForNewList);
				childUrlList.push_back(urlClass);
			}
		}
	}
	else{
		for (vector<string>::iterator iterForNewList = UrlList.begin(); iterForNewList != UrlList.end(); ++iterForNewList){
			{
				URLClass urlClass(*iterForNewList);
				childUrlList.push_back(urlClass);
			}
		}
	}
}
void LinkQueue::getNextElement(URLClass &urlClassNew){
	if (parentUrlList.empty()){
		if (childUrlList.empty()){
			urlClassNew.url = "";
			return;
		}
		bool isPresentInCrawledList;
		for (vector<URLClass>::iterator iterForChildList = childUrlList.begin(); iterForChildList != childUrlList.end(); ++iterForChildList){
			isPresentInCrawledList = false;
			if (!crawledUrlList.empty()){
				for (vector<URLClass>::iterator iterForCrawledList = crawledUrlList.begin(); iterForCrawledList != crawledUrlList.end(); ++iterForCrawledList){
					if ((iterForChildList->url).compare(iterForCrawledList->url) == NULL){
						isPresentInCrawledList = true;
						break;
					}
				}
			}
			if (!isPresentInCrawledList){
				parentUrlList.push_back(*iterForChildList);
			}
		}
		childUrlList.clear();
		if (parentUrlList.empty()){
			urlClassNew.url = "";
			return;
		}
	}
	URLClass urlClass = parentUrlList.back();
	crawledUrlList.push_back(urlClass);
	urlClassNew.url = urlClass.url;
	parentUrlList.pop_back();
}
void LinkQueue::addBadLink(string badLink){
	badUrlList.push_back(badLink);
}