#include <sstream>
#include <unordered_set>

#include "gtest/gtest.h"

#include "INIParser.h"

static inline const std::string data = R"([UnrealEd.SimpleMap]
SimpleMapName=/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap

[EditoronlyBP]
bAllowClassAndBlueprintPinMatching=true
bReplaceBlueprintWithClass= true
bDontLoadBlueprintOutsideEditor= true
bBlueprintIsNotBlueprintType= true

[Test]
intValue=5
doubleValue=32.2
)";

TEST(INI, Parse)
{
	utility::ini::INIParser parser = std::istringstream(data);

	ASSERT_EQ(parser.getValue("UnrealEd.SimpleMap", "SimpleMapName"), "/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");

	ASSERT_EQ(parser.getValue("EditoronlyBP", "bAllowClassAndBlueprintPinMatching"), "true");
	ASSERT_EQ(parser.getValue("EditoronlyBP", "bReplaceBlueprintWithClass"), "true");
	ASSERT_EQ(parser.getValue("EditoronlyBP", "bDontLoadBlueprintOutsideEditor"), "true");
	ASSERT_EQ(parser.getValue("EditoronlyBP", "bBlueprintIsNotBlueprintType"), "true");

	ASSERT_EQ(parser.getValue("Test", "intValue"), "5");
	ASSERT_EQ(parser.getValue("Test", "doubleValue"), "32.2");
}

TEST(INI, RangeBasedForLoop)
{
	std::unordered_set<std::string> sections =
	{
		"UnrealEd.SimpleMap",
		"EditoronlyBP",
		"Test"
	};
	std::unordered_set<std::string> keys =
	{
		"SimpleMapName",
		"bAllowClassAndBlueprintPinMatching",
		"bReplaceBlueprintWithClass",
		"bDontLoadBlueprintOutsideEditor",
		"bBlueprintIsNotBlueprintType",
		"intValue",
		"doubleValue"
	};
	std::unordered_set<std::string> values =
	{
		"/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap",
		"true",
		"5",
		"32.2"
	};
	utility::ini::INIParser parser = std::istringstream(data);

	for (const auto& [sectionName, section] : parser)
	{
		ASSERT_TRUE(sections.count(sectionName));

		for (const auto& [key, value] : section)
		{
			ASSERT_TRUE(keys.count(key));

			ASSERT_TRUE(values.count(value));
		}
	}
}

TEST(INI, GetAs)
{
	utility::ini::INIParser parser = std::istringstream(data);

	ASSERT_TRUE(parser.getAs<bool>("EditoronlyBP", "bAllowClassAndBlueprintPinMatching"));
	ASSERT_TRUE(parser.getAs<bool>("Test", "doubleValue"));
	ASSERT_EQ(parser.getAs<int>("Test", "intValue"), 5);
	ASSERT_EQ(parser.getAs<double>("Test", "doubleValue"), 32.2);
	ASSERT_EQ(parser.getAs<std::string>("EditoronlyBP", "bAllowClassAndBlueprintPinMatching"), "true");
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
