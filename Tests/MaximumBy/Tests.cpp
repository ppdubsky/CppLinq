#include <cstdint>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "MaximumBy/Human.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::MaximumBy
{
    TEST(MaximumBy, ReturnsMaximum_SourceIsNotEmpty)
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
        const Human expected{ 45U, "John" };

        // Act.
        const auto actual = From(source).MaximumBy([](const Human& human){ return human.age; });

        // Assert.
        EXPECT_EQ(actual, expected);
    }

    TEST(MaximumBy, ReturnsSameResults)
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
        const auto actual1 = query.MaximumBy([](const Human& human){ return human.age; });
        const auto actual2 = query.MaximumBy([](const Human& human){ return human.age; });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(MaximumBy, ThrowsOnMaximum_SourceIsEmpty)
    {
        // Arrange.
        const vector<Human> source;

        const auto query = From(source);

        // Act.
        // Assert.
        EXPECT_THROW(query.MaximumBy([](const Human& human){ return human.age; }), EmptyContainerException);
    }
}