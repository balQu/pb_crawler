#include "pb_crawler.h"

#include <iostream>


std::stringstream pb_crawler::getPasteContent(const paste_data& d)
{
	crawler.setUrl("https://pastebin.com/raw/" + d.id);
	return crawler.crawl();
}


std::vector<paste_data_content> pb_crawler::crawlPastes()
{

	std::vector<paste_data> somePastes;
	try
	{
		crawler.setUrl("https://pastebin.com/archive");
		Parser parser{ crawler.crawl() };
		if (parser.parse())
		{
			somePastes = parser.getParsed_data();
		}
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << "\n";
		return {};
	}

	for (const auto& p : somePastes)
	{
		data.emplace_back(paste_data_content{ p.id, p.title, p.paste_language, p.elapsed_time, getPasteContent(p).str() });
	}

	return data;
}