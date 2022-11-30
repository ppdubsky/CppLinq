#pragma once

#include "Details/Enumerators/ChunkEnumerator.Forward.hpp"

#include <cstdint>
#include <vector>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct ChunkEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = std::vector<typename Base::ValueType>;

        ChunkEnumerator(const TEnumerator enumerator, const std::uint32_t size);

        auto GetCurrent() -> const ValueType&;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        ValueType container;
        bool isBaseFinished{ false };
        bool isReady{ false };
        std::uint32_t size;
    };
}