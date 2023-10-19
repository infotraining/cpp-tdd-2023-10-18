#include <algorithm>

#include "recently_used_list.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace ::testing;

TEST(RecentlyUsedList_DefaultConstructed, IsEmpty)
{
    RecentlyUsedList rul;

    ASSERT_THAT(rul, ::testing::IsEmpty());
}

TEST(RecentlyUsedList_DefaultConstructed, SizeIsZero)
{
    RecentlyUsedList rul;

    ASSERT_THAT(rul.size(), ::testing::Eq(0));
}

TEST(RecentlyUsedList_AddingItem, IsNotEmpty)
{
    RecentlyUsedList rul;

    rul.add("item1");

    ASSERT_FALSE(rul.empty());
}

TEST(RecentlyUsedList_AddingItem, SizeIsIncreased)
{
    RecentlyUsedList rul;

    rul.add("item1");

    auto size_before = rul.size();
    ASSERT_EQ(size_before, 1u) << "Guard for a test";

    rul.add("item2");
    auto size_after = rul.size();

    ASSERT_THAT(size_after - size_before, Eq(1u));
}

TEST(RecentlyUsedList_AddingItem, AddingEmptyStringThrowsAnException)
{
    RecentlyUsedList rul;

    ASSERT_THROW(rul.add(""), std::invalid_argument);
}

TEST(RecentlyUsedList_Clear, RemovesAllItems)
{
    RecentlyUsedList rul;
    rul.add("item1");

    rul.clear();

    ASSERT_THAT(rul, IsEmpty());
}

struct RecentlyUsedList_WithItems : Test
{
    RecentlyUsedList rul;

    void SetUp() override
    {
        rul.add("item1");
        rul.add("item2");
        rul.add("item3");
    }

    void TearDown() override
    {
        rul.clear();
    }
};

struct RecentlyUsedList_LIFO : RecentlyUsedList_WithItems
{
};

TEST_F(RecentlyUsedList_LIFO, LastAddedItemIsAtFront)
{
    rul.add("item4");

    ASSERT_THAT(rul.front(), Eq("item4"));
}

struct RecentlyUsedList_Indexing : RecentlyUsedList_WithItems
{
};

TEST_F(RecentlyUsedList_Indexing, ItemsCanBeLookedUpByIndex)
{
    ASSERT_THAT(rul[0], StrEq("item3"));
    ASSERT_THAT(rul[1], StrEq("item2"));
    ASSERT_THAT(rul[2], StrEq("item1"));
}

struct RecentlyUsedList_InsertingDuplicate : RecentlyUsedList_WithItems
{
};

TEST_F(RecentlyUsedList_InsertingDuplicate, SizeIsNotChanged)
{
    auto prev_size = rul.size();

    rul.add("item2");

    ASSERT_THAT(rul.size(), Eq(prev_size));
}

TEST_F(RecentlyUsedList_InsertingDuplicate, ItemIsMovedToFront)
{
    EXPECT_THAT(rul, ElementsAre("item3", "item2", "item1"));

    rul.add("item2");

    ASSERT_THAT(rul, ElementsAre("item2", "item3", "item1"));
}

TEST(RecentlyUsedList_BoundedCapacity, DefaultConstructor_SetsMaxCapacity)
{
    RecentlyUsedList rul;

    ASSERT_THAT(rul.capacity(), Eq(std::numeric_limits<size_t>::max()));
}

TEST(RecentlyUsedList_BoundedCapacity, ConstructorWithArg_CapacityIsSet)
{
    RecentlyUsedList rul(5);

    ASSERT_THAT(rul.capacity(), Eq(5u));
}

TEST(RecentlyUsedList_BoundedCapacity, WhenListIsFullAddingUniqueItemDropsItemAtBack)
{
    // Arrange
    RecentlyUsedList rul(3);

    rul.add("item1");
    rul.add("item2");
    rul.add("item3");

    EXPECT_THAT(rul.size(), Eq(rul.capacity()));

    // Act
    rul.add("item4");

    // Assert
    ASSERT_THAT(rul, ElementsAre("item4", "item3", "item2"));
}