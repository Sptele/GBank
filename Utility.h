#include <string>
#include <iostream>
#include <optional>
#include <vector>

#pragma once
class Utility
{
public:
	static std::string BAR_DIVIDER_TM_C;

	static std::string prompt(const std::string& msg);
	static bool str_isdigit(const std::string& s);
	static std::vector<std::string> split(const std::string& line, char delimiter=' ');
	static std::optional<double> prompt_money(const std::string& msg);
	static size_t hash(const std::string& p);
	static void replace_all(std::string& str, const std::string& from, const std::string& to);
};

