#pragma once

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    struct WhereEnumerator final
    {
        using ValueType = typename TEnumerator::ValueType;

        WhereEnumerator(const TEnumerator enumerator, const TPredicate predicate) :
            enumerator(enumerator),
            predicate(predicate)
        {
        }

        auto GetCurrent() -> ValueType
        {
            EnsureEnumeratorIsReady();

            return enumerator.GetCurrent();
        }

        auto IsFinished() -> bool
        {
            EnsureEnumeratorIsReady();

            return enumerator.IsFinished();
        }

        void MoveNext()
        {
            EnsureEnumeratorIsReady();

            enumerator.MoveNext();

            isReady = false;
        }

    private:
        void EnsureEnumeratorIsReady()
        {
            if (!isReady)
            {
                while (!enumerator.IsFinished())
                {
                    if (predicate(enumerator.GetCurrent()))
                    {
                        break;
                    }
                    else
                    {
                        enumerator.MoveNext();
                    }
                }

                isReady = true;
            }
        }

        TEnumerator enumerator;
        bool isReady{ false };
        TPredicate predicate;
    };
}