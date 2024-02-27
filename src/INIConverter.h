#include <concepts>
#include <string>
#include <cctype>
#include <algorithm>
#include <string_view>

namespace utility
{
    namespace ini
    {
        template<typename T, typename ResultT>
        concept INIConverter = 
            std::default_initializable<T> &&
            std::convertible_to<decltype(T().convert(std::string())), ResultT>;

        template<typename T>
        struct DefaultINIConverter;

        template<>
        struct DefaultINIConverter<bool>
        {
            inline bool convert(const std::string& value) const
            {
                using namespace std::string_view_literals;

                static constexpr size_t trueSize = 4;
                static constexpr size_t falseSize = 5;
                auto trueFalseEqual = [](std::string_view left, std::string_view right) -> bool
                {
                    return std::ranges::equal
                    (
                        left,
                        right,
                        [](char leftChar, char rightChar)
                        { 
                            return std::tolower(static_cast<uint8_t>(leftChar)) == std::tolower(static_cast<uint8_t>(rightChar));
                        }
                    );
                };
                auto defaultConvert = [&value]() -> bool
                {
                    return static_cast<bool>(std::stod(value));
                };

                switch(value.size())
                {
                case trueSize:
                    return trueFalseEqual(value, "true"sv) ? true : defaultConvert();
                
                case falseSize:
                    return trueFalseEqual(value, "false"sv) ? false : defaultConvert();

                default:
                    return defaultConvert();
                }
            }
        };

        template<>
        struct DefaultINIConverter<int>
        {
            inline int convert(const std::string& value) const
            {
                return std::stoi(value);
            }
        };

        template<>
        struct DefaultINIConverter<int64_t>
        {
            inline int64_t convert(const std::string& value) const
            {
                return std::stoll(value);
            }
        };

        template<>
        struct DefaultINIConverter<std::string>
        {
            inline std::string convert(const std::string& value) const
            {
                return value;
            }
        };

        template<>
        struct DefaultINIConverter<double>
        {
            inline double convert(const std::string& value) const
            {
                return std::stod(value);
            }
        };
    }
}
