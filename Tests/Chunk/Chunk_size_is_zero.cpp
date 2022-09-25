#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::Chunk
{
    TEST(Chunk_size_is_zero, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<int> source;

        auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Chunk(0U); };

        // Assert.
        EXPECT_THROW(action(), ArgumentOutOfRangeException);
    }

    TEST(Chunk_size_is_zero, Throws_if_source_contains_one_element)
    {
        // Arrange.
        const int source[]{ 1 };

        auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Chunk(0U); };

        // Assert.
        EXPECT_THROW(action(), ArgumentOutOfRangeException);
    }

    TEST(Chunk_size_is_zero, Throws_if_source_contains_two_elements)
    {
        // Arrange.
        const int source[]{ 1, 2 };

        auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Chunk(0U); };

        // Assert.
        EXPECT_THROW(action(), ArgumentOutOfRangeException);
    }

    TEST(Chunk_size_is_zero, Throws_if_source_contains_thress_elements)
    {
        // Arrange.
        const int source[]{ 1, 2, 3 };

        auto query = From(source);

        // Act.
        const auto action = [&query](){ query.Chunk(0U); };

        // Assert.
        EXPECT_THROW(action(), ArgumentOutOfRangeException);
    }
}