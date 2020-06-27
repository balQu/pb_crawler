#include "crawler.h"
#include "parser.h"

#include <iostream>
#include <unordered_set>
#include <chrono>
#include <thread>

#define DEBUG

static constexpr int waittime = 60;
static std::unordered_set<std::string> visited_ids;

int main()
{
	Crawler crawler{ "https://pastebin.com/archive" };
	std::vector<paste_data> data;

	while (true)
	{
#ifdef DEBUG
		std::cout << "refreshing...\n";
#endif // DEBUG

		try
		{
			crawler.setUrl("https://pastebin.com/archive");
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
			auto result = visited_ids.find(d.id);
			if (result != std::end(visited_ids))
			{
				continue;
			}
			crawler.setUrl("https://pastebin.com/raw/" + d.id);
			raw_pastes.emplace_back(crawler.crawl());
			visited_ids.insert(d.id);
#ifdef DEBUG
			std::cout << "Added: [" << d.paste_language << "] - " << d.title << " (" << d.elapsed_time << ") /" << d.id << "\n";
#endif // DEBUG
		}
		std::this_thread::sleep_for(std::chrono::seconds{ waittime });
	}
}