#include "pb_crawler.h"

#include <iostream>
#include <thread>
#include <mutex>

constexpr auto PasteBinUrlRaw = "https://pastebin.com/raw/";
constexpr auto PasteBinUrlArchive = "https://pastebin.com/archive";
constexpr auto threadCount = 25;

auto pb_crawler::crawlPastes() -> std::vector<paste_data_content>
{
	// TODO: should be a std::queue
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

	std::vector<std::thread> threads;
	std::mutex foundPastes_mutex{};
	std::mutex data_mutex{};

	for (size_t i = 0; i < threadCount; ++i)
	{
		threads.emplace_back([&]() {
			while (!foundPastes.empty())
			{
				paste_data p;
				{
					std::scoped_lock lock{ foundPastes_mutex };
					// TODO: should be a std::queue
					p = foundPastes.back();
					foundPastes.pop_back();
				}

				auto content = Crawler::crawl(PasteBinUrlRaw + p.id).str();

				std::scoped_lock lock{ data_mutex };
				data.emplace_back(paste_data_content{
					p.id, p.title, p.elapsed_time, p.paste_language, content });
			}
		});
	}

	for (auto& t : threads)
	{
		t.join();
	}

	return data;
}