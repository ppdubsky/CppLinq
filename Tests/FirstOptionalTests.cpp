#include <optional>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(FirstOptional, ReturnsEmpty_FirstFromAll_SourceIsEmpty)
{
    vector<int> source;
    optional<int> expected;

    const auto actual = From(source).FirstOptional();

    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsFirst_FirstFromAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 1;

    const auto actual = From(source).FirstOptional();

    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsEmpty_FirstByPredicate_SourceIsEmpty)
{
    vector<int> source;
    optional<int> expected;

    const auto actual = From(source).FirstOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsFirst_FirstByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 2;

    const auto actual = From(source).FirstOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsEmpty_FirstByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 3, 5, 7, 9 };
    optional<int> expected;

    const auto actual = From(source).FirstOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsSameResults_FirstFromAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.FirstOptional();
    const auto actual2 = query.FirstOptional();

    EXPECT_EQ(actual1, actual2);
}

TEST(FirstOptional, ReturnsSameResults_FirstByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.FirstOptional([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.FirstOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual1, actual2);
}