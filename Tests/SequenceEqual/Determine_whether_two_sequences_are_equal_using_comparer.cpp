#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace std;

namespace CppLinq::Tests::SequenceEqual
{
    TEST(Determine_whether_two_sequences_are_equal_using_comparer, Returns_true_if_sources_are_empty)
    {
        // Arrange.
        const vector<int> source1;
        const vector<string> source2;

        // Act.
        const auto actual = From(source1).SequenceEqual(
            From(source2),
            [](const int value1, const string& value2){ return value1 == stoi(value2); }
        );

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Determine_whether_two_sequences_are_equal_using_comparer, Returns_true_if_sources_are_equal)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const string source2[]{ "1", "2", "3", "4", "5" };

        // Act.
        const auto actual = From(source1).SequenceEqual(
            From(source2),
            [](const int value1, const string& value2){ return value1 == stoi(value2); }
        );

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(Determine_whether_two_sequences_are_equal_using_comparer, Returns_false_if_first_source_is_longer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const string source2[]{ "1", "2", "3" };

        // Act.
        const auto actual = From(source1).SequenceEqual(
            From(source2),
            [](const int value1, const string& value2){ return value1 == stoi(value2); }
        );

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Determine_whether_two_sequences_are_equal_using_comparer, Returns_false_if_second_source_is_longer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3 };
        const string source2[]{ "1", "2", "3", "4", "5" };

        // Act.
        const auto actual = From(source1).SequenceEqual(
            From(source2),
            [](const int value1, const string& value2){ return value1 == stoi(value2); }
        );

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(Determine_whether_two_sequences_are_equal_using_comparer, Returns_the_same_result_on_every_call)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const string source2[]{ "1", "2", "3", "4", "5" };

        const auto query = From(source1);

        // Act.
        const auto actual1 = query.SequenceEqual(
            From(source2),
            [](const int value1, const string& value2){ return value1 == stoi(value2); }
        );
        const auto actual2 = query.SequenceEqual(
            From(source2),
            [](const int value1, const string& value2){ return value1 == stoi(value2); }
        );

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}