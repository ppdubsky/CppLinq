#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Single
{
    TEST(Return_single_element, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Single(); };

        // Assert.
        EXPECT_THROW(action(), EmptyContainerException);
    }

    TEST(Return_single_element, Returns_single_element_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };
        const auto expected = 1;

        // Act.
        const auto actual = From(source).Single();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_single_element, Throws_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Single(); };

        // Assert.
        EXPECT_THROW(action(), MoreThanOneElementException);
    }

    TEST(Return_single_element, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Single();
        const auto actual2 = query.Single();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}