#include "Utility.h"

std::string Utility::BAR_DIVIDER_TM_C{ "========================================================" };

std::string Utility::prompt(const std::string& msg)
{
	std::string input;
	std::cout << msg << std::endl;
	std::getline(std::cin, input);
	return input;
}

bool Utility::str_isdigit(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c) && c != '.'; }) == s.end();
}

std::vector<std::string> Utility::split(const std::string& line, char delimiter)
{
	std::vector<std::string> v;

	size_t past_i = 0;

	for (size_t i = 0; i < line.size(); i++) {
		if (line.at(i) == delimiter) {
			v.push_back(line.substr(past_i, i - past_i));
			past_i = i+1;
		}
	}

	v.push_back(line.substr(past_i));

	return v;
}

size_t Utility::hash(const std::string& password)
{
	std::hash<std::string> hasher;
	return hasher(password);
}

void Utility::replace_all(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		// Advance start_pos to avoid replacing the newly inserted 'to' string
		// if 'to' contains 'from' as a substring (e.g., replacing "x" with "yx").
		start_pos += to.length();
	}
}

std::optional<double> Utility::prompt_money(const std::string& msg)
{
	std::string s_amt = prompt(msg);

	if (!Utility::str_isdigit(s_amt)) {
		std::cout << "[ERROR] Money amounts must be entered as ONLY a double. Do not include $ signs or other characters." << std::endl;
		
		return {};
	}

	return std::stod(s_amt);
}


