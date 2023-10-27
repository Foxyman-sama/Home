#ifndef CONTROLLER_TESTS_DEF_HPP
#define CONTROLLER_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/adapters/webcontroller.hpp"
#include "modules/business_rules/interactor/boundary.hpp"
#include "../configtest.hpp"

using namespace home;

class MockBoundary
  : public interactor::Boundary {
public:
  MOCK_METHOD(void, writeFiles, (const interactor::InputData &), (override));
  MOCK_METHOD(interactor::OutputData, readFiles, (const interactor::InputData &), (override));
};

#endif
