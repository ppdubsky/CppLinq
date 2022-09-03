#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    struct WhereEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        WhereEnumerator(const TEnumerator enumerator, const TPredicate predicate) :
            Base(enumerator),
            predicate(predicate)
        {
        }

        auto GetCurrent() -> Base::ValueType
        {
            EnsureEnumeratorIsReady();

            return Base::GetCurrent();
        }

        auto IsFinished() -> bool
        {
            EnsureEnumeratorIsReady();

            return Base::IsFinished();
        }

        void MoveNext()
        {
            EnsureEnumeratorIsReady();

            Base::MoveNext();

            isReady = false;
        }

    private:
        void EnsureEnumeratorIsReady()
        {
            if (!isReady)
            {
                while (!Base::IsFinished())
                {
                    if (predicate(Base::GetCurrent()))
                    {
                        break;
                    }
                    else
                    {
                        Base::MoveNext();
                    }
                }

                isReady = true;
            }
        }

        bool isReady{ false };
        TPredicate predicate;
    };
}