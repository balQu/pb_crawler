#include "parser.h"

#include <exception>
#include <iostream>

auto Parser::parse() -> bool
{
  // set input position at the start of our paste table
  auto table_position = html_stream.str().find("<table");

  // TODO: maybe use a string-view instead of mutating the sstream
  html_stream.seekg(table_position);

  std::string line{};
  while (std::getline(html_stream, line))
  {
    // reached end of paste table
    if (line.find("</table>") != std::string::npos)
    {
      return true;
    }

    std::string openedTagA = "<a href=\"";
    auto id_pos = line.find(openedTagA);
    if (id_pos != std::string::npos)
    {
      // get ID of paste
      std::string endOfTag = "\">";
      auto id_end = line.find(endOfTag);
      id_end = line.find(endOfTag, id_end + 1);
      std::string id = line.substr(id_pos + openedTagA.length() + 1,
        id_end - (id_pos + openedTagA.length() + 1));

      // filter out obscure html tags
      if (id.find('<') != std::string::npos)
      {
        continue;
      }

      // get title of paste
      auto title_end = line.find("</a>");
      std::string title = line.substr(
        id_end + endOfTag.length(), title_end - (id_end + endOfTag.length()));

      // get paste time
      std::string next_line{};
      std::getline(html_stream, next_line);
      auto time_start = next_line.find("\">");
      auto time_end = next_line.find("ago");
      std::string timestamp =
        next_line.substr(time_start + 2, time_end - time_start + 1);

      // get paste language
      std::getline(html_stream, next_line);
      auto language_start = next_line.find("/archive");
      next_line.erase(0, language_start);
      language_start = next_line.find("\">");
      auto language_end = next_line.find("</a>");
      std::string paste_language =
        next_line.substr(language_start + 2, language_end - language_start - 2);

      // TODO: add correct timestamp instead of a dumb "elapsed time" stamp
      parsed_data.emplace_back(
        paste_data{ id, title, timestamp, paste_language });
    }
  }

  return true;
}