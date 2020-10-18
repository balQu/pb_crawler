#include "crawler.h"
#include "parser.h"
#include "database.h"

#include <iostream>
#include <unordered_set>
#include <chrono>
#include <thread>

static constexpr int waittime = 60;
static std::unordered_set<std::string> visited_ids;

std::vector<paste_data> getRecentPastes(Crawler& crawler)
{
	std::vector<paste_data> data;
	try
	{
		crawler.setUrl("https://pastebin.com/archive");
		Parser parser{ crawler.crawl() };
		if (parser.parse())
		{
			data = parser.getParsed_data();
		}
		return data;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << "\n";
		return {};
	}
}

std::stringstream getPasteContent(const paste_data& d, Crawler& crawler)
{
	auto result = visited_ids.find(d.id);
	if (result != std::end(visited_ids))
	{
		return {};
	}
	crawler.setUrl("https://pastebin.com/raw/" + d.id);
	visited_ids.insert(d.id);
#ifdef _DEBUG
	std::cout << "Found: [" << d.paste_language << "] - " << d.title << " (" << d.elapsed_time << ") /" << d.id << "\n";
#endif // DEBUG
	return crawler.crawl();
}

std::string replaceSingleQuote(std::string& content)
{
	auto pos = content.find('\'');
	while (pos != std::string::npos)
	{
		content.replace(pos, 1, "\"");
		pos = content.find('\'');
	}

	return content;
}

bool findPaste(db::Database& db, const std::string& id)
{
	std::string result = "SELECT * FROM pastes WHERE id=\"" + id + "\"";
	if (!db.query(result).empty())
	{
		return true;
	}
	return false;
}

bool addPaste(const paste_data& d, db::Database& db, const std::string& content)
{
	std::string insert = "INSERT INTO pastes VALUES('" + d.id + "', '" + d.paste_language + "', '" + d.title + "', '" + content + "')";
	auto result = db.query(insert);
	if (result.empty())
	{
		return false;
	}
	return true;
}

int main()
{
	db::config my_db_conf{ "localhost", "root", "", "pastes" };
	db::Database db = db::Database::getInstance();
	db.setConfig(my_db_conf);
	if (!db.connect())
	{
		std::cout << "Couldn't connect to the database.\n";
		return -1;
	}

	std::cout << "There are currently " << db.query("SELECT COUNT(*) from pastes") << " pastes in the database.\n\n";

	Crawler crawler{ "https://pastebin.com/archive" };
	std::vector<paste_data> data;

	while (true)
	{
#ifdef _DEBUG
		std::cout << "refreshing...\n";
#endif // _DEBUG

		data = getRecentPastes(crawler);

		for (auto& d : data)
		{
			auto content = getPasteContent(d, crawler);
			if (content.str() == "")
			{
				continue;
			}

			auto content_string = content.str();
			content_string = replaceSingleQuote(content_string);
			d.title = replaceSingleQuote(d.title);

			if (findPaste(db, d.id))
			{
				continue;
			}

			if (addPaste(d, db, content_string))
			{
				std::cout << "Added paste (id: " << d.id << ") to database.\n";
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds{ waittime });
	}
}