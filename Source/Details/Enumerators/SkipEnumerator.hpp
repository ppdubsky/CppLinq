#pragma once

#include "Details/Enumerators/SkipEnumerator.Forward.hpp"

#include <cstdint>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct SkipEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        SkipEnumerator(const TEnumerator enumerator, const std::uint32_t count);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        std::uint32_t count;
        bool isReady{ false };
    };
}