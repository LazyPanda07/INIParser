#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>

#include "INIConverter.h"

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
	namespace ini
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

#if defined(__cpp_concepts) && __cpp_concepts
			template<typename ResultT, typename T = DefaultINIConverter<ResultT>>
			ResultT getAs(const std::string& sectionName, const std::string& key) const requires(INIConverter<T, ResultT>);
#endif

			INIParser() = default;
		};
	}
}

#if defined(__cpp_concepts) && __cpp_concepts
namespace utility
{
	namespace ini
	{
		template<typename ResultT, typename T>
		ResultT INIParser::getAs(const std::string& sectionName, const std::string& key) const requires(INIConverter<T, ResultT>)
		{
			return static_cast<ResultT>(T().convert(this->getValue(sectionName, key)));
		}
	}
}
#endif
