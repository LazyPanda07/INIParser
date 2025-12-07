#include "INIParser.h"

namespace utility::ini
{
	void INIParser::parse(std::istream&& stream)
	{
		std::string temp;
		std::unordered_map<std::string, std::string>* currentSection = nullptr;
		auto removeSpaces = [](std::string& source)
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

		while (std::getline(stream, temp))
		{
			if (temp.empty())
			{
				continue;
			}
			else if (temp[0] == '[')
			{
				currentSection = &data[std::string(temp.begin() + 1, temp.end() - 1)];

				continue;
			}
			else if (temp[0] == ';' || temp[0] == '#')
			{
				continue;
			}

			std::string key;
			std::string value;
			std::string* current = &key;

			for (char c : temp)
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
				throw std::runtime_error("No section");
			}

			currentSection->try_emplace(move(key), move(value));
		}
	}

	std::string INIParser::getVersion()
	{
		std::string version = "1.2.1";

		return version;
	}

	INIParser::INIParser(const std::filesystem::path& filePath)
	{
		if (!std::filesystem::exists(filePath))
		{
			throw std::runtime_error("Path " + filePath.string() + " doesn't exist");
		}

		this->parse(std::ifstream(filePath));
	}

	INIParser::INIParser(std::istream&& inputStream)
	{
		if (inputStream.bad())
		{
			throw std::runtime_error("Bad stream");
		}

		this->parse(std::move(inputStream));
	}

	const std::string& INIParser::getValue(const std::string& sectionName, const std::string& key) const
	{
		return data.at(sectionName).at(key);
	}

	const std::unordered_map<std::string, std::string>& INIParser::operator [](const std::string& sectionName) const
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
