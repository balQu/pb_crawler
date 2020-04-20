#include "crawler.h"
#include "parser.h"

#include <iostream>

int main()
{
	Crawler crawler{ "https://pastebin.com/archive" };

	try
	{
		Parser parser{ crawler.crawl() };
		if (parser.parse())
		{
			std::vector<paste_data> data = parser.getParsed_data();
		}
	}
	catch (const std::exception& exc)
	{
		exc.what();
	}
}