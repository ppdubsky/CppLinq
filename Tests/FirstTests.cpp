#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(First, ReturnsFirst_FirstFromAll_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 1;

    // Act.
    const auto actual = From(source).First();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(First, ReturnsFirst_FirstByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 2;

    // Act.
    const auto actual = From(source).First([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(First, ReturnsSameResults_FirstFromAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.First();
    const auto actual2 = query.First();

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(First, ReturnsSameResults_FirstByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.First([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.First([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(First, ThrowsOnFirst_FirstFromAll_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;

    const auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.First(), EmptyContainerException);
}

TEST(First, ThrowsOnFirst_FirstByPredicate_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;

    const auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.First([](const int value){ return value % 2 == 0; }), EmptyContainerException);
}

TEST(First, ThrowsOnFirst_FirstByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 3, 5, 7, 9 };

    const auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.First([](const int value){ return value % 2 == 0; }), EmptyContainerException);
}