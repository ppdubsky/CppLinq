#include <string>
#include <vector>

#include "Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq::Exceptions;
using namespace std;

namespace CppLinq::Tests::SequenceEqual
{
    TEST(SequenceEqual, ReturnsTrue_SourcesAreEmpty_DefaultComparer)
    {
        // Arrange.
        const vector<int> source1;
        const vector<int> source2;

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2);

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(SequenceEqual, ReturnsTrue_SourcesAreEmpty_CustomComparer)
    {
        // Arrange.
        const vector<int> source1;
        const vector<string> source2;

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2, [](const int value1, const string& value2){ return value1 == stoi(value2); });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(SequenceEqual, ReturnsTrue_SourcesOfSameLength_DefaultComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 1, 2, 3, 4, 5 };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2);

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(SequenceEqual, ReturnsTrue_SourcesOfSameLength_CustomComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const string source2[]{ "1", "2", "3", "4", "5" };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2, [](const int value1, const string& value2){ return value1 == stoi(value2); });

        // Assert.
        EXPECT_TRUE(actual);
    }

    TEST(SequenceEqual, ReturnsFalse_FirstSourceIsLonger_DefaultComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 1, 2, 3 };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2);

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(SequenceEqual, ReturnsFalse_FirstSourceIsLonger_CustomComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const string source2[]{ "1", "2", "3" };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2, [](const int value1, const string& value2){ return value1 == stoi(value2); });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(SequenceEqual, ReturnsFalse_SecondSourceIsLonger_DefaultComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3 };
        const int source2[]{ 1, 2, 3, 4, 5 };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2);

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(SequenceEqual, ReturnsFalse_SecondSourceIsLonger_CustomComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3 };
        const string source2[]{ "1", "2", "3", "4", "5" };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual = query1.SequenceEqual(query2, [](const int value1, const string& value2){ return value1 == stoi(value2); });

        // Assert.
        EXPECT_FALSE(actual);
    }

    TEST(SequenceEqual, ReturnsSameResults_DefaultComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const int source2[]{ 1, 2, 3, 4, 5 };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual1 = query1.SequenceEqual(query2);
        const auto actual2 = query1.SequenceEqual(query2);

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }

    TEST(SequenceEqual, ReturnsSameResults_CustomComparer)
    {
        // Arrange.
        const int source1[]{ 1, 2, 3, 4, 5 };
        const string source2[]{ "1", "2", "3", "4", "5" };

        const auto query1 = From(source1);
        const auto query2 = From(source2);

        // Act.
        const auto actual1 = query1.SequenceEqual(query2, [](const int value1, const string& value2){ return value1 == stoi(value2); });
        const auto actual2 = query1.SequenceEqual(query2, [](const int value1, const string& value2){ return value1 == stoi(value2); });

        // Assert.
        EXPECT_EQ(actual1, actual2);
    }
}