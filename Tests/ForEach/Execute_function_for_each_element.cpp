#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::ForEach
{
    TEST(Execute_function_for_each_element, ReturnsExpectedValues)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const int expected[]{ 1, 2, 3, 4, 5 };

        auto sum = 0;

        // Act.
        const auto actual = From(source).ForEach([&sum](const int value){ sum += value; });

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);

        EXPECT_EQ(sum, 15);
    }

    TEST(Execute_function_for_each_element, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ForEach([](const int /*value*/){});
        const auto actual2 = query.ForEach([](const int /*value*/){});

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}