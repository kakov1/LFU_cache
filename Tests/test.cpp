#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include "../Cache/cache.hpp"
#include "../Cache/ideal_cache.hpp"

const int LFU = 0;
const int IDEAL = 1;
const char* LFU_ANSWERS = "../lfu_answers.txt";
const char* IDEAL_ANSWERS = "../ideal_answers.txt";

size_t get_answer(int test_number, const char* filename) {
    std::vector<size_t> answers;
    
    std::fstream test_file(filename);

    size_t buf;

    while (test_file >> buf) {
        answers.push_back(buf);
    }
    
    return answers[test_number - 1];


}
size_t test(int test_number, int cache_algorithm) {
    std::fstream test_file("../" + std::to_string(test_number) + "test.txt");
    std::cin.rdbuf(test_file.rdbuf()); 

    size_t cache_size, pages_amount;

    std::cin >> cache_size >> pages_amount;


    if (cache_algorithm == LFU) {
        cache_t<size_t, size_t> test_cache(cache_size, pages_amount);
        test_cache.processing_cache();
        return test_cache.hits;
    }
    else {
        ideal_cache_t<size_t, size_t> test_cache(cache_size, pages_amount);
        test_cache.processing_cache();
        return test_cache.hits;
    }

}

TEST(tests, test1) {
    EXPECT_EQ(test(1, LFU), get_answer(1, LFU_ANSWERS));
    EXPECT_EQ(test(1, IDEAL), get_answer(1, IDEAL_ANSWERS));
}

TEST(tests, test2) {
    EXPECT_EQ(test(2, LFU), get_answer(2, LFU_ANSWERS));
    EXPECT_EQ(test(2, IDEAL), get_answer(2, IDEAL_ANSWERS));
}

TEST(tests, test3) {
    EXPECT_EQ(test(3, LFU), get_answer(3, LFU_ANSWERS));
    EXPECT_EQ(test(3, IDEAL), get_answer(3, IDEAL_ANSWERS));
}

TEST(tests, test4) {
    EXPECT_EQ(test(4, LFU), get_answer(4, LFU_ANSWERS));
    EXPECT_EQ(test(4, IDEAL), get_answer(4, IDEAL_ANSWERS));
}

TEST(tests, test5) {
    EXPECT_EQ(test(5, LFU), get_answer(5, LFU_ANSWERS));
    EXPECT_EQ(test(5, IDEAL), get_answer(5, IDEAL_ANSWERS));
}

TEST(tests, test6) {
    EXPECT_EQ(test(6, LFU), get_answer(6, LFU_ANSWERS));
    EXPECT_EQ(test(6, IDEAL), get_answer(6, IDEAL_ANSWERS));
}

TEST(tests, test7) {
    EXPECT_EQ(test(7, LFU), get_answer(7, LFU_ANSWERS));
    EXPECT_EQ(test(7, IDEAL), get_answer(7, IDEAL_ANSWERS));
}

TEST(tests, test8) {
    EXPECT_EQ(test(8, LFU), get_answer(8, LFU_ANSWERS));
    EXPECT_EQ(test(8, IDEAL), get_answer(8, IDEAL_ANSWERS));
}

TEST(tests, test9) {
    EXPECT_EQ(test(9, LFU), get_answer(9, LFU_ANSWERS));
    EXPECT_EQ(test(9, IDEAL), get_answer(9, IDEAL_ANSWERS));
}

TEST(tests, test10) {
    EXPECT_EQ(test(10, LFU), get_answer(10, LFU_ANSWERS));
    EXPECT_EQ(test(10, IDEAL), get_answer(10, IDEAL_ANSWERS));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}