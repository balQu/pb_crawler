#include "pb_crawler.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

constexpr auto PasteBinUrlRaw = "https://pastebin.com/raw/";
constexpr auto PasteBinUrlArchive = "https://pastebin.com/archive";
constexpr auto ThreadCount = 25;

auto pb_crawler::crawlPastes() -> std::vector<paste_data>
{
	std::queue<paste_data> paste_queue{};
	try
	{
		parser parser{ crawler::crawl(PasteBinUrlArchive) };
		if (parser.parse())
		{
			paste_queue = parser.getPasteQueue();
		}
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << "\n";
		return {};
	}

	std::vector<std::thread> threads;
	std::mutex paste_queue_mutex{};
	std::mutex data_mutex{};
	std::vector<paste_data> data;

	for (size_t i = 0; i < ThreadCount; ++i)
	{
		threads.emplace_back([&]() {
			while (!paste_queue.empty())
			{
				paste_data p;
				{
					std::scoped_lock lock{ paste_queue_mutex };
					p = paste_queue.front();
					paste_queue.pop();
				}

				auto content = crawler::crawl(PasteBinUrlRaw + p.id).str();

				std::scoped_lock lock{ data_mutex };
				data.emplace_back(paste_data{
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