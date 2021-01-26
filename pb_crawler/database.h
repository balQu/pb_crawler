#pragma once

#include "mysql.h"

#include <string>

namespace db {
struct config
{
	std::string host{};
	std::string username{};
	std::string password{};
	std::string database_name{};
};

// The class "Database" is a Singleton!
// see https://refactoring.guru/design-patterns/singleton
// only access is via Database::getInstance() which will
// always return the same class instance
class Database
{
private:
	Database() = default;

	MYSQL* connection{ mysql_init(nullptr) };
	config db_config{};

public:
	Database(const Database& other) = delete;
	auto operator=(const Database& other) -> Database& = delete;

	auto setConfig(const config& db_config) noexcept -> void
	{
		this->db_config = db_config;
	}
	auto connect() const -> bool;
	auto query(const std::string& query) const -> std::string;
	static auto getInstance() -> Database&;
};

}// namespace db