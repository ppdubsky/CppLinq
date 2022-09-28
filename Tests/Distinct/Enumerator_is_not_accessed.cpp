#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "Distinct/Stubs/Equatable.hpp"

using namespace CppLinq::Tests::Distinct::Stubs;

namespace CppLinq::Tests::Distinct
{
    TEST(Enumerator_is_not_accessed, Execution_is_deferred)
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