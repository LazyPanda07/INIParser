#include "INIParser.h"

using namespace std;

namespace utility
{
	void INIParser::parse(ifstream&& file)
	{
		string sectionName;

		while (!file.eof())
		{
			string tem;

			getline(file, tem);

			if (tem == "")
			{
				continue;
			}
			else
			{
				switch (tem[0])
				{
				case ';':
				case '#':
					continue;

					break;

				case '[':
					sectionName = string(begin(tem) + 1, end(tem) - 1);

					break;

				default:
					data[sectionName].emplace(make_pair(tem.substr(0, tem.find('=')), tem.substr(tem.find('=') + 1)));

					break;
				}
			}
		}
	}

	INIParser::INIParser(const string_view& fileName)
	{
		this->parse(ifstream(fileName));
	}

	INIParser::INIParser(const filesystem::path& fileName)
	{
		this->parse(ifstream(fileName));
	}

	INIParser::INIParser(ifstream&& file) noexcept
	{
		this->parse(move(file));
	}

	const INIParser::iniStructure& INIParser::get() const
	{
		return data;
	}

	const unordered_multimap<string, string>& INIParser::getSection(const string& sectionName) const
	{
		return data.find(sectionName)->second;
	}

	string INIParser::getKeyValue(const string& sectionName, const string& keyName) const
	{
		return data.find(sectionName)->second.find(keyName)->second;
	}
}