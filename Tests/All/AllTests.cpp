#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::All
{
    TEST(All, ReturnsTrue_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).All([](const int value){ return value > 0; });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(All, ReturnsTrue_SourceContainsOnlyValidValues)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        // Act.
        const auto actual = From(source).All([](const int value){ return value > 0; });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(All, ReturnsFalse_SourceContainsOnlyInvalidValues)
    {
        // Arrange.
        const int source[]{ -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };

        // Act.
        const auto actual = From(source).All([](const int value){ return value > 0; });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(All, ReturnsFalse_SourceContainsValidAndInvalidValues)
    {
        // Arrange.
        const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };

        // Act.
        const auto actual = From(source).All([](const int value){ return value > 0; });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(All, ReturnsSameResults)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.All([](const int value){ return value > 0; });
        const auto actual2 = query.All([](const int value){ return value > 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}