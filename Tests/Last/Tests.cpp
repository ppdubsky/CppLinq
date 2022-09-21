#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Last
{
    TEST(Last, ReturnsLast_LastFromAll_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 10;

        // Act.
        const auto actual = From(source).Last();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Last, ReturnsLast_LastByPredicate_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const auto expected = 9;

        // Act.
        const auto actual = From(source).Last([](const int value){ return value % 2 != 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Last, ReturnsSameResults_LastFromAll)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Last();
        const auto actual2 = query.Last();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Last, ReturnsSameResults_LastByPredicate)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Last([](const int value){ return value % 2 != 0; });
        const auto actual2 = query.Last([](const int value){ return value % 2 != 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(Last, ThrowsOnLast_LastFromAll_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.Last(), EmptyContainerException);
    }

    TEST(Last, ThrowsOnLast_LastByPredicate_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.Last([](const int value){ return value % 2 != 0; }), EmptyContainerException);
    }

    TEST(Last, ThrowsOnLast_LastByPredicate_SourceIsNotEmpty)
    {
        // Arrange.
        const int source[]{ 2, 4, 6, 8, 10 };

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.Last([](const int value){ return value % 2 != 0; }), EmptyContainerException);
    }
}