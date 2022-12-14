#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Count
{
    TEST(Count_elements, Returns_zero_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;
        const auto expected = 0U;

        // Act.
        const auto actual = From(source).Count();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Count_elements, Returns_size_of_sequence_if_source_is_not_empty)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const auto expected = 5U;

        // Act.
        const auto actual = From(source).Count();

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Count_elements, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.Count();
        const auto actual2 = query.Count();

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}