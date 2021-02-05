#include "pb_crawler.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

static constexpr std::chrono::seconds waittime{ 60 };

auto main() -> int
{
	pb_crawler crawler{};

	while (true)
	{
		std::cout << "fetching recent pastes...\n";
		auto pastes = crawler.crawlPastes();

		std::cout << "waiting " << waittime.count() << " seconds...\n";
		std::this_thread::sleep_for(waittime);
	}

	return 0;
}