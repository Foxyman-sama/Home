#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "modules/core/decoder_base64.hpp"
#include "modules/core/encoder_base64.hpp"
#include "modules/core/hash_table.hpp"
#include "modules/core/json_container.hpp"
#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace interactor;
using namespace crypto;

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

class Interactor {
 private:
  Base64Encoder &encoder;
  Base64Decoder &decoder;
  Container &container;

 public:
  Interactor(Base64Encoder &encoder, Base64Decoder &decoder, Container &container)
      : encoder { encoder }, decoder { decoder }, container { container } {}

  void encodeAndSave(const HashTable<std::string, std::vector<char>> &files) {
    for (auto &&[filename, filedata] : files) {
      auto encoded { encoder.encode(filedata) };
      std::string temp;
      std::copy(std::begin(encoded), std::end(encoded), std::back_inserter(temp));
      container.write(filename, temp);
    }
  }

  std::string decodeAndSave(const std::string &filename) {}
};

class InteractorTest : public Test {};

TEST_F(InteractorTest, Call_encode_and_save_call_encode_and_write) {
  MockEncoder encoder;
  MockDecoder decoder;
  MockContainer container;
  Interactor interactor { encoder, decoder, container };
  EXPECT_CALL(encoder, encode(_)).Times(100);
  EXPECT_CALL(container, write(_, _)).Times(100);
  interactor.encodeAndSave(generateFiles(100, 10));
}
TEST_F(InteractorTest, Call_decode_and_get_call_read_and_decode) {
  MockEncoder encoder;
  MockDecoder decoder;
  MockContainer container;
  Interactor interactor { encoder, decoder, container };
  EXPECT_CALL(encoder, encode(_)).Times(100);
  EXPECT_CALL(container, read(_)).Times(100);
  interactor.encodeAndSave(generateFiles(100, 10));
}

#endif