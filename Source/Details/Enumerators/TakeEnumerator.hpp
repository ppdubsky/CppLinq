#pragma once

#include <cstdint>

#include "EnumeratorWrapper.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct TakeEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        TakeEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
            Base(enumerator),
            count(count)
        {
        }

        auto GetCurrent() -> Base::ValueType
        {
            if (IsFinished())
            {
                throw Exceptions::FinishedEnumeratorException();
            }

            return Base::GetCurrent();
        }

        auto IsFinished() -> bool
        {
            return count == 0U || Base::IsFinished();
        }

        void MoveNext()
        {
            if (count == 0U)
            {
                throw Exceptions::FinishedEnumeratorException();
            }

            Base::MoveNext();

            --count;
        }

    private:
        std::uint32_t count;
    };
}