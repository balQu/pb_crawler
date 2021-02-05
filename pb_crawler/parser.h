#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <queue>

struct paste_data
{
	std::string id{};
	std::string title{};
	std::string elapsed_time{};
	std::string paste_language{};
};

class Parser
{
private:
	std::queue<paste_data> parsed_data_queue{};
	std::stringstream html_stream{};

public:
	Parser(std::stringstream stream) : html_stream{ std::move(stream) } {}

	auto getPasteQueue() const -> std::queue<paste_data>
	{
		return parsed_data_queue;
	}

	auto setHtmlStream(std::stringstream stream) -> void
	{
		html_stream = std::move(stream);
	}

	auto parse() -> bool;
};