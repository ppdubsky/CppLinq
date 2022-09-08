#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Average, ReturnsAverage_SourceIsNotEmpty)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 5;

    // Act.
    const auto actual = From(source).Average();

    // Assert.
    EXPECT_EQ(actual, expected);
}

TEST(Average, ReturnsSameResults)
{
    // Arrange.
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto query = From(source);

    // Act.
    const auto actual1 = query.Average();
    const auto actual2 = query.Average();

    // Assert.
    EXPECT_EQ(actual1, actual2);
}

TEST(Average, ThrowsOnAverage_SourceIsEmpty)
{
    // Arrange.
    const vector<int> source;

    const auto query = From(source);

    // Act.
    // Assert.
    EXPECT_THROW(query.Average(), EmptyContainerException);
}