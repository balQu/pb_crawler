#pragma once

#include <string>
#include <sstream>

namespace crawler {
auto crawl(const std::string& url) -> std::stringstream;
}