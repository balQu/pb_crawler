#pragma once

#include "crawler.h"
#include "parser.h"

#include <vector>
#include <utility>

#ifdef COMPILING_DLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

class pb_crawler
{
public:
	DLLEXPORT auto init() -> void;
	DLLEXPORT auto cleanup() -> void;
	DLLEXPORT auto crawlPastes() -> std::vector<paste_data>;

private:
};