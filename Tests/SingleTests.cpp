#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Single, ReturnsSingle_SingleFromAll_SourceContainsSingleElement)
{
    // Arrange.
    const int source[]{ 1 };
    const auto expected = 1;

    // Act.
    const auto actual = From(source).Single();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Single, ReturnsSingle_SingleByPredicate_SourceContainsSingleElement)
{
    // Arrange.
    const int source[]{ 1, 2, 3 };
    const auto expected = 2;

    // Act.
    const auto actual = From(source).Single([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Single, ReturnsSameResults_SingleFromAll)
{
    // Arrange.
    const int source[]{ 1 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.Single();
    const auto actual2 = query.Single();

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(Single, ReturnsSameResults_SingleByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.Single([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.Single([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(Single, ThrowsOnSingle_SingleFromAll_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;

    auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Single(), EmptyCollectionException);
}

TEST(Single, ThrowsOnSingle_SingleFromAll_SourceContainsMoreThanOneElement)
{
    // Arrange.
    const int source[]{ 1, 2 };

    auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Single(), MoreThanOneElementException);
}

TEST(Single, ThrowsOnSingle_SingleByPredicate_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;

    auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Single([](const int value){ return value % 2 == 0; }), EmptyCollectionException);
}

TEST(Single, ThrowsOnSingle_SingleByPredicate_SourceContainsSingleElementThatDoesNotSatisfyPredicate)
{
    // Arrange.
    const int source[]{ 1 };

    auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Single([](const int value){ return value % 2 == 0; }), EmptyCollectionException);
}

TEST(Single, ThrowsOnSingle_SingleByPredicate_SourceContainsMultipleElementsThatSatisfyPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5 };

    auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Single([](const int value){ return value % 2 == 0; }), MoreThanOneElementException);
}