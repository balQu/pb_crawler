#pragma once

#include "curl/curl.h"

#include <string>
#include <sstream>

class Crawler
{
private:
	CURL* curl;
	std::string url;
public:
	Crawler();
	Crawler(std::string url) : Crawler() { this->url = url; }
	~Crawler();
	std::stringstream crawl() const;
	void setUrl(std::string url) { this->url = url; }
};