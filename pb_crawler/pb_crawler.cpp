#include "crawler.h"
#include "parser.h"

#include <iostream>

int main()
{
	Crawler crawler{ "https://pastebin.com/archive" };

	try
	{
		std::stringstream response = crawler.crawl();
		std::cout << response.str() << "\n";
	}
	catch (const std::exception& exc)
	{
		exc.what();
	}
}