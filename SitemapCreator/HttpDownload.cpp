#include "HttpDownload.h"
HttpDownload::HttpDownload(){
	hSession = NULL;
	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WebCrawler", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
}
HttpDownload::~HttpDownload(){}

string HttpDownload::Download(string webLink)
{
	string webPage;
	dwSize = 0;
	dwDownloaded = 0;
	pszOutBuffer;
	bResults = FALSE;
	hConnect = NULL;
	hRequest = NULL;

	wstring wide_string(webLink.begin(), webLink.end());

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, wide_string.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);

	// Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

	// Send a request.
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

	// End the request.
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	// Keep checking for data until there is nothing left.
	if (bResults)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				cout << "Error " << GetLastError() << " in WinHttpQueryDataAvailable.\n";
			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				cout << "Out of memory\n";
				dwSize = 0;
			}
			else
			{
				// Read the data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
					cout << "Error " << GetLastError() << " in WinHttpReadData.\n";
				else
					webPage += pszOutBuffer;

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}
		} while (dwSize > 0);
	}

	// Report any errors.
	if (!bResults)
		cout << "Error " << GetLastError() << " has occurred.\n";

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return webPage;
}