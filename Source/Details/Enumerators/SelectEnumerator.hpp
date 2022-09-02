#pragma once

#include <type_traits>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector>
    struct SelectEnumerator final
    {
        using ValueType = decltype(std::declval<TSelector>()(std::declval<typename TEnumerator::ValueType>()));

        SelectEnumerator(const TEnumerator enumerator, const TSelector selector) :
            enumerator(enumerator),
            selector(selector)
        {
        }

        auto GetCurrent() -> ValueType
        {
            return selector(enumerator.GetCurrent());
        }

        auto IsFinished() -> bool
        {
            return enumerator.IsFinished();
        }

        void MoveNext()
        {
            enumerator.MoveNext();
        }

    private:
        TEnumerator enumerator;
        TSelector selector;
    };
}