#include "Assertions.hpp"
#include "CppLinq.hpp"

namespace CppLinq::Tests::ToVector
{
    TEST(Create_vector, Returns_expected_container)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        const int expected[]{ 2, 4, 6, 8, 10 };

        // Act.
        const auto actual = From(source)
            .Where([](const int value){ return value % 2 == 0; })
            .ToVector();

        // Assert.
        ExpectSequencesAreEquivalent(actual, expected);
    }

    TEST(Create_vector, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        const auto query = From(source).Where([](const int value){ return value % 2 == 0; });

        // Act.
        const auto actual1 = query.ToVector();
        const auto actual2 = query.ToVector();

        // Assert.
        ExpectSequencesAreEquivalent(actual1, actual2);
    }
}