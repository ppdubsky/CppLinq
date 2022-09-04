#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Average, ReturnsAverage_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 5;

    const auto actual = From(source).Average();

    EXPECT_EQ(actual, expected);
}

TEST(Average, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Average();
    const auto actual2 = query.Average();

    EXPECT_EQ(actual1, actual2);
}

TEST(Average, ThrowsOnAverage_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Average(), EmptyCollectionException);
}