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

auto insertPaste(const paste_data_content& d) -> bool
{
	std::string sql_insert = "INSERT INTO pastes VALUES('" + d.id + "', '"
							 + d.paste_language + "', '" + d.title + "', '"
							 + d.content + "')";
	auto result = db::Database::getInstance().query(sql_insert);
	return !result.empty();
}

auto addPaste(paste_data_content& p) -> void
{
	if (p.content.empty())
	{
		return;
	}

	std::replace(std::begin(p.content), std::end(p.content), '\'', '\"');
	std::replace(std::begin(p.title), std::end(p.title), '\'', '\"');

	if (findPaste(p.id))
	{
		return;
	}

	if (insertPaste(p))
	{
		std::cout << "Added paste (id: " << p.id << ") to database.\n";
	}
}

auto main() -> int
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
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
		std::cout << "fetching recent pastes...\n";

		// TODO: "data" of crawler stacks up on each iteration...
		auto pastes = crawler.crawlPastes();

		std::for_each(std::begin(pastes), std::end(pastes), addPaste);

		std::cout << "waiting " << waittime.count() << " seconds...\n";
		std::this_thread::sleep_for(waittime);
	}

	return 0;
}