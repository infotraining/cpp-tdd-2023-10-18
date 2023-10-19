#include <catch2/catch_test_macros.hpp>
#include "recently_used_list.hpp"
#include <algorithm>
#include <deque>

using namespace std;

namespace TestHelpers
{
    void add_many(RecentlyUsedList& rul, std::initializer_list<std::string> items)
    {
        for (const auto& item : items)
            rul.add(item);
    }
}

TEST_CASE("RecentlyUsedList after default construction", "[rul][constructors]")
{
    RecentlyUsedList rul;

    SECTION("size is zero")
    {
        REQUIRE(rul.size() == 0);
    }

    SECTION("is empty")
    {
        REQUIRE(rul.empty());
    }
}

TEST_CASE("RecentlyUsedList - inserting unique items", "[rul][insert]")
{
    RecentlyUsedList rul;

    rul.add("item1");

    SECTION("is not empty")
    {
        REQUIRE_FALSE(rul.empty());
    }

    SECTION("size is increased")
    {
        REQUIRE(rul.size() == 1);
    }

    SECTION("last inserted item is first")
    {
        rul.add("item2");
        rul.add("item3");

        REQUIRE(rul.front() == "item3");

        SECTION("items are in lifo order")
        {
            auto expected_order = {"item3", "item2", "item1"};
            REQUIRE(equal(begin(rul), end(rul), begin(expected_order), end(expected_order)));
        }
    }
}

TEST_CASE("RecentlyUsedList - indexing", "[rul][index]")
{
    RecentlyUsedList rul;

    TestHelpers::add_many(rul, {"1", "2", "3"});

    REQUIRE(rul[0] == "3");
    REQUIRE(rul[1] == "2");
    REQUIRE(rul[2] == "1");
}

TEST_CASE("RecentlyUsedList - inserting duplicates", "[rul][insert][duplicates]")
{
    string item1 = "item1";
    string item2 = "item2";
    string item3 = "item3";

    RecentlyUsedList rul;
    TestHelpers::add_many(rul, {item1, item2, item3});

    auto prev_size = rul.size();
    REQUIRE(prev_size == 3);

    rul.add(item2);

    SECTION("doesn't change a size")
    {
        REQUIRE(rul.size() == prev_size);
    }

    SECTION("moves duplicate to front")
    {
        REQUIRE(rul.front() == item2);
    }

    SECTION("doesn't change relative order other items")
    {
        auto expected_order = {item3, item1};
        REQUIRE(equal(begin(rul) + 1, end(rul), begin(expected_order)));
    }
}

TEST_CASE("RecentlyUsedList - empty string not allowed", "[rul][insert]")
{
    SECTION("inserting empty string throws an exception")
    {
        RecentlyUsedList rul;

        REQUIRE_THROWS_AS(rul.add(""s), std::invalid_argument);
    }
}

TEST_CASE("RecentlyUsedList - bounded capacity", "[rul][bounded]")
{
    SECTION("bounded capacity can be set as constructor")
    {
        RecentlyUsedList rul(5);

        REQUIRE(rul.capacity() == 5);
    }

    SECTION("when list is full")
    {
        RecentlyUsedList rul(4);

        TestHelpers::add_many(rul, {"item1"s, "item2"s, "item3"s, "item4"s});

        REQUIRE(rul.size() == rul.capacity());
        auto prev_size = rul.size();

        SECTION("inserting item")
        {
            rul.add("item5");

            SECTION("pushes item at front")
            {
                REQUIRE(rul.front() == "item5");
            }

            SECTION("doesn't change a size")
            {
                REQUIRE(rul.size() == prev_size);
            }

            SECTION("last item is dropped")
            {
                REQUIRE(rul.back() == "item2"s);
            }
        }
    }
}


// SCENARIO("Duplicates")
// {
//     GIVEN("RecentlyUsedList with items")
//     {
//         RecentlyUsedList rul;
//         rul.add(1);
//         rul.add(2);
//         rul.add(3);
//         size_t prev_size = rul.size();

//         WHEN("inserting duplicate")
//         {
//             rul.add(2);

//             THEN("size is not changed")
//             {
//                 REQUIRE(rul.size() == prev_size);
//             }

//             THEN("inserted item is moved to front")
//             {
//                 REQUIRE(rul.front() == 2);
//             }
//         }       
//     }
// }


// TEST_CASE("Rover - rotation")
// {
//     SECTION("Coordinates are the same")
//     {        
//     }

//     SECTION("Direction is changed")
//     {        
//     }
// }