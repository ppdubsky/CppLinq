#include <string>

#include "Common/Assertions.hpp"
#include "CppLinq.hpp"

using namespace CppLinq;
using namespace CppLinq::Exceptions;
using namespace std;

TEST(Zip, ReturnsExpectedValues_SourcesOfSameLength)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };
    const string expected[]{ "a1", "b2", "c3", "d4", "e5" };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Zip, ReturnsExpectedValues_FirstSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c' };
    const string expected[]{ "a1", "b2", "c3" };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Zip, ReturnsExpectedValues_SecondSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };
    const string expected[]{ "a1", "b2", "c3" };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    // Assert.
    ExpectSequencesAreEquivalent(actual, expected);
}

TEST(Zip, ReturnsSameResults_SourcesOfSameLength)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual1 = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });
    const auto actual2 = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Zip, ReturnsSameResults_FirstSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual1 = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });
    const auto actual2 = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Zip, ReturnsSameResults_SecondSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query1 = From(source1);
    const auto query2 = From(source2);

    // Act.
    const auto actual1 = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });
    const auto actual2 = query1.Zip(query2, [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    // Assert.
    ExpectSequencesAreEquivalent(actual1, actual2);
}

TEST(Zip, SourceThrowsOnMoveNext_SourcesOfSameLength)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source1).Zip(From(source2), [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Zip, SourceThrowsOnMoveNext_FirstSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c' };

    const auto query = From(source1).Zip(From(source2), [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Zip, SourceThrowsOnMoveNext_SecondSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source1).Zip(From(source2), [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.MoveNext(), FinishedEnumeratorException);
}

TEST(Zip, SourceThrowsOnGetCurrent_SourcesOfSameLength)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source1).Zip(From(source2), [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(Zip, SourceThrowsOnGetCurrent_FirstSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    const int source2[]{ 'a', 'b', 'c' };

    const auto query = From(source1).Zip(From(source2), [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}

TEST(Zip, SourceThrowsOnGetCurrent_SecondSourceIsLonger)
{
    // Arrange.
    const double source1[]{ 1.1, 2.2, 3.3 };
    const int source2[]{ 'a', 'b', 'c', 'd', 'e' };

    const auto query = From(source1).Zip(From(source2), [](const double value1, const int value2){ return string(1U, static_cast<char>(value2)).append(1U, '0' + static_cast<char>(value1)); });

    auto enumerator = query.GetEnumerator();
    while (enumerator.HasCurrent())
    {
        enumerator.MoveNext();
    }

    // Act.
    // Assert.
    EXPECT_THROW(enumerator.GetCurrent(), FinishedEnumeratorException);
}