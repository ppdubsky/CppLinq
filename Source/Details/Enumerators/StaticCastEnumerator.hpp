#pragma once

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNewType>
    struct StaticCastEnumerator final
    {
        using ValueType = TNewType;

        StaticCastEnumerator(const TEnumerator enumerator) :
            enumerator(enumerator)
        {
        }

        auto GetCurrent() -> ValueType
        {
            return static_cast<TNewType>(enumerator.GetCurrent());
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
    };
}