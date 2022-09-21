#include <cctype>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Contains
{
    TEST(Contains, ReturnsFalse_WithDefaultComparer_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Contains('c');

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Contains, ReturnsFalse_WithCustomComparer_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        // Act.
        const auto actual = From(source).Contains('C', [](const int object1, const int object2){ return tolower(object1) == tolower(object2); });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Contains, ReturnsTrue_WithDefaultComparer_SourceContainsElement)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e', 'f' };

        // Act.
        const auto actual = From(source).Contains('c');

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Contains, ReturnsTrue_WithCustomComparer_SourceContainsElement)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e', 'f' };

        // Act.
        const auto actual = From(source).Contains('C', [](const int object1, const int object2){ return tolower(object1) == tolower(object2); });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Contains, ReturnsTrue_WithDefaultComparer_SourceDoesNotContainElement)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e', 'f' };

        // Act.
        const auto actual = From(source).Contains('C');

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Contains, ReturnsTrue_WithCustomComparer_SourceDoesNotContainElement)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e', 'f' };

        // Act.
        const auto actual = From(source).Contains('g', [](const int object1, const int object2){ return tolower(object1) == tolower(object2); });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Contains, ReturnsSameResults_WithDefaultComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e', 'f' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Contains('c');
        const auto actual2 = query.Contains('c');

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Contains, ReturnsSameResults_WithCustomComparer)
    {
        // Arrange.
        const int source[]{ 'a', 'b', 'c', 'd', 'e', 'f' };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Contains('C', [](const int object1, const int object2){ return tolower(object1) == tolower(object2); });
        const auto actual2 = query.Contains('C', [](const int object1, const int object2){ return tolower(object1) == tolower(object2); });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}