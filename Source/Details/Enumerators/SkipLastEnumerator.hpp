#pragma once

#include "Details/Enumerators/SkipLastEnumerator.Forward.hpp"

#include <cstdint>
#include <queue>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct SkipLastEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ContainerType = std::queue<typename Base::ValueType>;

        SkipLastEnumerator(const TEnumerator enumerator, const std::uint32_t count);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        ContainerType container;
        std::uint32_t count;
        bool isReady{ false };
    };
}