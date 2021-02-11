#pragma once

#include "crawler.h"
#include "parser.h"

#include <vector>
#include <utility>

class pb_crawler
{
public:
	static auto crawlPastes() -> std::vector<paste_data>;
};