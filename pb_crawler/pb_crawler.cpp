#include "crawler.h"

#include <iostream>

int main()
{
	crawler crawler;
	std::string response = crawler.crawl();
	std::cout << response << "\n";
}