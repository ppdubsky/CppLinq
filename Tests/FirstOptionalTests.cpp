#include <optional>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(FirstOptional, ReturnsEmpty_FirstFromAll_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const optional<int> expected;

    // Act.
    const auto actual = From(source).FirstOptional();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsFirst_FirstFromAll_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 1;

    // Act.
    const auto actual = From(source).FirstOptional();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsEmpty_FirstByPredicate_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;
    const optional<int> expected;

    // Act.
    const auto actual = From(source).FirstOptional([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsFirst_FirstByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 2;

    // Act.
    const auto actual = From(source).FirstOptional([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsEmpty_FirstByPredicate_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 3, 5, 7, 9 };
    const optional<int> expected;

    // Act.
    const auto actual = From(source).FirstOptional([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(FirstOptional, ReturnsSameResults_FirstFromAll)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.FirstOptional();
    const auto actual2 = query.FirstOptional();

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(FirstOptional, ReturnsSameResults_FirstByPredicate)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.FirstOptional([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.FirstOptional([](const int value){ return value % 2 == 0; });

    // Assert.
    EXPECT_EQ(actual1, actual2);
}