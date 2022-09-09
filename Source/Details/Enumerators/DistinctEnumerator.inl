#pragma once

#include "Details/Enumerators/DistinctEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TComparer>
    DistinctEnumerator<TEnumerator, TComparer>::DistinctEnumerator(const TEnumerator enumerator, const TComparer comparer) :
        Base(enumerator),
        comparer(comparer)
    {
    }

    template <typename TEnumerator, typename TComparer>
    void DistinctEnumerator<TEnumerator, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            current = container.cend();

            while (Base::HasCurrent())
            {
                const auto result = container.insert(Base::GetCurrent());

                if (result.second)
                {
                    current = result.first;
                    break;
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TComparer>
    auto DistinctEnumerator<TEnumerator, TComparer>::GetCurrent() -> const Base::ValueType&
    {
        EnsureEnumeratorIsReady();

        if (!Base::HasCurrent() || current == container.cend())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *current;
    }

    template <typename TEnumerator, typename TComparer>
    void DistinctEnumerator<TEnumerator, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}