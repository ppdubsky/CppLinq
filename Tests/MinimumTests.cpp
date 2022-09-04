#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Minimum, ReturnsMinimum_SourceIsNotEmpty)
{
    const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
    const auto expected = -10;

    const auto actual = From(source).Minimum();

    EXPECT_EQ(actual, expected);
}

TEST(Minimum, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Minimum();
    const auto actual2 = query.Minimum();

    EXPECT_EQ(actual1, actual2);
}

TEST(Minimum, ThrowsOnMinimum_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Minimum(), EmptyCollectionException);
}