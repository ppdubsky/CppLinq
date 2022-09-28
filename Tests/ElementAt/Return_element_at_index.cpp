#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::ElementAt
{
    TEST(Return_element_at_index, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.ElementAt(0U), EmptyContainerException);
    }

    TEST(Return_element_at_index, Returns_element_if_index_is_valid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };
        const auto expected = 4;

        // Act.
        const auto actual = From(source).ElementAt(3U);

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(Return_element_at_index, Throws_if_index_is_invalid)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.ElementAt(10U), EmptyContainerException);
    }

    TEST(Return_element_at_index, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5 };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.ElementAt(3U);
        const auto actual2 = query.ElementAt(3U);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}