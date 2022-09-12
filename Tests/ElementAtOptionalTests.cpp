#include <optional>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(ElementAtOptional, ReturnsEmpty_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const optional<int> expected;

    // Act.
    const auto actual = From(source).ElementAtOptional(0U);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(ElementAtOptional, ReturnsElement_SourceIsNotEmpty_IndexIsValid)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 4;

    // Act.
    const auto actual = From(source).ElementAtOptional(3U);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(ElementAtOptional, ReturnsElement_SourceIsNotEmpty_IndexIsNotValid)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const optional<int> expected;

    // Act.
    const auto actual = From(source).ElementAtOptional(10U);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(ElementAtOptional, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.ElementAtOptional(3U);
    const auto actual2 = query.ElementAtOptional(3U);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}