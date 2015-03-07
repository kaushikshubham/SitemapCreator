#pragma once

#include <Windows.h>
#include <WinHttp.h>
#include <Winerror.h>
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::wstring;

#pragma comment(lib, "winhttp")

class HttpDownload
{
	DWORD dwSize;
	DWORD dwDownloaded;
	LPSTR pszOutBuffer;
	BOOL bResults;
	HINTERNET hSession, hConnect, hRequest;

public:

	HttpDownload();
	~HttpDownload();
	string Download(string);
};