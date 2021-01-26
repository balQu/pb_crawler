#pragma once

#include <string>
#include <sstream>
#include <vector>

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
	std::vector<paste_data> parsed_data{};
	std::stringstream html_stream{};

public:
	Parser(std::stringstream stream) : html_stream{ std::move(stream) } {}
	auto getParsed_data() const -> std::vector<paste_data>
	{
		return parsed_data;
	}
	auto setHtmlStream(std::stringstream stream) -> void
	{
		html_stream = std::move(stream);
	}
	auto parse() -> bool;
};