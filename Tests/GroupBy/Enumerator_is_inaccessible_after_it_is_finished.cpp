#include <cstdint>
#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "GroupBy/Stubs/Human.hpp"
#include "GroupBy/Stubs/Join.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::GroupBy::Stubs;
using namespace std;

namespace CppLinq::Tests::GroupBy
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
    {
        // Arrange.
        const Human source[]
        {
            { 16U, "James" },
            { 24U, "Robert" },
            { 45U, "John" },
            { 43U, "Michael" },
            { 16U, "David" },
            { 45U, "William" },
            { 45U, "Richard" },
            { 50U, "Joseph" }
        };

        const auto query = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        const auto action = [&enumerator](){ enumerator.MoveNext(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }

    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_get_current)
    {
        // Arrange.
        const Human source[]
        {
            { 16U, "James" },
            { 24U, "Robert" },
            { 45U, "John" },
            { 43U, "Michael" },
            { 16U, "David" },
            { 45U, "William" },
            { 45U, "Richard" },
            { 50U, "Joseph" }
        };

        const auto query = From(source).GroupBy(
            [](const Human& human){ return human.age; },
            [](const Human& human){ return human.name; },
            [](const uint32_t age, const vector<string>& elements){ return to_string(age) + " " + Join(elements); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        const auto action = [&enumerator](){ enumerator.GetCurrent(); };

        // Assert.
        EXPECT_THROW(action(), FinishedEnumeratorException);
    }
}