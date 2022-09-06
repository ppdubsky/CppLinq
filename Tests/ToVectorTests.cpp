#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;

TEST(ToVector, ReturnsExpectedValues)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const int expected[]{ 2, 4, 6, 8, 10 };

    // Act.
    const auto actual = From(source)
        .Where([](const int value){ return value % 2 == 0; })
        .ToVector();

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(ToVector, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source).Where([](const int value){ return value % 2 == 0; });

    // Act.
    const auto actual1 = query.ToVector();
    const auto actual2 = query.ToVector();

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}