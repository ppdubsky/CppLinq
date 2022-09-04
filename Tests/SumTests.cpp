#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Sum, ReturnsSum_SourceIsEmpty)
{
    vector<int> source;
    const auto expected = 0;

    const auto actual = From(source).Sum();

    EXPECT_EQ(actual, expected);
}

TEST(Sum, ReturnsSum_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 55;

    const auto actual = From(source).Sum();

    EXPECT_EQ(actual, expected);
}

TEST(Sum, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Sum();
    const auto actual2 = query.Sum();

    EXPECT_EQ(actual1, actual2);
}