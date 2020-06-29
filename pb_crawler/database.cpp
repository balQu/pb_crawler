#include "database.h"

bool Database::connect(const std::string& host, const std::string& username, const std::string& password, const std::string& database_name)
{
	if (mysql_real_connect(connection, host.c_str(), username.c_str(), password.c_str(), database_name.c_str(), 33060, NULL, 0) == NULL)
	{
		auto error = mysql_error(connection);
		fprintf(stderr, "%s\n", error);
		mysql_close(connection);
		exit(1);
		return false;
	}
	return true;
}

std::string Database::query(const std::string& query)
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