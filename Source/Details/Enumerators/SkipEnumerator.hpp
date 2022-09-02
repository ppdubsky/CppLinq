#pragma once

#include <cstdint>

#include "EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct SkipEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        SkipEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
            Base(enumerator),
            count(count)
        {
        }

        auto GetCurrent() -> Base::ValueType
        {
            EnsureEnumeratorIsReady();

            return Base::GetCurrent();
        }

        auto IsFinished() -> bool
        {
            EnsureEnumeratorIsReady();

            return Base::IsFinished();
        }

        void MoveNext()
        {
            EnsureEnumeratorIsReady();

            Base::MoveNext();
        }

    private:
        void EnsureEnumeratorIsReady()
        {
            if (!isReady)
            {
                while (count > 0U && !Base::IsFinished())
                {
                    Base::MoveNext();

                    --count;
                }

                isReady = true;
            }
        }

        std::uint32_t count;
        bool isReady{ false };
    };
}