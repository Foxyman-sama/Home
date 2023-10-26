#ifndef INTERACTOR_TESTS_DEF_HPP
#define INTERACTOR_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/business_rules/interactor/interactor.hpp"
#include "modules/business_rules/entities/filereadstreamfactory.hpp"
#include "modules/business_rules/entities/filewritestreamfactory.hpp"
#include "../configtest.hpp"

class InteractorTest 
  : public testing::Test {
public:
  std::unique_ptr<home::interactor::Interactor> interactor;
  std::unique_ptr<home::entities::FileReadStreamFactory> read_factory;
  std::unique_ptr<home::entities::FileWriteStreamFactory> write_factory;

  void SetUp() override {
    read_factory.reset(new home::entities::FileReadStreamFactory { });
    write_factory.reset(new home::entities::FileWriteStreamFactory { });
    interactor.reset(new home::interactor::Interactor { path_test_directory, *write_factory, *read_factory });
  }
};

#endif
