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
  for (auto i { 0 }; i < 100; ++i) {
    auto &first_call { EXPECT_CALL(encoder, encode(_)).Times(2) };
    EXPECT_CALL(container, write(_, _)).After(first_call);
    interactor.encodeAndSave(generateFiles<std::string, std::string>(1, 1));
  }
}
TEST_F(InteractorTest, Call_decode_and_get_call_read_and_decode) {
  for (auto i { 0 }; i < 100; ++i) {
    auto &first_call { EXPECT_CALL(encoder, encode(_)) };
    auto &second_call { EXPECT_CALL(container, read(_)).After(first_call) };
    EXPECT_CALL(decoder, decode(_)).After(second_call);
    interactor.decodeAndGet("");
  }
}

#endif