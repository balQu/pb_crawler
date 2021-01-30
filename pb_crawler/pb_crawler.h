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
	std::vector<paste_data_content> data{};

	auto getPasteContent(const paste_data& d) -> std::stringstream;

public:
	auto crawlPastes() -> std::vector<paste_data_content>;
};