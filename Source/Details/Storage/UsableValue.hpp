#pragma once

namespace CppLinq::Details::Storage
{
    template <typename T>
    struct UsableValue final
    {
        bool isUsed{ false };
        T value;
    };
}