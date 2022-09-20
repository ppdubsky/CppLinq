#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::ElementAt
{
    TEST(ElementAt, ReturnsElement_SourceIsNotEmpty_IndexIsValid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 4;

        // Act.
        const auto actual = From(source).ElementAt(3U);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(ElementAt, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ElementAt(3U);
        const auto actual2 = query.ElementAt(3U);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(ElementAt, ThrowsOnElement_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.ElementAt(0U), EmptyContainerException);
    }

    TEST(ElementAt, ThrowsOnElement_SourceIsNotEmpty_IndexIsNotValid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.ElementAt(10U), EmptyContainerException);
    }
}