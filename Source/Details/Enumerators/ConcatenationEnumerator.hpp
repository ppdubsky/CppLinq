#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details
{
    template <typename TEnumerator>
    struct Query;
}

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNextEnumerator>
    struct ConcatenationEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        ConcatenationEnumerator(const TEnumerator enumerator, const Query<TNextEnumerator>& nextQuery) :
            Base(enumerator),
            nextQuery(nextQuery)
        {
        }

        auto GetCurrent() -> Base::ValueType
        {
            return Base::IsFinished() ? nextQuery.GetEnumerator().GetCurrent() : Base::GetCurrent();
        }

        auto IsFinished() -> bool
        {
            return Base::IsFinished() && nextQuery.GetEnumerator().IsFinished();
        }

        void MoveNext()
        {
            if (Base::IsFinished())
            {
                nextQuery.GetEnumerator().MoveNext();
            }
            else
            {
                Base::MoveNext();
            }
        }

    private:
        Query<TNextEnumerator> nextQuery;
    };
}