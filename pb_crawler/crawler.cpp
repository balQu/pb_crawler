#include "crawler.h"

#include <exception>

Crawler::~Crawler()
{
	curl_easy_cleanup(curl);
}

// see https://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
static auto WriteCallback(char* data, size_t size, size_t nmemb,
	std::stringstream& writerData) -> size_t
{
	writerData.write(data, size * nmemb);
	return size * nmemb;
}

auto Crawler::crawl() const -> std::stringstream
{
	if (url.empty())
	{
		throw std::exception{ "Url is missing." };
	}

	if (!curl)
	{
		throw std::exception{ "Couldn't initialize cURL." };
	}

#pragma warning(suppress : 26812) // curl still uses enum instead of enum class (C lib)
	CURLcode res{};
	std::stringstream response{};
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
