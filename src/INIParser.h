#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>

namespace utility
{
	class INIParser
	{
	public:
		// section name - key(name=value)
		using iniStructure = std::unordered_map<std::string, std::unordered_multimap<std::string, std::string>>;

		// section name - map of maps
		using iniMapStructure = std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_multimap<std::string, std::string>>>;

		// std::unordered_multimap.equal_range()
		using iniMapStructureGetStruct = std::pair<std::unordered_map<std::string, std::string>::const_iterator, std::unordered_map<std::string, std::string>::const_iterator>;

	private:
		iniStructure data;
		iniMapStructure mapData;

	private:
		void parse(std::ifstream&& file);

	public:
		/// @brief Parse .ini file from path
		/// @param filePath Path to .ini file
		/// @exception std::runtime_error
		INIParser(const std::filesystem::path& filePath);

		/// @brief Parse .ini file from std::ifstream
		/// @param file File input streams
		/// @exception std::runtime_error
		INIParser(std::ifstream&& file);

		const iniStructure& getData() const;

		const iniMapStructure& getMapData() const;

		const std::unordered_multimap<std::string, std::string>& getSectionData(const std::string& sectionName) const;

		const std::unordered_multimap<std::string, std::string>& getSectionMapData(const std::string& sectionName, const std::string& mapName) const;

		std::string getKeyValueData(const std::string& sectionName, const std::string& keyName) const;

		iniMapStructureGetStruct getKeyValueMapData(const std::string& sectionName, const std::string& mapName, const std::string& keyName) const;

		INIParser() = default;
	};
}