#include "parser.h"

#include <exception>
#include <iostream>

bool Parser::parse()
{
	// set input position at the start of our paste table
	auto table_position = html_stream.str().find("<table");
	html_stream.seekg(table_position);

	std::string line;
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
			std::string id = line.substr(id_pos + openedTagA.length() + 1, id_end - (id_pos + openedTagA.length() + 1));

			// filter out obscure html tags
			if (id.find("<") != std::string::npos)
			{
				continue;
			}

			// get title of paste
			auto title_end = line.find("</a>");
			std::string title = line.substr(id_end + endOfTag.length(), title_end - (id_end + endOfTag.length()));

			// TODO: add elapsed_time and paste_language
			parsed_data.emplace_back(paste_data{ id, title, "soon", "some lang" });
		}
	}

	return true;
}