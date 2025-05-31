#include <gtest/gtest.h>
#include "cyclicList.h"

TEST(CyclicListTest, DefaultConstructor) {
    CyclicList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(CyclicListTest, InitializerListConstructor) {
    CyclicList<int> list = {1, 2, 3};
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3);
}

TEST(CyclicListTest, PushBack) {
    CyclicList<int> list;
    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(CyclicListTest, PushFront) {
    CyclicList<int> list;
    list.push_front(1);
    list.push_front(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 1);
}

TEST(CyclicListTest, PopFront) {
    CyclicList<int> list = {1, 2, 3};
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
}

TEST(CyclicListTest, PopBack) {
    CyclicList<int> list = {1, 2, 3};
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(CyclicListTest, Iterator) {
    CyclicList<int> list = {1, 2, 3};
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(CyclicListTest, ConstIterator) {
    const CyclicList<int> list = {1, 2, 3};
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(CyclicListTest, Insert) {
    CyclicList<int> list = {1, 3};
    auto it = list.begin();
    ++it;
    list.insert(it, 2);
    
    std::vector<int> result;
    for (auto item : list) {
        result.push_back(item);
    }
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST(CyclicListTest, Erase) {
    CyclicList<int> list = {1, 2, 3};
    auto it = list.begin();
    ++it;
    list.erase(it);
    
    std::vector<int> result;
    for (auto item : list) {
        result.push_back(item);
    }
    EXPECT_EQ(result, std::vector<int>({1, 3}));
}

TEST(CyclicListTest, Clear) {
    CyclicList<int> list = {1, 2, 3};
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(CyclicListTest, Equality) {
    CyclicList<int> list1 = {1, 2, 3};
    CyclicList<int> list2 = {1, 2, 3};
    CyclicList<int> list3 = {1, 2};
    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 == list3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}