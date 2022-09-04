#pragma once

#include "Details/Enumerators/AppendEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct AppendEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        AppendEnumerator(const TEnumerator enumerator, const Base::ValueType& value);

        auto GetCurrent() -> Base::ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        bool isAppended{ false };
        Base::ValueType value;
    };
}