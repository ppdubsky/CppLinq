#pragma once

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct EnumeratorWrapper
    {
        using ValueType = typename TEnumerator::ValueType;

        auto GetCurrent() -> ValueType;
        auto IsFinished() -> bool;
        void MoveNext();

    protected:
        EnumeratorWrapper(const TEnumerator enumerator);

    private:
        TEnumerator enumerator;
    };
}