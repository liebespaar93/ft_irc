
#include "Utile.hpp"
#include <algorithm>

std::vector<std::string> split(const std::string &str, const std::string &delimiters)
{
	std::vector<std::string> tokens;

	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	return tokens;
}

bool ft_check_valid(const char c)
{
	const char allowed_chars[9] = { '[', ']', '\\', '`', '_', '^', '{', '|', '}' };
	for (int i = 0; i < 9; i++)
	{
		if (allowed_chars[i] == c)
			return true;
	}
	if (isalpha(c))
		return true;
	else
		return false;
}

std::string ft_itostring(int i)
{
	std::string num = "";
	std::string sign = "";
	if (i == 0)
		return "0";
	if (i < 0)
	{
		i *= -1;
		sign = "-";
	}
	while (i != 0)
	{
		num.push_back('0' + (i % 10));
		std::reverse(num.begin(), num.end());
		i = i / 10;
	}
	return (sign + num);
}
