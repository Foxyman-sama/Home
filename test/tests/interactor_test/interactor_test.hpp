#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/business_rules/interactor/interactor.hpp"
 
class InteractorTest
    : public testing::Test {
private:
    home::entities::FileManipulatorImpl impl_;

public:
    home::interactor::UseCaseInteractor *p_intr_;

    void SetUp() override {
        p_intr_ = new home::interactor::UseCaseInteractor { impl_ };
    }
    void TearDown() override {
        delete p_intr_;
    }
};
 
TEST_F(InteractorTest, EmptyReadExpectThrow) {
    ASSERT_THROW(p_intr_->readFiles({ }), std::runtime_error);
}
TEST_F(InteractorTest, EmptyFilenameExpectThrow) {
    ASSERT_THROW(p_intr_->readFiles({ " " }), std::runtime_error);
}
TEST_F(InteractorTest, EmptyWriteExpectThrow) {
    ASSERT_THROW(p_intr_->writeFiles({ }), std::runtime_error);
}
TEST_F(InteractorTest, EmptyFilenameAndDataExpectThrow) {
    std::unordered_map<std::string, std::vector<char>> test_case { };
    test_case[""] = { };
    ASSERT_THROW(p_intr_->writeFiles(test_case), std::runtime_error);
}

#endif
