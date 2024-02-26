#include <sstream>

#include "gtest/gtest.h"

#include "INIParser.h"

TEST(INI, Parse)
{
    std::string data = R"([UnrealEd.SimpleMap]
SimpleMapName=/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap

[EditoronlyBP]
bAllowClassAndBlueprintPinMatching=true
bReplaceBlueprintWithClass= true
bDontLoadBlueprintOutsideEditor= true
bBlueprintIsNotBlueprintType= true
)";

    utility::INIParser parser = std::istringstream(data);

    ASSERT_EQ(parser.getValue("UnrealEd.SimpleMap", "SimpleMapName"), "/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");

    ASSERT_EQ(parser.getValue("EditoronlyBP", "bAllowClassAndBlueprintPinMatching"), "true");
    ASSERT_EQ(parser.getValue("EditoronlyBP", "bReplaceBlueprintWithClass"), "true");
    ASSERT_EQ(parser.getValue("EditoronlyBP", "bDontLoadBlueprintOutsideEditor"), "true");
    ASSERT_EQ(parser.getValue("EditoronlyBP", "bBlueprintIsNotBlueprintType"), "true");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
