#include "pb_crawler.h"

#include <iostream>


auto pb_crawler::getPasteContent(const paste_data& d) -> std::stringstream
{
	crawler.setUrl("https://pastebin.com/raw/" + d.id);
	return crawler.crawl();
}


auto pb_crawler::crawlPastes() -> std::vector<paste_data_content>
{

	std::vector<paste_data> foundPastes{};
	try
	{
		crawler.setUrl("https://pastebin.com/archive");
		Parser parser{ crawler.crawl() };
		if (parser.parse())
		{
			foundPastes = parser.getParsed_data();
		}
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << "\n";
		return {};
	}

	for (const auto& p : foundPastes)
	{
		data.emplace_back(paste_data_content{ p.id, p.title, p.paste_language, p.elapsed_time, getPasteContent(p).str() });
	}

	return data;
}