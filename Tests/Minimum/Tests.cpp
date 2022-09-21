#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Minimum
{
    TEST(Minimum, ReturnsMinimum_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
        const auto expected = -10;

        // Act.
        const auto actual = From(source).Minimum();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Minimum, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Minimum();
        const auto actual2 = query.Minimum();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Minimum, ThrowsOnMinimum_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.Minimum(), EmptyContainerException);
    }
}