#include <optional>
#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(SingleOptional, ReturnsEmpty_SingleFromAll_SourceIsEmpty)
{
    vector<int> source;
    optional<int> expected;

    const auto actual = From(source).SingleOptional();

    EXPECT_EQ(actual, expected);
}

TEST(SingleOptional, ReturnsSingle_SingleFromAll_SourceContainsSingleElement)
{
    const int source[]{ 1 };
    const auto expected = 1;

    const auto actual = From(source).SingleOptional();

    EXPECT_EQ(actual, expected);
}

TEST(SingleOptional, ReturnsEmpty_SingleByPredicate_SourceIsEmpty)
{
    vector<int> source;
    optional<int> expected;

    const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(SingleOptional, ReturnsEmpty_SingleByPredicate_SourceContainsSingleElementThatDoesNotSatisfyPredicate)
{
    const int source[]{ 1 };
    optional<int> expected;

    const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(SingleOptional, ReturnsSingle_SingleByPredicate_SourceContainsSingleElement)
{
    const int source[]{ 1, 2, 3 };
    const auto expected = 2;

    const auto actual = From(source).SingleOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual, expected);
}

TEST(SingleOptional, ReturnsSameResults_SingleFromAll)
{
    const int source[]{ 1 };

    auto query = From(source);

    const auto actual1 = query.SingleOptional();
    const auto actual2 = query.SingleOptional();

    EXPECT_EQ(actual1, actual2);
}

TEST(SingleOptional, ReturnsSameResults_SingleByPredicate)
{
    const int source[]{ 1, 2, 3 };

    auto query = From(source);

    const auto actual1 = query.SingleOptional([](const int value){ return value % 2 == 0; });
    const auto actual2 = query.SingleOptional([](const int value){ return value % 2 == 0; });

    EXPECT_EQ(actual1, actual2);
}

TEST(SingleOptional, ThrowsOnSingleOptional_SingleFromAll_SourceContainsMoreThanOneElement)
{
    const int source[]{ 1, 2 };

    auto query = From(source);

    EXPECT_THROW(query.SingleOptional(), MoreThanOneElementException);
}

TEST(SingleOptional, ThrowsOnSingleOptional_SingleByPredicate_SourceContainsMultipleElementsThatSatisfyPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5 };

    auto query = From(source);

    EXPECT_THROW(query.SingleOptional([](const int value){ return value % 2 == 0; }), MoreThanOneElementException);
}