#include "crawler.h"
#include "parser.h"

#include <iostream>

int main()
{
	Crawler crawler{ "https://pastebin.com/archive" };
	std::vector<paste_data> data;

	try
	{
		Parser parser{ crawler.crawl() };
		if (parser.parse())
		{
			data = parser.getParsed_data();
		}
	}
	catch (const std::exception& exc)
	{
		exc.what();
	}

	std::vector<std::stringstream> raw_pastes;
	for (const auto& d : data)
	{
		crawler.setUrl("https://pastebin.com/raw/" + d.id);
		raw_pastes.emplace_back(crawler.crawl());
	}
}