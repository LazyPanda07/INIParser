#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>

#ifdef INI_PARSER_DLL
#ifdef __LINUX__
#define INI_PARSER_API __attribute__((visibility("default")))
#else
#define INI_PARSER_API __declspec(dllexport)
#endif
#else
#define INI_PARSER_API
#endif

namespace utility
{
	class INI_PARSER_API INIParser
	{
	public:
		/**
		* section name - (key - value)
		*/
		using iniStructure = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

	private:
		iniStructure data;

	private:
		void parse(std::istream&& stream);

	public:
		/**
		 * @brief Get version on INIParser
		 */
		static std::string getVersion();

	public:
		/**
		* @brief Parse .ini file from path
		* @param filePath Path to .ini file
		* @exception std::runtime_error
		*/
		INIParser(const std::filesystem::path& filePath);

		/**
		* @brief Parse from std::istream
		* @param inputStream Input stream
		* @exception std::runtime_error
		*/
		INIParser(std::istream&& inputStream);

		/**
		* @brief Get value from specific section by key
		* @exception std::out_of_range
		*/
		const std::string& getValue(const std::string& sectionName, const std::string& key) const;

		/**
		* @brief Get section by name
		* @exception std::out_of_range
		*/
		const std::unordered_map<std::string, std::string>& operator[](const std::string& sectionName) const;

		/**
		* @brief Range-based for loop
		*/
		iniStructure::const_iterator begin() const noexcept;

		/**
		* @brief Range-based for loop
		*/
		iniStructure::const_iterator end() const noexcept;

		INIParser() = default;
	};
}