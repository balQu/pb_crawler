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


	// The class "Database" is a Singleton!
	// see https://refactoring.guru/design-patterns/singleton
	// only access is via Database::getInstance() which will
	// always return the same class instance
	class Database
	{
	private:
		Database() {}
		Database(const config& db_config) : db_config{db_config} {}

		MYSQL* connection{ mysql_init(nullptr) };
		config db_config{};

	public:
		void setConfig(const config& db_config) { this->db_config = db_config; }
		bool connect() const;
		std::string query(const std::string& query) const;
		static Database& getInstance();
	};

} // namespace db