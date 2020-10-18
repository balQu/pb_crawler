#include "database.h"

namespace db
{
	Database& Database::getInstance()
	{
		static Database instance;
		return instance;
	}

	bool Database::connect() const
	{
		if (mysql_real_connect(connection, db_config.host.c_str(),
			db_config.username.c_str(), db_config.password.c_str(),
			db_config.database_name.c_str(), 33060, nullptr, 0) == nullptr)
		{
			auto error = mysql_error(connection);
			fprintf(stderr, "%s\n", error);
			mysql_close(connection);
			exit(1);
			return false;
		}
		return true;
	}

	std::string Database::query(const std::string& query) const
	{
		if (mysql_query(connection, query.c_str()))
		{
			auto error = mysql_error(connection);
			if (error != nullptr)
			{
				fprintf(stderr, "%s\n", error);
				return "";
			}
		}

		MYSQL_RES* result = mysql_store_result(connection);
		if (!result)
		{
			return  "Executed query";
		}

		int num_fields = mysql_num_fields(result);
		MYSQL_ROW row;
		std::string query_result;

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
} // namespace db