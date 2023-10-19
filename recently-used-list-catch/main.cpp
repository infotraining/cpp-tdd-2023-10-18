#include "recently_used_list.hpp"
#include <iostream>

using namespace std;

int main()
{
    RecentlyUsedList rul;

    rul.add("item1");
    rul.add("item2");
    rul.add("item3");
    rul.add("item2");

    for (const auto& item : rul)
        cout << item << '\n';
}