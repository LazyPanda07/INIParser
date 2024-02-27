#include "INIParser.h"

using namespace std;

namespace utility
{
	void INIParser::parse(istream&& stream)
	{
		string tem;
		unordered_map<string, string>* currentSection = nullptr;
		auto removeSpaces = [](string& source)
		{
			size_t spaces = 0;

			for (char c : source)
			{
				if (isspace(c))
				{
					spaces++;
				}
				else
				{
					break;
				}
			}

			source.erase(0, spaces);

			while (isspace(source.back()))
			{
				source.pop_back();
			}
		};

		while (getline(stream, tem))
		{
			if (tem.empty())
			{
				continue;
			}
			else if (tem[0] == '[')
			{
				currentSection = &data[string(tem.begin() + 1, tem.end() - 1)];
				
				continue;
			}
			else if (tem[0] == ';' || tem[0] == '#')
			{
				continue;
			}

			string key;
			string value;
			string* current = &key;

			for (char c : tem)
			{
				if (c == '=')
				{
					if (current != &value)
					{
						current = &value;

						continue;
					}
				}

				*current += c;
			}

			removeSpaces(key);
			removeSpaces(value);

			if (!currentSection)
			{
				throw runtime_error("No section");
			}

			currentSection->emplace(move(key), move(value));
		}
	}

	string INIParser::getVersion()
	{
		string version = "1.0.0";

		return version;
	}

	INIParser::INIParser(const filesystem::path& filePath)
	{
		if (!filesystem::exists(filePath))
		{
			throw runtime_error("Path " + filePath.string() + " doesn't exist");
		}

		this->parse(ifstream(filePath));
	}

	INIParser::INIParser(istream&& inputStream)
	{
		if (inputStream.bad())
		{
			throw runtime_error("Bad stream");
		}

		this->parse(move(inputStream));
	}

	const string& INIParser::getValue(const string& sectionName, const string& key) const
	{
		return data.at(sectionName).at(key);
	}

	const unordered_map<string, string>& INIParser::operator[](const string& sectionName) const
	{
		return data.at(sectionName);
	}

	INIParser::iniStructure::const_iterator INIParser::begin() const noexcept
	{
		return data.begin();
	}

	INIParser::iniStructure::const_iterator INIParser::end() const noexcept
	{
		return data.end();
	}
}
