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
)";

TEST(INI, Parse)
{
	utility::INIParser parser = std::istringstream(data);

	ASSERT_EQ(parser.getValue("UnrealEd.SimpleMap", "SimpleMapName"), "/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");

	ASSERT_EQ(parser.getValue("EditoronlyBP", "bAllowClassAndBlueprintPinMatching"), "true");
	ASSERT_EQ(parser.getValue("EditoronlyBP", "bReplaceBlueprintWithClass"), "true");
	ASSERT_EQ(parser.getValue("EditoronlyBP", "bDontLoadBlueprintOutsideEditor"), "true");
	ASSERT_EQ(parser.getValue("EditoronlyBP", "bBlueprintIsNotBlueprintType"), "true");
}

TEST(INI, ForBasedRangeLoop)
{
	std::unordered_set<std::string> sections =
	{
		"UnrealEd.SimpleMap",
		"EditoronlyBP"
	};
	std::unordered_set<std::string> keys =
	{
		"SimpleMapName",
		"bAllowClassAndBlueprintPinMatching",
		"bReplaceBlueprintWithClass",
		"bDontLoadBlueprintOutsideEditor",
		"bBlueprintIsNotBlueprintType"
	};
	std::unordered_set<std::string> values =
	{
		"/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap",
		"true"
	};
	utility::INIParser parser = std::istringstream(data);

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

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
