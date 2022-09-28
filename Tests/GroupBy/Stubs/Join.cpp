#include "GroupBy/Stubs/Join.hpp"

using namespace std;

namespace CppLinq::Tests::GroupBy
{
    auto Join(const vector<string>& elements) -> string
    {
        string joinedString;

        for (const string& element : elements)
        {
            joinedString.append(element);
        }

        return joinedString;
    }
}