#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Average
{
    TEST(Compute_the_average, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<double> source;

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Average(); };

        // Assert.
        EXPECT_THROW(action(), EmptyContainerException);
    }

    TEST(Compute_the_average, Returns_first_element_if_source_contains_one_element)
    {
        // Arrange.
        const double source[]{ 1.0 };
        const auto expected = 1.0;

        // Act.
        const auto actual = From(source).Average();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Compute_the_average, Returns_average_value_if_source_contains_two_elements)
    {
        // Arrange.
        const double source[]{ 1.0, 2.0 };
        const auto expected = 1.5;

        // Act.
        const auto actual = From(source).Average();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Compute_the_average, Returns_average_value_if_source_contains_three_elements)
    {
        // Arrange.
        const double source[]{ 1.0, 2.0, 3.0 };
        const auto expected = 2.0;

        // Act.
        const auto actual = From(source).Average();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Compute_the_average, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const double source[]{ 1.0, 2.0, 3.0, 4.0, 5.0 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Average();
        const auto actual2 = query.Average();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}