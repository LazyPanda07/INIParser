#include "INIParser.h"

using namespace std;

namespace utility
{
	void INIParser::parse(ifstream&& file)
	{
		string sectionName;
		string tem;

		while (getline(file, tem))
		{
			size_t isStringValue = tem.find('\"');
			string key;
			string value;

			if (isStringValue == string::npos)
			{
				tem.erase(remove_if(tem.begin(), tem.end(), [](const char& c) { return isspace(static_cast<unsigned char>(c)); }), tem.end());
			}
			else
			{
				tem.erase(remove_if(tem.begin(), tem.begin() + tem.find('\"'), [](const char& c) {return isspace(c); }), tem.begin() + tem.find('\"'));

				tem.erase(remove(tem.begin(), tem.end(), '\"'), tem.end());
			}

			if (tem.empty())
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
					sectionName = string(tem.begin() + 1, tem.end() - 1);

					break;

				default:
					key = tem.substr(0, tem.find('='));
					value = tem.substr(tem.find('=') + 1);

					{
						size_t isMap = key.find('[');

						if (isMap != string::npos)
						{
							if (key[isMap + 1] != ']')
							{
								string mapName(key.begin(), key.begin() + isMap);
								
								key.erase(key.begin(), key.begin() + isMap + 1);

								key.pop_back();

								mapData[sectionName][mapName].emplace(move(key), move(value));

								continue;
							}
							else
							{
								key.pop_back();

								key.pop_back();
							}
						}
					}

					data[sectionName].emplace(make_pair(move(key), move(value)));

					break;
				}
			}
		}
	}

	INIParser::INIParser(const filesystem::path& filePath)
	{
		if (!filesystem::exists(filePath))
		{
			throw runtime_error("Path " + filePath.string() + " doesn't exist");
		}

		this->parse(ifstream(filePath));
	}

	INIParser::INIParser(ifstream&& file)
	{
		if (!file.is_open())
		{
			throw runtime_error("File is not open");
		}

		this->parse(move(file));
	}

	const INIParser::iniStructure& INIParser::getData() const
	{
		return data;
	}

	const INIParser::iniMapStructure& INIParser::getMapData() const
	{
		return mapData;
	}

	const unordered_multimap<string, string>& INIParser::getSectionData(const string& sectionName) const
	{
		return data.at(sectionName);
	}

	const unordered_multimap<string, string>& INIParser::getSectionMapData(const string& sectionName, const string& mapName) const
	{
		return mapData.at(sectionName).at(mapName);
	}

	string INIParser::getKeyValueData(const string& sectionName, const string& keyName) const
	{
		return data.find(sectionName)->second.find(keyName)->second;
	}

	INIParser::iniMapStructureGetStruct INIParser::getKeyValueMapData(const string& sectionName, const string& mapName, const string& keyName) const
	{
		return mapData.at(sectionName).at(mapName).equal_range(keyName);
	}
}