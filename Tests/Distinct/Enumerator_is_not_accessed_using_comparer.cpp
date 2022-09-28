#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Distinct/Stubs/Equatable.hpp"

using namespace CppLinq::Tests::Distinct::Stubs;

namespace CppLinq::Tests::Distinct
{
    TEST(Enumerator_is_not_accessed_using_comparer, Execution_is_deferred)
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