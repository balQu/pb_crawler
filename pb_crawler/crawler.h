#pragma once

#include <string>
#include <sstream>

namespace Crawler {
auto crawl(const std::string& url) -> std::stringstream;
}