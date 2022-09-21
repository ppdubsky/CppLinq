#include <optional>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::SingleOptional
{
    TEST(SingleOptional, ReturnsEmpty_SingleFromAll_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const optional<int> expected;

        // Act.
        const auto actual = From(source).SingleOptional();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(SingleOptional, ReturnsSingle_SingleFromAll_SourceContainsSingleElement)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = 1;

        // Act.
        const auto actual = From(source).SingleOptional();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(SingleOptional, ReturnsEmpty_SingleByPredicate_SourceIsEmpty)
    {
        // Arrange.
        const vector<int> source;
        const optional<int> expected;

        // Act.
        const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(SingleOptional, ReturnsEmpty_SingleByPredicate_SourceContainsSingleElementThatDoesNotSatisfyPredicate)
    {
        // Arrange.
        const int source[]{ 1 };
        const optional<int> expected;

        // Act.
        const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(SingleOptional, ReturnsSingle_SingleByPredicate_SourceContainsSingleElement)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };
        const auto expected = 2;

        // Act.
        const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(SingleOptional, ReturnsSameResults_SingleFromAll)
    {
        // Arrange.
        const int source[]{ 1 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SingleOptional();
        const auto actual2 = query.SingleOptional();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(SingleOptional, ReturnsSameResults_SingleByPredicate)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.SingleOptional([](const int value){ return value % 2 == 0; });
        const auto actual2 = query.SingleOptional([](const int value){ return value % 2 == 0; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(SingleOptional, ThrowsOnSingleOptional_SingleFromAll_SourceContainsMoreThanOneElement)
    {
        // Arrange.
        const int source[]{ 1, 2 };

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.SingleOptional(), MoreThanOneElementException);
    }

    TEST(SingleOptional, ThrowsOnSingleOptional_SingleByPredicate_SourceContainsMultipleElementsThatSatisfyPredicate)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.SingleOptional([](const int value){ return value % 2 == 0; }), MoreThanOneElementException);
    }
}