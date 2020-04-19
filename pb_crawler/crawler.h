#pragma once

#include "curl/curl.h"

#include <string>

class crawler
{
private:
	CURL* curl;
public:
	crawler();
	~crawler();
	std::string crawl();

};