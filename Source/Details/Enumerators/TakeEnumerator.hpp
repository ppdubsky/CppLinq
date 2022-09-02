#pragma once

#include <cstdint>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct TakeEnumerator final
    {
        using ValueType = typename TEnumerator::ValueType;

        TakeEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
            count(count),
            enumerator(enumerator)
        {
        }

        auto GetCurrent() -> ValueType
        {
            return enumerator.GetCurrent();
        }

        auto IsFinished() -> bool
        {
            return count == 0U || enumerator.IsFinished();
        }

        void MoveNext()
        {
            if (count > 0U)
            {
                enumerator.MoveNext();

                --count;
            }
        }

    private:
        std::uint32_t count;
        TEnumerator enumerator;
    };
}