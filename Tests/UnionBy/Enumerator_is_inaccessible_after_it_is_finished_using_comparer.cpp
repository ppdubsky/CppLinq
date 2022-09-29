#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "UnionBy/Stubs/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::UnionBy::Stubs;
using namespace std;

namespace CppLinq::Tests::UnionBy
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished_using_comparer, Throws_on_move_next)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1).UnionBy(
            From(source2),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
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

    TEST(Enumerator_is_inaccessible_after_it_is_finished_using_comparer, Throws_on_get_current)
    {
        // Arrange.
        const Customer source1[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "John" },
            { 5U, "Michael" },
            { 6U, "David" },
            { 7U, "William" }
        };
        const Customer source2[]
        {
            { 8U, "Robert" },
            { 9U, "Richard" },
            { 10U, "Joseph" },
            { 11U, "James" },
            { 12U, "James" },
            { 13U, "Thomas" },
            { 14U, "Michael" }
        };

        const auto query = From(source1).UnionBy(
            From(source2),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
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