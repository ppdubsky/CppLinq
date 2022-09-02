#pragma once

#include <cstdint>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct SkipEnumerator final
    {
        using ValueType = typename TEnumerator::ValueType;

        SkipEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
            count(count),
            enumerator(enumerator)
        {
        }

        auto GetCurrent() -> ValueType
        {
            EnsureEnumeratorIsReady();

            return enumerator.GetCurrent();
        }

        auto IsFinished() -> bool
        {
            EnsureEnumeratorIsReady();

            return enumerator.IsFinished();
        }

        void MoveNext()
        {
            EnsureEnumeratorIsReady();

            enumerator.MoveNext();
        }

    private:
        void EnsureEnumeratorIsReady()
        {
            if (!isReady)
            {
                while (count > 0U && !enumerator.IsFinished())
                {
                    enumerator.MoveNext();

                    --count;
                }

                isReady = true;
            }
        }

        std::uint32_t count;
        bool isReady{ false };
        TEnumerator enumerator;
    };
}