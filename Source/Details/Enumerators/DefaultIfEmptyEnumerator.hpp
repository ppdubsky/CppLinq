#pragma once

#include "Details/Enumerators/DefaultIfEmptyEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct DefaultIfEmptyEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        DefaultIfEmptyEnumerator(const TEnumerator enumerator, const Base::ValueType value);

        auto GetCurrent() -> Base::ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        bool isEnumeratorEmpty{ true };
        bool isMovedNext{ false };
        Base::ValueType value;
    };
}