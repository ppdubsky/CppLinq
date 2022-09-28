#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Minimum
{
    TEST(Return_the_minimum, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Minimum(); };

        // Assert.
        EXPECT_THROW(action(), EmptyContainerException);
    }

    TEST(Return_the_minimum, Returns_minimum_value_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
        const auto expected = -10;

        // Act.
        const auto actual = From(source).Minimum();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_the_minimum, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Minimum();
        const auto actual2 = query.Minimum();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}