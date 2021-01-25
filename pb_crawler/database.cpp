#include "database.h"

#include <iostream>

constexpr int MySqlPort = 33060;

namespace db {
Database& Database::getInstance()
{
	static Database instance{};
	return instance;
}

bool Database::connect() const
{
	if (mysql_real_connect(connection,
			db_config.host.c_str(),
			db_config.username.c_str(),
			db_config.password.c_str(),
			db_config.database_name.c_str(),
			MySqlPort,
			nullptr,
			0)
		== nullptr)
	{
		auto error = mysql_error(connection);
		if (error != nullptr)
		{
			std::cerr << error << "\n";
		}

		mysql_close(connection);
		return false;
	}
	return true;
}

std::string Database::query(const std::string& query) const
{
	if (mysql_query(connection, query.c_str()) != 0)
	{
		auto error = mysql_error(connection);
		if (error != nullptr)
		{
			std::cerr << error << "\n";
		}
		return "";
	}

	MYSQL_RES* result = mysql_store_result(connection);
	if (!result)
	{
		return "";
	}

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row{};
	std::string query_result{};

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			if (row[i])
			{
				query_result += row[i];
			}
		}
	}
	mysql_free_result(result);
	return query_result;
}
}// namespace db