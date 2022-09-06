#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(FirstOrDefault, ReturnsDefault_FirstFromAll_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    const int expected = 11;

    // Act.
    const auto actual = From(source).FirstOrDefault(11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsFirst_FirstFromAll_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 1;

    // Act.
    const auto actual = From(source).FirstOrDefault(11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsDefault_FirstByPredicate_SourceIsEmpty)
{
    // Arrange.
    vector<int> source;
    const int expected = 11;

    // Act.
    const auto actual = From(source).FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsFirst_FirstByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 2;

    // Act.
    const auto actual = From(source).FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsDefault_FirstByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 3, 5, 7, 9 };
    const int expected = 11;

    // Act.
    const auto actual = From(source).FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsSameResults_FirstFromAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.FirstOrDefault(11);
    const auto actual2 = query.FirstOrDefault(11);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(FirstOrDefault, ReturnsSameResults_FirstByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    // Act.
    const auto actual1 = query.FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);
    const auto actual2 = query.FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    // Assert.
    EXPECT_EQ(actual1, actual2);
}