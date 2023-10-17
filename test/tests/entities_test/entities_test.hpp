#ifndef TEST_ENTITIES_HPP
#define TEST_ENTITIES_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/entities/filemanipulatorimpl.hpp"

constexpr std::string_view gk_test_file { "test/test.txt" };
constexpr size_t gk_test_file_size { 100 };

class FileManipulatorImplTest
    : public testing::Test {
public:
    home::entities::FileManipulatorImpl *p_fm_;

    void SetUp() override { 
        p_fm_ = new  home::entities::FileManipulatorImpl { };
    }
    void TearDown() override {
        delete p_fm_;
    }
};

TEST_F(FileManipulatorImplTest, EmptyReadExpectThrow) {
    ASSERT_THROW(p_fm_->readFile(""), std::runtime_error);
}
TEST_F(FileManipulatorImplTest, BadFilenameReadExpectThrow) {
    ASSERT_THROW(p_fm_->readFile("f.txt"), std::runtime_error);
}
TEST_F(FileManipulatorImplTest, EmptyFilenameAndDataWriteExpectThrow) {
    ASSERT_THROW(p_fm_->writeFile("", { }), std::runtime_error);
}
TEST_F(FileManipulatorImplTest, EmptyFilenameWriteExpectThrow) {
    ASSERT_THROW(p_fm_->writeFile("", { 'f' }), std::runtime_error);
}
TEST_F(FileManipulatorImplTest, EmptyDataWriteExpectThrow) {
    ASSERT_THROW(p_fm_->writeFile(gk_test_file.data(), { }), std::runtime_error);
}
TEST_F(FileManipulatorImplTest, CorrectWriteAndCorrectRead) {
    std::vector<char> test_case { };
    for (size_t i { }; i < gk_test_file_size; ++i) {
        test_case.emplace_back('f');
    }
    
    ASSERT_NO_THROW(p_fm_->writeFile(gk_test_file.data(), test_case));
    ASSERT_EQ(p_fm_->readFile(gk_test_file.data()), test_case);
}
TEST_F(FileManipulatorImplTest, CorrectWriteAndCorrectRead1000Times) {
    for (size_t time { }; time < 1'000; ++time) {
        std::vector<char> test_case { };
        for (size_t i { }; i < gk_test_file_size; ++i) {
            test_case.emplace_back('f');
        }

        ASSERT_NO_THROW(p_fm_->writeFile(gk_test_file.data(), test_case));
        ASSERT_EQ(p_fm_->readFile(gk_test_file.data()), test_case);
    }
}

#endif
