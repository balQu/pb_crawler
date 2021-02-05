#include "pb_crawler.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

static constexpr std::chrono::seconds waittime{ 60 };

auto main() -> int
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	pb_crawler crawler{};

	while (true)
	{
		std::cout << "fetching recent pastes...\n";

		// TODO: "data" of crawler stacks up on each iteration...
		auto pastes = crawler.crawlPastes();

		std::cout << "waiting " << waittime.count() << " seconds...\n";
		std::this_thread::sleep_for(waittime);
	}

	return 0;
}
