#include <vector>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(FirstOrDefault, ReturnsDefault_FirstFromAll_SourceIsEmpty)
{
    vector<int> source;
    const int expected = 11;

    const auto actual = From(source).FirstOrDefault(11);

    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsFirst_FirstFromAll_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 1;

    const auto actual = From(source).FirstOrDefault(11);

    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsDefault_FirstByPredicate_SourceIsEmpty)
{
    vector<int> source;
    const int expected = 11;

    const auto actual = From(source).FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsFirst_FirstByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const auto expected = 2;

    const auto actual = From(source).FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsDefault_FirstByPredicate_SourceIsNotEmpty)
{
    const int source[]{ 1, 3, 5, 7, 9 };
    const int expected = 11;

    const auto actual = From(source).FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    EXPECT_EQ(actual, expected);
}

TEST(FirstOrDefault, ReturnsSameResults_FirstFromAll)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.FirstOrDefault(11);
    const auto actual2 = query.FirstOrDefault(11);

    EXPECT_EQ(actual1, actual2);
}

TEST(FirstOrDefault, ReturnsSameResults_FirstByPredicate)
{
    const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto query = From(source);

    const auto actual1 = query.FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);
    const auto actual2 = query.FirstOrDefault([](const int value){ return value % 2 == 0; }, 11);

    EXPECT_EQ(actual1, actual2);
}