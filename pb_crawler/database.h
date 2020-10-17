#pragma once

#include "mysql.h"

#include <string>

namespace db
{
	struct config
	{
		std::string host;
		std::string username;
		std::string password;
		std::string database_name;

		config() = default;
		config(const std::string& host, const std::string& username,
			const std::string& password,
			const std::string& database_name) : host{ host }, username{ username },
			password{ password }, database_name{ database_name } { }
	};

	class Database
	{
	private:
		MYSQL* connection{ mysql_init(nullptr) };
		config db_config{};
	public:
		Database(const config& db_config) : db_config{db_config} {}
		void setConfig(const config& db_config) { this->db_config = db_config; }
		bool connect() const;
		std::string query(const std::string& query) const;
	};

} // namespace db