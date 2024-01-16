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
  MOCK_METHOD((std::vector<char>), encode, (const std::vector<char> &), (override));
};
class MockDecoder : public Base64Decoder {
 public:
  MOCK_METHOD((std::vector<char>), decode, (const std::vector<char> &), (override));
};
class MockContainer : public Container {
 public:
  MOCK_METHOD(void, write, (const std::string &, const std::string &), (override));
  MOCK_METHOD((std::string), read, (const std::string &), (override));
};

class InteractorTest : public Test {
 public:
  InteractorImpl interactor;
  MockEncoder encoder;
  MockDecoder decoder;
  MockContainer container;

  InteractorTest() : interactor { encoder, decoder, container } {}
};

TEST_F(InteractorTest, Call_encode_and_save_call_encode_and_write) {
  GTEST_SKIP();
  EXPECT_CALL(encoder, encode(_)).Times(100);
  EXPECT_CALL(container, write(_, _)).Times(100);
  interactor.encodeAndSave(generateFiles(100, 1));
}
TEST_F(InteractorTest, Call_decode_and_get_call_read_and_decode) {
  EXPECT_CALL(decoder, decode(_)).Times(100);
  EXPECT_CALL(container, read(_)).Times(100);
  for (auto i { 0 }; i < 100; ++i) {
    interactor.decodeAndGet("");
  }
}

#endif