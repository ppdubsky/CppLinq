#include <cctype>
#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "ExceptBy/Stubs/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::ExceptBy::Stubs;
using namespace std;

namespace CppLinq::Tests::ExceptBy
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished_using_comparer, Throws_on_move_next)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "robert" },
            { 4U, "John" },
            { 5U, "john" },
            { 6U, "Michael" },
            { 7U, "David" },
            { 8U, "david" },
            { 9U, "William" }
        };
        const string except[]
        {
            "thomas",
            "robert",
            "joseph",
            "david",
            "richard"
        };

        const auto query = From(source).ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
    }

    TEST(Enumerator_is_inaccessible_after_it_is_finished_using_comparer, Throws_on_get_current)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "robert" },
            { 4U, "John" },
            { 5U, "john" },
            { 6U, "Michael" },
            { 7U, "David" },
            { 8U, "david" },
            { 9U, "William" }
        };
        const string except[]
        {
            "thomas",
            "robert",
            "joseph",
            "david",
            "richard"
        };

        const auto query = From(source).ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; },
            [](const string& value1, const string& value2){ return tolower(value1.front()) == tolower(value2.front()); }
        );

        auto enumerator = query.GetEnumerator();
        while (enumerator.HasCurrent())
        {
            enumerator.MoveNext();
        }

        // Act.
        // Assert.
        EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
    }
}