#include "database.h"
#include "pb_crawler.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

static constexpr std::chrono::seconds waittime{ 60 };

auto findPaste(const std::string& id) -> bool
{
	std::string sql_query = "SELECT * FROM pastes WHERE id=\"" + id + "\"";
	auto result = db::Database::getInstance().query(sql_query);
	return !result.empty();
}

auto addPaste(const paste_data_content& d) -> bool
{
	std::string sql_insert = "INSERT INTO pastes VALUES('" + d.id + "', '"
							 + d.paste_language + "', '" + d.title + "', '"
							 + d.content + "')";
	auto result = db::Database::getInstance().query(sql_insert);
	return !result.empty();
}

auto main() -> int
{
	db::Database::getInstance().setConfig(
		{ "localhost", "root", "", "pastes" });
	if (!db::Database::getInstance().connect())
	{
		std::cout << "Couldn't connect to the database.\n";
		return 1;
	}

	std::cout << "There are currently "
			  << db::Database::getInstance().query(
					 "SELECT COUNT(*) from pastes")
			  << " pastes in the database.\n\n";

	pb_crawler crawler{};

	while (true)
	{
#ifdef _DEBUG
		std::cout << "refreshing...\n";
#endif// _DEBUG

		std::cout << "fetching recent pastes...\n";
		auto pastes = crawler.crawlPastes();

		for (auto& p : pastes)
		{
			// TODO: early return if id is already visited (keep track in a
			// vector<string> visited ids?)

			if (p.content.empty())
			{
				continue;
			}

			std::replace(
				std::begin(p.content), std::end(p.content), '\'', '\"');
			std::replace(std::begin(p.title), std::end(p.title), '\'', '\"');

			if (findPaste(p.id))
			{
				continue;
			}

			if (addPaste(p))
			{
				std::cout << "Added paste (id: " << p.id << ") to database.\n";
			}
		}
		std::cout << "waiting " << waittime.count() << " seconds...\n";
		std::this_thread::sleep_for(waittime);
	}

	return 0;
}