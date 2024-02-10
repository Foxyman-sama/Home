#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include "test_base.hpp"

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

TEST_F(InteractorTest, Call_encode_and_saveFiles_call_encode_and_write) {
  EXPECT_CALL(container, write(_, _));
  interactor.save({ { "", "" } });
}
TEST_F(InteractorTest, Call_decode_and_getFile_call_read_and_decode) {
  EXPECT_CALL(container, read(_));
  interactor.get("");
}

#endif