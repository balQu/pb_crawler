#include "pb_crawler.h"

#include "curl/curl.h"

#include <chrono>
#include <iostream>
#include <thread>

static constexpr std::chrono::seconds waittime{ 60 };

auto main() -> int
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	while (true)
	{
		std::cout << "fetching recent pastes...\n";

		auto pastes = pb_crawler::crawlPastes();

		std::cout << "waiting " << waittime.count() << " seconds...\n";
		std::this_thread::sleep_for(waittime);
	}

	return 0;
}
