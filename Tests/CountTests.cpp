#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Count, ReturnsCount_CountAll_SourceIsEmpty)
{
    vector<int> source;
    const auto expected = 0U;

    const auto actual = From(source).Count();

    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10U;

    const auto actual = From(source).Count();

    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceIsEmpty)
{
    vector<int> source;
    const auto expected = 0U;

    const auto actual = From(source).Count([](const int value){ return value > 0; });

    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceContainsOnlyValidValues)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10U;

    const auto actual = From(source).Count([](const int value){ return value > 0; });

    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceContainsOnlyInvalidValues)
{
    const int source[]{ -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    const auto expected = 0U;

    const auto actual = From(source).Count([](const int value){ return value > 0; });

    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceContainsValidAndInvalidValues)
{
    const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
    const auto expected = 5U;

    const auto actual = From(source).Count([](const int value){ return value > 0; });

    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsSameResults_CountAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Count();
    const auto actual2 = query.Count();

    EXPECT_EQ(actual1, actual2);
}

TEST(Count, ReturnsSameResults_CountByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Count([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.Count([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual1, actual2);
}