#include "library/enum_array.h"
#include <gtest/gtest.h>

namespace PS::Testing
{

enum class Test_Index
{
    First,
    Second,
    LAST
};

TEST(EnumArray, UsesLastAsTheElementCount)
{
    Library::Enum_Array<Test_Index, int> values;

    static_assert(Library::Enum_Array<Test_Index, int>::count == 2);
    EXPECT_EQ(values.size(), 2);
}

TEST(EnumArray, IsIndexedByTheEnum)
{
    Library::Enum_Array<Test_Index, int> values;

    values[Test_Index::First] = 10;
    values[Test_Index::Second] = 20;

    EXPECT_EQ(values[Test_Index::First], 10);
    EXPECT_EQ(values.at(Test_Index::Second), 20);
}

TEST(EnumArray, AtRejectsLast)
{
    Library::Enum_Array<Test_Index, int> values;

    EXPECT_THROW(values.at(Test_Index::LAST), std::out_of_range);
}

} // namespace PS::Testing