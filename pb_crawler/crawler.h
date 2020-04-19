#pragma once

#include "curl/curl.h"

class crawler
{
private:
	CURL* curl;
public:
	crawler();
	~crawler();
	void crawl();

};