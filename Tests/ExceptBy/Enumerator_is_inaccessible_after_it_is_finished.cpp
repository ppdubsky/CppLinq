#include <string>

#include "Assertions.hpp"
#include "CppLinq.hpp"
#include "ExceptBy/Stubs/Customer.hpp"

using namespace CppLinq::Exceptions;
using namespace CppLinq::Tests::ExceptBy::Stubs;
using namespace std;

namespace CppLinq::Tests::ExceptBy
{
    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_move_next)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };
        const string except[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };

        const auto query = From(source).ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; }
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

    TEST(Enumerator_is_inaccessible_after_it_is_finished, Throws_on_get_current)
    {
        // Arrange.
        const Customer source[]
        {
            { 1U, "James" },
            { 2U, "Robert" },
            { 3U, "John" },
            { 4U, "Michael" },
            { 5U, "David" },
            { 6U, "William" }
        };
        const string except[]
        {
            "Thomas",
            "Robert",
            "Joseph",
            "David",
            "Richard"
        };

        const auto query = From(source).ExceptBy(
            From(except),
            [](const Customer& customer){ return customer.name; }
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