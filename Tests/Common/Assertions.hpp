#pragma once

#include <cstdint>
#include <format>
#include <gtest/gtest.h>

template <typename TQuery, typename T, std::uint32_t TLength>
void ExpectSequencesAreEqual(const TQuery& actualSequence, const T (&expectedSequence)[TLength])
{
    std::uint32_t index = 0U;

    for (const auto actual : actualSequence)
    {
        const bool isExpectedIndexValid = index < TLength;
        EXPECT_TRUE(isExpectedIndexValid) << "Actual sequence is longer than the expected one.";

        if (!isExpectedIndexValid)
        {
            break;;
        }

        const auto expected = expectedSequence[index];

        EXPECT_EQ(actual, expected) << std::format("Elements are not equal at index {}.", index);

        ++index;
    }

    const bool isExpectedSequenceFinished = index >= TLength;
    EXPECT_TRUE(isExpectedSequenceFinished) << "Expected sequence is longer than the actual one.";
}