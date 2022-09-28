#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Distinct/Equatable.hpp"

namespace CppLinq::Tests::Distinct
{
    TEST(Distinct_deferred_execution_with_comparer, Execution_is_deferred)
    {
        // Arrange.
        Equatable::equalityCount = 0U;

        const Equatable source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Distinct([](const Equatable value1, const Equatable value2){ return value1.EqualTo(value2); });

        // Assert.
        EXPECT_EQ(Equatable::equalityCount, 0U);
    }
}