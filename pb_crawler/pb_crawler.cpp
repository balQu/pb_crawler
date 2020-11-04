#include "database.h"
#include "pb_crawler.h"

#include <iostream>
#include <chrono>
#include <thread>

static constexpr int waittime = 60;

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

bool findPaste(const std::string& id)
{
	std::string result = "SELECT * FROM pastes WHERE id=\"" + id + "\"";
	if (!db::Database::getInstance().query(result).empty())
	{
		return true;
	}
	return false;
}

bool addPaste(const paste_data_content& d)
{
	std::string insert = "INSERT INTO pastes VALUES('" + d.id + "', '" + d.paste_language + "', '" + d.title + "', '" + d.content + "')";
	auto result = db::Database::getInstance().query(insert);
	if (result.empty())
	{
		return false;
	}
	return true;
}

int main()
{
	db::config my_db_conf{ "localhost", "root", "", "pastes" };
	db::Database::getInstance().setConfig(my_db_conf);
	if (!db::Database::getInstance().connect())
	{
		std::cout << "Couldn't connect to the database.\n";
		return 1;
	}

	std::cout << "There are currently " << db::Database::getInstance().query("SELECT COUNT(*) from pastes") << " pastes in the database.\n\n";

	pb_crawler crawler;

	while (true)
	{
#ifdef _DEBUG
		std::cout << "refreshing...\n";
#endif // _DEBUG

		std::cout << "fetching recent pastes...\n";
		auto pastes = crawler.crawlPastes();

		for(auto& p : pastes)
		{

			// TODO: early return if id is already visited (keep track in a vector<string> visited ids?)

			if (p.content == "")
			{
				continue;
			}

			p.content = replaceSingleQuote(p.content);
			p.title = replaceSingleQuote(p.title);

			if (findPaste(p.id))
			{
				continue;
			}

			if (addPaste(p))
			{
				std::cout << "Added paste (id: " << p.id << ") to database.\n";
			}
		}
		std::cout << "waiting " << waittime << " seconds...\n";
		std::this_thread::sleep_for(std::chrono::seconds{ waittime });
	}
}