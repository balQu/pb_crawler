#include "curl/curl.h"

#include "crawler.h"

#include <exception>

namespace {
// see
// https://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
static auto WriteCallback(char* data,
	size_t size,
	size_t nmemb,
	std::stringstream& writerData) -> size_t
{
	writerData.write(data, size * nmemb);
	return size * nmemb;
}

}// namespace

auto crawler::crawl(const std::string& url) -> std::stringstream
{
	if (url.empty())
	{
		throw std::exception{ "Url is missing." };
	}

	CURL* curl{ curl_easy_init() };
	if (!curl)
	{
		throw std::exception{ "Couldn't initialize cURL." };
	}

	// curl still uses enum instead of enum class (C lib)
#pragma warning(push)
#pragma warning(suppress : 26812)
	CURLcode res{};
#pragma warning(pop)
	std::stringstream response{};

	try
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
	}
	catch (const std::exception&)
	{
		curl_easy_cleanup(curl);
		throw;
	}

	curl_easy_cleanup(curl);

	if (res != CURLE_OK)
	{
		throw std::exception{ "Couldn't perform the request." };
	}
	return response;
}
