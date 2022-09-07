#pragma once

#include "Details/Enumerators/PrependEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct PrependEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        PrependEnumerator(const TEnumerator enumerator, const Base::ValueType& value);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        bool isPrepended{ false };
        Base::ValueType value;
    };
}