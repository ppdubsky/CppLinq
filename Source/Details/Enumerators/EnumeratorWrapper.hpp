#pragma once

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct EnumeratorWrapper
    {
        using ValueType = typename TEnumerator::ValueType;

        auto GetCurrent() -> ValueType
        {
            return enumerator.GetCurrent();
        }

        auto IsFinished() -> bool
        {
            return enumerator.IsFinished();
        }

        void MoveNext()
        {
            enumerator.MoveNext();
        }

    protected:
        EnumeratorWrapper(const TEnumerator enumerator) :
            enumerator(enumerator)
        {
        }

    private:
        TEnumerator enumerator;
    };
}