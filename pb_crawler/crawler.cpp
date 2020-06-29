#include "crawler.h"

#include <exception>

Crawler::Crawler()
{
	curl = curl_easy_init();
}

Crawler::~Crawler()
{
	curl_easy_cleanup(curl);
}

// see https://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
static size_t WriteCallback(char* data, size_t size, size_t nmemb,
	std::stringstream* writerData)
{
	writerData->write(data, size * nmemb);
	return size * nmemb;
}

std::stringstream Crawler::crawl() const
{
	if (url.empty())
	{
		throw std::exception{ "Url is missing." };
	}

	if (!curl)
	{
		throw std::exception{ "Couldn't initialize cURL." };
	}

	CURLcode res;
	std::stringstream response;
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		throw std::exception{ "Couldn't perform the request." };
	}
	return response;
}
