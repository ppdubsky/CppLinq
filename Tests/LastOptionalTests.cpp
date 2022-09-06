#include <optional>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(LastOptional, ReturnsEmpty_LastFromAll_SourceIsEmpty)
{
    vector<int> source;
    optional<int> expected;

    const auto actual = From(source).LastOptional();

    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsLast_LastFromAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10;

    const auto actual = From(source).LastOptional();

    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsEmpty_LastByPredicate_SourceIsEmpty)
{
    vector<int> source;
    optional<int> expected;

    const auto actual = From(source).LastOptional([](const int value){ return value % 2 != 0; });

    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsLast_LastByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 9;

    const auto actual = From(source).LastOptional([](const int value){ return value % 2 != 0; });

    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsEmpty_LastByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 2, 4, 6, 8, 10 };
    optional<int> expected;

    const auto actual = From(source).LastOptional([](const int value){ return value % 2 != 0; });

    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsSameResults_LastFromAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.LastOptional();
    const auto actual2 = query.LastOptional();

    EXPECT_EQ(actual1, actual2);
}

TEST(LastOptional, ReturnsSameResults_LastByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.LastOptional([](const int value){ return value % 2 != 0; });
    const auto actual2 = query.LastOptional([](const int value){ return value % 2 != 0; });

    EXPECT_EQ(actual1, actual2);
}