#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#include <string_view>

namespace utility
{
	class INIParser
	{
	public:
		using iniStructure = std::unordered_map<std::string, std::unordered_multimap<std::string, std::string>>;	//section name - key(name=value)
		using iniMapStructure = std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_multimap<std::string, std::string>>>;	//section name - map of maps
		using iniMapStructureGetStruct = std::pair<std::unordered_map<std::string, std::string>::const_iterator, std::unordered_map<std::string, std::string>::const_iterator>;	//std::unordered_multimap.equal_range()

	private:
		iniStructure data;
		iniMapStructure mapData;

	private:
		void parse(std::ifstream&& file);

	public:
		INIParser(const std::string_view& fileName);

		INIParser(const std::filesystem::path& fileName);

		INIParser(std::ifstream&& file) noexcept;

		const iniStructure& getData() const;

		const iniMapStructure& getMapData() const;

		const std::unordered_multimap<std::string, std::string>& getSectionData(const std::string& sectionName) const;

		const std::unordered_multimap<std::string, std::string>& getSectionMapData(const std::string& sectionName, const std::string& mapName) const;

		std::string getKeyValueData(const std::string& sectionName, const std::string& keyName) const;

		iniMapStructureGetStruct getKeyValueMapData(const std::string& sectionName, const std::string& mapName, const std::string& keyName) const;

		INIParser() = default;
	};
}