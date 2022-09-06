#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(LastOrDefault, ReturnsDefault_LastFromAll_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    const int expected = 11;

    // Act.
    const auto actual = From(source).LastOrDefault(11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsLast_LastFromAll_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10;

    // Act.
    const auto actual = From(source).LastOrDefault(11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsDefault_LastByPredicate_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    const int expected = 11;

    // Act.
    const auto actual = From(source).LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsLast_LastByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 9;

    // Act.
    const auto actual = From(source).LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsDefault_LastByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 2, 4, 6, 8, 10 };
    const int expected = 11;

    // Act.
    const auto actual = From(source).LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOrDefault, ReturnsSameResults_LastFromAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.LastOrDefault(11);
    const auto actual2 = query.LastOrDefault(11);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(LastOrDefault, ReturnsSameResults_LastByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.LastOrDefault([](const int value){ return value % 2 != 0; }, 11);
    const auto actual2 = query.LastOrDefault([](const int value){ return value % 2 != 0; }, 11);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}