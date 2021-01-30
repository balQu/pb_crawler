#include "pb_crawler.h"

#include <iostream>

constexpr auto PasteBinUrlRaw = "https://pastebin.com/raw/";
constexpr auto PasteBinUrlArchive = "https://pastebin.com/archive";

auto pb_crawler::getPasteContent(const paste_data& d) -> std::stringstream
{
	try
	{
		return Crawler::crawl(PasteBinUrlRaw + d.id);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << "\n";
		return {};
	}
}

auto pb_crawler::crawlPastes() -> std::vector<paste_data_content>
{
	std::vector<paste_data> foundPastes{};
	try
	{
		Parser parser{ Crawler::crawl("https://pastebin.com/archive") };
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
		data.emplace_back(paste_data_content{ p.id,
			p.title,
			p.elapsed_time,
			p.paste_language,
			getPasteContent(p).str() });
	}

	return data;
}