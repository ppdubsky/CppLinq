#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Any, ReturnsFalse_SourceIsEmpty)
{
    vector<int> source;

    const auto actual = From(source).Any([](const int value){ return value > 0; });

    EXPECT_FALSE(actual);
}

TEST(Any, ReturnsTrue_SourceContainsOnlyValidValues)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    const auto actual = From(source).Any([](const int value){ return value > 0; });

    EXPECT_TRUE(actual);
}

TEST(Any, ReturnsFalse_SourceContainsOnlyInvalidValues)
{
    const int source[]{ -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };

    const auto actual = From(source).Any([](const int value){ return value > 0; });

    EXPECT_FALSE(actual);
}

TEST(Any, ReturnsTrue_SourceContainsValidAndInvalidValues)
{
    const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };

    const auto actual = From(source).Any([](const int value){ return value > 0; });

    EXPECT_TRUE(actual);
}

TEST(Any, ReturnsSameResults)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Any([](const int value){ return value > 0; });
    const auto actual2 = query.Any([](const int value){ return value > 0; });

    EXPECT_EQ(actual1, actual2);
}