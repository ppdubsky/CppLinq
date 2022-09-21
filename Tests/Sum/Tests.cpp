#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Sum
{
    TEST(Sum, ReturnsSum_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = 0;

        // Act.
        const auto actual = From(source).Sum();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Sum, ReturnsSum_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 55;

        // Act.
        const auto actual = From(source).Sum();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Sum, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Sum();
        const auto actual2 = query.Sum();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}