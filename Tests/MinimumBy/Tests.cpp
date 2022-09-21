#include <cstdint>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "MinimumBy/Human.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::MinimumBy
{
    TEST(MinimumBy, ReturnsMinimum_SourceIsNotEmpty)
    {
        // Arrange.
        const Human source[]
        {
            { 16U, "James" },
            { 24U, "Robert" },
            { 45U, "John" },
            { 43U, "Michael" },
            { 16U, "David" },
            { 45U, "William" }
        };
        const Human expected{ 16U, "James" };

        // Act.
        const auto actual = From(source).MinimumBy([](const Human& human){ return human.age; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(MinimumBy, ReturnsSameResults)
    {
        // Arrange.
        const Human source[]
        {
            { 16U, "James" },
            { 24U, "Robert" },
            { 45U, "John" },
            { 43U, "Michael" },
            { 16U, "David" },
            { 45U, "William" }
        };

        const auto query = From(source);

        // Act.
        const auto actual1 = query.MinimumBy([](const Human& human){ return human.age; });
        const auto actual2 = query.MinimumBy([](const Human& human){ return human.age; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(MinimumBy, ThrowsOnMinimum_SourceIsEmpty)
    {
        // Arrange.
        const vector<Human> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.MinimumBy([](const Human& human){ return human.age; }), EmptyContainerException);
    }
}