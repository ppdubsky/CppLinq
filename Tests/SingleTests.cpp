#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Single, ReturnsSingle_SingleFromAll_SourceContainsSingleElement)
{
    const int source[]{ 1 };
    const auto expected = 1;

    const auto actual = From(source).Single();

    EXPECT_EQ(actual, expected);
}

TEST(Single, ReturnsSingle_SingleByPredicate_SourceContainsSingleElement)
{
    const int source[]{ 1, 2, 3 };
    const auto expected = 2;

    const auto actual = From(source).Single([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(Single, ReturnsSameResults_SingleFromAll)
{
    const int source[]{ 1 };

    auto query = From(source);

    const auto actual1 = query.Single();
    const auto actual2 = query.Single();

    EXPECT_EQ(actual1, actual2);
}

TEST(Single, ReturnsSameResults_SingleByPredicate)
{
    const int source[]{ 1, 2, 3 };

    auto query = From(source);

    const auto actual1 = query.Single([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.Single([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual1, actual2);
}

TEST(Single, ThrowsOnSingle_SingleFromAll_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Single(), EmptyCollectionException);
}

TEST(Single, ThrowsOnSingle_SingleFromAll_SourceContainsMoreThanOneElement)
{
    const int source[]{ 1, 2 };

    auto query = From(source);

    EXPECT_THROW(query.Single(), MoreThanOneElementException);
}

TEST(Single, ThrowsOnSingle_SingleByPredicate_SourceIsEmpty)
{
    vector<int> source;

    auto query = From(source);

    EXPECT_THROW(query.Single([](const int value){ return value % 2 == 0; }), EmptyCollectionException);
}

TEST(Single, ThrowsOnSingle_SingleByPredicate_SourceContainsSingleElementThatDoesNotSatisfyPredicate)
{
    const int source[]{ 1 };

    auto query = From(source);

    EXPECT_THROW(query.Single([](const int value){ return value % 2 == 0; }), EmptyCollectionException);
}

TEST(Single, ThrowsOnSingle_SingleByPredicate_SourceContainsMultipleElementsThatSatisfyPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5 };

    auto query = From(source);

    EXPECT_THROW(query.Single([](const int value){ return value % 2 == 0; }), MoreThanOneElementException);
}