#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(LastOrDefault, ReturnsDefault_LastFromAll_SourceIsEmpty)
{
    vector<int> source;
    const int expected = 11;

    const auto actual = From(source).LastOrDefault(11);

    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsLast_LastFromAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10;

    const auto actual = From(source).LastOrDefault(11);

    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsDefault_LastByPredicate_SourceIsEmpty)
{
    vector<int> source;
    const int expected = 11;

    const auto actual = From(source).LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsLast_LastByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 9;

    const auto actual = From(source).LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsDefault_LastByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 2, 4, 6, 8, 10 };
    const int expected = 11;

    const auto actual = From(source).LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsSameResults_LastFromAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.LastOrDefault(11);
    const auto actual2 = query.LastOrDefault(11);

    EXPECT_EQ(actual1, actual2);
}

TEST(LastOrDefault, ReturnsSameResults_LastByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.LastOrDefault([](const int value){ return value % 2 != 0; }, 11);
    const auto actual2 = query.LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    EXPECT_EQ(actual1, actual2);
}