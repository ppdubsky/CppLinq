#include <optional>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(LastOptional, ReturnsEmpty_LastFromAll_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    optional<int> expected;

    // Act.
    const auto actual = From(source).LastOptional();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsLast_LastFromAll_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10;

    // Act.
    const auto actual = From(source).LastOptional();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsEmpty_LastByPredicate_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    optional<int> expected;

    // Act.
    const auto actual = From(source).LastOptional([](const int value){ return value % 2 != 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsLast_LastByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 9;

    // Act.
    const auto actual = From(source).LastOptional([](const int value){ return value % 2 != 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsEmpty_LastByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 2, 4, 6, 8, 10 };
    optional<int> expected;

    // Act.
    const auto actual = From(source).LastOptional([](const int value){ return value % 2 != 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(LastOptional, ReturnsSameResults_LastFromAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.LastOptional();
    const auto actual2 = query.LastOptional();

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(LastOptional, ReturnsSameResults_LastByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.LastOptional([](const int value){ return value % 2 != 0; });
    const auto actual2 = query.LastOptional([](const int value){ return value % 2 != 0; });

    // Assert.
    EXPECT_EQ(actual1, actual2);
}