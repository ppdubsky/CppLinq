#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::ElementAtOrDefault
{
    TEST(ElementAtOrDefault, ReturnsDefault_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const int expected = 11;

        // Act.
        const auto actual = From(source).ElementAtOrDefault(0U, 11);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(ElementAtOrDefault, ReturnsElement_SourceIsNotEmpty_IndexIsValid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 4;

        // Act.
        const auto actual = From(source).ElementAtOrDefault(3U, 11);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(ElementAtOrDefault, ReturnsElement_SourceIsNotEmpty_IndexIsNotValid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected = 11;

        // Act.
        const auto actual = From(source).ElementAtOrDefault(10U, 11);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(ElementAtOrDefault, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ElementAtOrDefault(3U, 11);
        const auto actual2 = query.ElementAtOrDefault(3U, 11);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}