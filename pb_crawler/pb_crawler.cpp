#include "pb_crawler.h"

#include <iostream>

constexpr auto PasteBinUrlRaw = "https://pastebin.com/raw/";
constexpr auto PasteBinUrlArchive = "https://pastebin.com/archive";

std::stringstream pb_crawler::getPasteContent(const paste_data& d)
{
  crawler.setUrl(PasteBinUrlRaw + d.id);
  return crawler.crawl();
}

std::vector<paste_data_content> pb_crawler::crawlPastes()
{
  std::vector<paste_data> foundPastes{};
  try
  {
    crawler.setUrl(PasteBinUrlArchive);
    Parser parser{ crawler.crawl() };
    if (parser.parse())
    {
      foundPastes = parser.getParsed_data();
    }
  }
  catch (const std::exception& exc)
  {
    std::cout << exc.what() << "\n";
    return {};
  }

  for (const auto& p : foundPastes)
  {
    data.emplace_back(paste_data_content{ p.id,
      p.title,
      p.paste_language,
      p.elapsed_time,
      getPasteContent(p).str() });
  }

  return data;
}