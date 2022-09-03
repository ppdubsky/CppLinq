#pragma once

#include <cstdint>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct TakeEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        TakeEnumerator(const TEnumerator enumerator, const std::uint32_t count);

        auto GetCurrent() -> Base::ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        std::uint32_t count;
    };
}