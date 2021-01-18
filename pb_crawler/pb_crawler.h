#pragma once

#include "crawler.h"
#include "parser.h"

#include <vector>

struct paste_data_content : public paste_data
{
	std::string content{};
};

class pb_crawler
{
private:
	Crawler crawler{ "https://pastebin.com/archive" };
	std::vector<paste_data_content> data{};

	std::stringstream getPasteContent(const paste_data& d);
public:
	std::vector<paste_data_content> crawlPastes();
};