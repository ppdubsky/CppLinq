#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(First, ReturnsFirst_FirstFromAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 1;

    const auto actual = From(source).First();

    EXPECT_EQ(actual, expected);
}

TEST(First, ReturnsFirst_FirstByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 2;

    const auto actual = From(source).First([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(First, ReturnsSameResults_FirstFromAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.First();
    const auto actual2 = query.First();

    EXPECT_EQ(actual1, actual2);
}

TEST(First, ReturnsSameResults_FirstByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.First([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.First([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual1, actual2);
}

TEST(First, ThrowsOnFirst_FirstFromAll_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.First(), EmptyCollectionException);
}

TEST(First, ThrowsOnFirst_FirstByPredicate_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.First([](const int value){ return value % 2 == 0; }), EmptyCollectionException);
}

TEST(First, ThrowsOnFirst_FirstByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 3, 5, 7, 9 };

    auto query = From(source);

    EXPECT_THROW(query.First([](const int value){ return value % 2 == 0; }), EmptyCollectionException);
}