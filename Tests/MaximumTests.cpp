#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Maximum, ReturnsMaximum_SourceIsNotEmpty)
{
    const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
    const auto expected = 9;

    const auto actual = From(source).Maximum();

    EXPECT_EQ(actual, expected);
}

TEST(Maximum, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Maximum();
    const auto actual2 = query.Maximum();

    EXPECT_EQ(actual1, actual2);
}

TEST(Maximum, ThrowsOnMaximum_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Maximum(), EmptyCollectionException);
}