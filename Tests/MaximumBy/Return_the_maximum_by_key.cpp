#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "MaximumBy/Stubs/Human.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::MaximumBy::Stubs;
using namespace std;

namespace CppLinq::Tests::MaximumBy
{
    TEST(Return_the_maximum_by_key, Throws_if_source_is_empty)
    {
        // Arrange.
        const vector<Human> source;

        const auto query = From(source);

        // Act.
        const auto action = [&query](){ query.MaximumBy([](const Human& human){ return human.age; }); };

        // Assert.
        EXPECT_THROW(action(), EmptyContainerException);
    }

    TEST(Return_the_maximum_by_key, Returns_maximum_value_if_source_is_not_empty)
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

    TEST(Return_the_maximum_by_key, Returns_the_same_result_on_every_call)
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
}