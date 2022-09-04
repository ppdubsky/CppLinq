#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Last, ReturnsLast_LastFromAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 10;

    const auto actual = From(source).Last();

    EXPECT_EQ(actual, expected);
}

TEST(Last, ReturnsLast_LastByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 9;

    const auto actual = From(source).Last([](const int value){ return value % 2 != 0; });

    EXPECT_EQ(actual, expected);
}

TEST(Last, ReturnsSameResults_LastFromAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Last();
    const auto actual2 = query.Last();

    EXPECT_EQ(actual1, actual2);
}

TEST(Last, ReturnsSameResults_LastByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.Last([](const int value){ return value % 2 != 0; });
    const auto actual2 = query.Last([](const int value){ return value % 2 != 0; });

    EXPECT_EQ(actual1, actual2);
}

TEST(Last, ThrowsOnLast_LastFromAll_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Last(), EmptyCollectionException);
}

TEST(Last, ThrowsOnLast_LastByPredicate_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Last([](const int value){ return value % 2 != 0; }), EmptyCollectionException);
}

TEST(Last, ThrowsOnLast_LastByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 2, 4, 6, 8, 10 };

    auto query = From(source);

    EXPECT_THROW(query.Last([](const int value){ return value % 2 != 0; }), EmptyCollectionException);
}