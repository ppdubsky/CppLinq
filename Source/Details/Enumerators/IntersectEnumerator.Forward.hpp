#pragma once

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    struct IntersectEnumerator;
}