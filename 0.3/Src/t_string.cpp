#include <cstdarg>
#include <algorithm>
#include <sstream>
#include "t_string.h"

t_string::t_string() : value("")
{
}

t_string::t_string(const char* str) : value(str)
{
}

t_string::t_string(const t_string& other) : value(other.value)
{
}

t_string::t_string(const std::string& other) : value(other)
{
}

t_string::t_string(const char& single_char) : value(1, single_char)
{
}

t_string::t_string(t_string&& other) noexcept : value(std::move(other.value))
{
}

t_string::t_string(int value) : value(from_int(value))
{
}

t_string::operator const std::string&() const
{
	return (const std::string&) value;
}

bool t_string::operator==(const t_string& other) const
{
	return value == other.value;
}

t_string& t_string::operator=(const char* other)
{
	value = other;
	return *this;
}

t_string& t_string::operator=(const t_string& other)
{
	if (this != &other)
		value = other.value;

	return *this;
}

t_string& t_string::operator=(const std::string& other)
{
	value = other;
	return *this;
}

t_string& t_string::operator=(t_string&& other) noexcept
{
	if (this != &other)
		value = std::move(other.value);

	return *this;
}

char& t_string::operator[](size_t index)
{
	return value[index];
}

const char& t_string::operator[](size_t index) const
{
	return value[index];
}

t_string& t_string::operator+=(const t_string& other)
{
	value += other.value;
	return *this;
}

t_string& t_string::operator+=(const int& ch)
{
	value.push_back(ch);
	return *this;
}

t_string t_string::operator+(const t_string& other) const
{
	return t_string(value + other.value);
}

const std::string& t_string::s_str() const
{
	return value;
}

const char* t_string::c_str() const noexcept
{
	return value.c_str();
}
	
size_t t_string::length() const noexcept
{
	return value.length();
}

bool t_string::has_length(int len) const noexcept
{
	return value.length() == len;
}

bool t_string::has_length(int min, int max) const noexcept
{
	return value.length() >= min && value.length() <= max;
}

int t_string::to_int() const
{
	t_string str = t_string(value).trim();
	if (str.empty())
		return 0;

	bool negative = str[0] == '-';
	bool positive = str[0] == '+';

	if (negative || positive)
		str = str.skip(1);

	int int_value = 0;

	try {
		if ((str[0] == '0' && str[1] == 'x') || (str[0] == '&' && toupper(str[1]) == 'H'))
			int_value = std::stoi(str.skip(2), nullptr, 16);
		else if ((str[0] == '0' && str[1] == 'b') || (str[0] == '&' && toupper(str[1]) == 'B'))
			int_value = std::stoi(str.skip(2), nullptr, 2);
		else if (isdigit(str[0]))
			int_value = std::stoi(str);
	}
	catch (std::out_of_range) {
		int_value = 0;
	}

	return negative ? -int_value : int_value;
}

float t_string::to_float() const
{
	float float_value = 0.0f;

	t_string str = t_string(value).trim();

	bool sign = str[0] == '-';
	if (sign)
		str = str.skip(1);

	float_value = (float)std::atof(str.c_str());

	return sign ? -float_value : float_value;
}

void t_string::clear() noexcept
{
	value.clear();
}

bool t_string::empty() const noexcept
{
	return value.empty();
}

bool t_string::is_number() const noexcept
{
	std::string text = value;
	if (text.starts_with("-"))
		text = skip(1);

	std::string::const_iterator it = text.begin();
	while (it != text.end() && std::isdigit(*it)) ++it;
	return !text.empty() && it == text.end();
}

t_string t_string::to_upper() const
{
	std::string result = value;

	for (unsigned i = 0; i < result.size(); i++)
		result[i] = toupper(result[i]);

	return result;
}

t_string t_string::to_lower() const
{
	std::string result = value;

	for (unsigned i = 0; i < result.size(); i++)
		result[i] = tolower(result[i]);

	return result;
}

t_string t_string::trim() const
{
	size_t first = value.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return "";
		
	size_t last = value.find_last_not_of(" \t\n\r");
	return value.substr(first, last - first + 1);
}

t_string t_string::skip(int count) const
{
	return remove_first(count);
}

t_string t_string::remove_first(int count) const
{
	if (count > value.length())
		return "";

	return value.substr(count);
}

t_string t_string::remove_last(int count) const
{
	if (count > value.length())
		return "";

	return value.substr(0, value.length() - count);
}

t_string t_string::remove_first_and_last(int count) const
{
	return remove_first(count).remove_last(count);
}

t_string t_string::get_first(int count) const
{
	return value.substr(0, count);
}

t_string t_string::get_last(int count) const
{
	if (value.size() < (unsigned)count)
		return value;

	return value.substr(value.size() - count, count);
}

t_list<t_string> t_string::split(char delim, bool trim_tokens) const
{
	t_list<t_string> elems;
	std::string item;
	std::stringstream ss(value);

	while (std::getline(ss, item, delim)) {
		if (trim_tokens)
			elems.emplace_back(t_string(item).trim());
		else
			elems.emplace_back(item);
	}

	return elems;
}

t_list<t_string> t_string::split_chunks(int chunk_size) const
{
	t_list<t_string> tokens;
	std::string token = "";

	for (int i = 0; i < value.length(); i++) {
		token += value[i];
		if (token.length() == chunk_size) {
			tokens.push_back(token);
			token = "";
		}
	}

	if (!token.empty())
		tokens.push_back(token);

	return tokens;
}

t_string t_string::substr(int first) const
{
	return value.substr(first);
}

t_string t_string::substr(int first, int last) const
{
	last++;

	if (first < 0)
		first = 0;
	if (last < first)
		return "";
	if (last > value.length())
		return "";

	int&& count = last - first;
	return value.substr(first, count);
}

t_string t_string::replace(const t_string& original, const t_string& replacement) const
{
	if (original.empty())
		return "";
		
	std::string replaced = value;
	size_t startPos = 0;

	while ((startPos = replaced.find(original, startPos)) != std::string::npos) {
		replaced.replace(startPos, original.length(), replacement);
		startPos += replacement.length();
	}

	return replaced;
}

t_string t_string::replace(const char& original, const char& replacement) const
{
	t_string replaced;

	for (auto& current : value) {
		if (current == original)
			replaced += replacement;
		else
			replaced += current;
	}

	return replaced;
}

t_string t_string::remove_all(const t_string& chars) const
{
	std::string result = value;

	for (unsigned int i = 0; i < chars.length(); i++)
		result.erase(remove(result.begin(), result.end(), chars[i]), result.end());

	return result;
}

t_string t_string::reverse() const
{
	std::string reversed = value;
	std::reverse(reversed.begin(), reversed.end());
	return reversed;
}

bool t_string::starts_with(const t_string& prefix) const
{
	return value.starts_with(prefix.s_str());
}

bool t_string::ends_with(const t_string& suffix) const
{
	return value.ends_with(suffix.s_str());
}

bool t_string::starts_and_ends_with(const t_string& prefix, const t_string& suffix) const
{
	return starts_with(prefix) && ends_with(suffix);
}

bool t_string::starts_and_ends_with(const t_string& same_preffix_and_suffix) const
{
	return starts_with(same_preffix_and_suffix) && ends_with(same_preffix_and_suffix);
}

bool t_string::contains(const t_string& other) const
{
	return value.find(other) != std::string::npos;
}

bool t_string::contains_only(const t_string& chars) const
{
	return std::all_of(value.begin(), value.end(), [&chars](char c) {
		return chars.s_str().find(c) != std::string::npos;
	});
}

bool t_string::contains_any(const t_string& chars) const
{
	return value.find_first_of(chars.s_str()) != std::string::npos;
}

bool t_string::in(const t_list<t_string>& strings) const
{
	return std::find(strings.begin(), strings.end(), value) != strings.end();
}

int t_string::index_of(const t_string& str) const
{
	return (int)value.find(str);
}

int t_string::last_index_of(const t_string& str) const
{
	return (int)value.find_last_of(str);
}

t_list<int> t_string::find_all(const char& ch, size_t offset)
{
	t_list<int> indexes;

	for (size_t i = offset; i < value.length(); i++) {
		if (value[i] == ch) {
			indexes.push_back((int)i);
		}
	}

	return indexes;
}

int t_string::count(const char& ch)
{
	return (int)find_all(ch).size();
}

t_string t_string::fmt(const char* str, ...)
{
	char output[fmt_buf_maxlen] = { 0 };

	va_list arg;
	va_start(arg, str);
	vsprintf_s(output, str, arg);
	va_end(arg);

	return output;
}

t_string t_string::from_int(int value)
{
	return std::to_string(value);
}

t_string t_string::from_int(int value, int digits)
{
	const std::string result = from_int(value);
	std::string padding = "";

	for (int i = 0; i < digits - result.length(); i++)
		padding += '0';

	return padding + result;
}

t_string t_string::from_float(float value)
{
	return std::to_string(value);
}

t_string t_string::from_bool(bool value)
{
	return value ? "true" : "false";
}

t_string t_string::to_hex(int value)
{
	return fmt("%x", value);
}

t_string t_string::to_hex(int value, int digits)
{
	const std::string hex = to_hex(value);
	std::string padding = "";

	for (int i = 0; i < digits - hex.length(); i++)
		padding += '0';

	return padding + hex;
}

t_string t_string::to_binary(int value)
{
	std::string str = "";

	while (value != 0) { 
		str = (value % 2 == 0 ? "0" : "1") + str; 
		value /= 2; 
	}

	return str;
}

t_string t_string::to_binary(int value, int digits)
{
	const std::string binary = to_binary(value);
	std::string padding = "";

	for (int i = 0; i < digits - binary.length(); i++)
		padding += '0';

	return padding + binary;
}

t_string t_string::join(const t_list<t_string>& str_list, const t_string& separator)
{
	std::string str = "";

	for (int i = 0; i < str_list.size(); i++) {
		if (!separator.empty()) {
			str += str_list[i];
			if (i < str_list.size() - 1) {
				str += separator;
			}
		}
		else {
			str += str_list[i];
		}
	}

	return str;
}

t_string t_string::repeat(const t_string& str, int count)
{
	std::string result = "";
	for (int i = 0; i < count; i++)
		result += str;

	return result;
}

char t_string::to_upper(char ch)
{
	return toupper(ch);
}

char t_string::to_lower(char ch)
{
	return tolower(ch);
}
