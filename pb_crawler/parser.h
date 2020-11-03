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
	std::vector<paste_data> getParsed_data() const { return parsed_data; }
	void setHtmlStream(std::stringstream stream) { html_stream = std::move(stream); }
	bool parse();
};