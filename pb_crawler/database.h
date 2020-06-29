#pragma once

#include "mysql.h"

#include <string>

class Database
{
private:
	MYSQL* connection;
public:
	Database() : connection(mysql_init(NULL)) {}
	bool connect(const std::string& host, const std::string& username, const std::string& password, const std::string& database_name);
	std::string query(const std::string& query);
};