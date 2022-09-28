#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Distinct/Equatable.hpp"

namespace CppLinq::Tests::Distinct
{
    TEST(Distinct_deferred_execution_without_comparer, Execution_is_deferred)
    {
        // Arrange.
        Equatable::equalityCount = 0U;

        const Equatable source[]{ 'a', 'b', 'c', 'd', 'e' };

        // Act.
        const auto actual = From(source).Distinct();

        // Assert.
        EXPECT_EQ(Equatable::equalityCount, 0U);
    }
}