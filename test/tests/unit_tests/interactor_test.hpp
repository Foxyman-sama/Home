#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "modules/core/interactor_impl.hpp"
#include "modules/core/json_container.hpp"
#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace interactor;
using namespace crypto;
using namespace container;

class MockEncoder : public Base64Encoder {
 public:
  MOCK_METHOD((std::string), encode, (const std::string &), (override));
};
class MockDecoder : public Base64Decoder {
 public:
  MOCK_METHOD((std::string), decode, (const std::string &), (override));
};
class MockContainer : public JSONContainer {
 public:
  MOCK_METHOD(void, write, (const std::string &, const std::string &), (override));
  MOCK_METHOD((std::string), read, (const std::string &), (override));
};
class InteractorTest : public Test {
 public:
  InteractorImpl interactor;
  MockContainer container;

  InteractorTest() : interactor { container } {}
};

TEST_F(InteractorTest, Call_encode_and_save_call_encode_and_write) {
  EXPECT_CALL(container, write(_, _));
  interactor.encodeAndSave(generateFiles<std::string, std::string>(1, 1));
}
TEST_F(InteractorTest, Call_decode_and_get_call_read_and_decode) {
  EXPECT_CALL(container, read(_));
  interactor.decodeAndGet("");
}

#endif