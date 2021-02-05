#pragma once

#include "crawler.h"
#include "parser.h"

#include <vector>
#include <utility>

class pb_crawler
{
private:
	std::vector<paste_data> data{};

public:
	auto crawlPastes() -> std::vector<paste_data>;
};