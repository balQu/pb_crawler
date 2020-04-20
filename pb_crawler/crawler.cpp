#include "crawler.h"

crawler::crawler()
{
	curl = curl_easy_init();
}

crawler::~crawler()
{
	curl_easy_cleanup(curl);
}

// see https://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
static size_t WriteCallback(char* data, size_t size, size_t nmemb,
	std::string* writerData)
{
	writerData->append(data, size * nmemb);
	return size * nmemb;
}

std::string crawler::crawl()
{
	if (curl) {
		CURLcode res;
		std::string response; // maybe a stringstream is better?
		curl_easy_setopt(curl, CURLOPT_URL, "https://pastebin.com/archive");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			//throw something; //TODO
			return std::string{ "Couldn't perform the request." };
		}
		return response;
	}

	return std::string{};
}
