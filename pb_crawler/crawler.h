#pragma once

#include "curl/curl.h"

#include <string>
#include <sstream>

class Crawler
{
private:
	CURL* curl{ curl_easy_init() };
	std::string url{};

public:
	explicit Crawler(const std::string& url) : url{ url } {}
	~Crawler();

	Crawler(const Crawler& other) = delete;
	auto operator=(const Crawler& other) -> Crawler& = delete;
	Crawler(const Crawler&& other) = delete;
	auto operator=(const Crawler&& other) -> Crawler& = delete;

	auto crawl() const -> std::stringstream;
	auto setUrl(const std::string& url) -> void
	{
		this->url = url;
	}
};