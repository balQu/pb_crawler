#pragma once

#include "curl/curl.h"

#include <string>
#include <sstream>

namespace Crawler {
auto crawl(const std::string& url) -> std::stringstream;
}