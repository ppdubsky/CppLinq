#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Count, ReturnsCount_CountAll_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    const auto expected = 0U;

    // Act.
    const auto actual = From(source).Count();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountAll_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10U;

    // Act.
    const auto actual = From(source).Count();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    const auto expected = 0U;

    // Act.
    const auto actual = From(source).Count([](const int value){ return value > 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceContainsOnlyValidValues)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10U;

    // Act.
    const auto actual = From(source).Count([](const int value){ return value > 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceContainsOnlyInvalidValues)
{
    // Arrange.
    const int source[]{ -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    const auto expected = 0U;

    // Act.
    const auto actual = From(source).Count([](const int value){ return value > 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsCount_CountByPredicate_SourceContainsValidAndInvalidValues)
{
    // Arrange.
    const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
    const auto expected = 5U;

    // Act.
    const auto actual = From(source).Count([](const int value){ return value > 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Count, ReturnsSameResults_CountAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.Count();
    const auto actual2 = query.Count();

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(Count, ReturnsSameResults_CountByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.Count([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.Count([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual1, actual2);
}