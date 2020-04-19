#include "crawler.h"

#include <string>
#include <iostream>

crawler::crawler()
{
	curl = curl_easy_init();
}

crawler::~crawler()
{
	curl_easy_cleanup(curl);
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void crawler::crawl()
{
	if (curl) {
		CURLcode res;
		std::string readBuffer;
		curl_easy_setopt(curl, CURLOPT_URL, "https://pastebin.com/archive");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		std::cout << readBuffer << "\n";
		res = curl_easy_perform(curl);
	}
}
