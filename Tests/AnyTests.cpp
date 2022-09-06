#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Any, ReturnsFalse_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;

    // Act.
    const auto actual = From(source).Any([](const int value){ return value > 0; });

    // Assert.
    EXPECT_FALSE(actual);
}

TEST(Any, ReturnsTrue_SourceContainsOnlyValidValues)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act.
    const auto actual = From(source).Any([](const int value){ return value > 0; });

    // Assert.
    EXPECT_TRUE(actual);
}

TEST(Any, ReturnsFalse_SourceContainsOnlyInvalidValues)
{
    // Arrange.
    const int source[]{ -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };

    // Act.
    const auto actual = From(source).Any([](const int value){ return value > 0; });

    // Assert.
    EXPECT_FALSE(actual);
}

TEST(Any, ReturnsTrue_SourceContainsValidAndInvalidValues)
{
    // Arrange.
    const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };

    // Act.
    const auto actual = From(source).Any([](const int value){ return value > 0; });

    // Assert.
    EXPECT_TRUE(actual);
}

TEST(Any, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Any([](const int value){ return value > 0; });
    const auto actual2 = query.Any([](const int value){ return value > 0; });

    // Assert.
    EXPECT_EQ(actual1, actual2);
}