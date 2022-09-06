#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(SingleOrDefault, ReturnsDefault_SingleFromAll_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const int expected = 11;

    // Act.
    const auto actual = From(source).SingleOrDefault(11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(SingleOrDefault, ReturnsSingle_SingleFromAll_SourceContainsSingleElement)
{
    // Arrange.
    const int source[]{ 1 };
    const auto expected = 1;

    // Act.
    const auto actual = From(source).SingleOrDefault(11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(SingleOrDefault, ReturnsDefault_SingleByPredicate_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const int expected = 11;

    // Act.
    const auto actual = From(source).SingleOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(SingleOrDefault, ReturnsDefault_SingleByPredicate_SourceContainsSingleElementThatDoesNotSatisfyPredicate)
{
    // Arrange.
    const int source[]{ 1 };
    const int expected = 11;

    // Act.
    const auto actual = From(source).SingleOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(SingleOrDefault, ReturnsSingle_SingleByPredicate_SourceContainsSingleElement)
{
    // Arrange.
    const int source[]{ 1, 2, 3 };
    const auto expected = 2;

    // Act.
    const auto actual = From(source).SingleOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(SingleOrDefault, ReturnsSameResults_SingleFromAll)
{
    // Arrange.
    const int source[]{ 1 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.SingleOrDefault(11);
    const auto actual2 = query.SingleOrDefault(11);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(SingleOrDefault, ReturnsSameResults_SingleByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.SingleOrDefault([](const int value){ return value % 2 == 0; }, 11);
    const auto actual2 = query.SingleOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(SingleOrDefault, ThrowsOnSingleOrDefault_SingleFromAll_SourceContainsMoreThanOneElement)
{
    // Arrange.
    const int source[]{ 1, 2 };

    const auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.SingleOrDefault(11), MoreThanOneElementException);
}

TEST(SingleOrDefault, ThrowsOnSingleOrDefault_SingleByPredicate_SourceContainsMultipleElementsThatSatisfyPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5 };

    const auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.SingleOrDefault([](const int value){ return value % 2 == 0; }, 11), MoreThanOneElementException);
}