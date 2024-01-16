#ifndef TEST_ENCODER_HPP
#define TEST_ENCODER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <modules/core/encoder_base64.hpp>

using namespace testing;
using namespace home;
using namespace crypto;

class EncoderTest : public Test {
 private:
  Base64Encoder encoder;
  std::string raw_data;
  std::string expected;
  std::string actual;

 public:
  void givenRawAndExpectedData(const std::string &raw_data, const std::string &expected) {
    this->raw_data = raw_data;
    this->expected = expected;
  }

  void whenEncoderIsEncoding() { actual = encoder.encode(raw_data); }

  void thenActualDataShouldBeEqualExpected() {
    ASSERT_EQ(actual.size(), expected.size());
    ASSERT_EQ(actual, expected);
  }
};

TEST_F(EncoderTest, Encoding_empty_input_data) {
  givenRawAndExpectedData("", "");
  whenEncoderIsEncoding();
  thenActualDataShouldBeEqualExpected();
}
TEST_F(EncoderTest, Encoding_one_char) {
  givenRawAndExpectedData("Q", "UQ==");
  whenEncoderIsEncoding();
  thenActualDataShouldBeEqualExpected();
}
TEST_F(EncoderTest, Encoding_one_word) {
  givenRawAndExpectedData("Amazing", "QW1hemluZw==");
  whenEncoderIsEncoding();
  thenActualDataShouldBeEqualExpected();
}
TEST_F(EncoderTest, Encoding_lorem_ipsum) {
  givenRawAndExpectedData(
      "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum "
      "sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies "
      "nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, "
      "aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam "
      "dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean "
      "vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem "
      "ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet.",
      "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVlciBhZGlwaXNjaW5nIGVsaXQuIEFlbmVhbiBjb21tb2RvIGxpZ3VsYSBlZ2V0"
      "IGRvbG9yLiBBZW5lYW4gbWFzc2EuIEN1bSBzb2NpaXMgbmF0b3F1ZSBwZW5hdGlidXMgZXQgbWFnbmlzIGRpcyBwYXJ0dXJpZW50IG1vbnRlcywg"
      "bmFzY2V0dXIgcmlkaWN1bHVzIG11cy4gRG9uZWMgcXVhbSBmZWxpcywgdWx0cmljaWVzIG5lYywgcGVsbGVudGVzcXVlIGV1LCBwcmV0aXVtIHF1"
      "aXMsIHNlbS4gTnVsbGEgY29uc2VxdWF0IG1hc3NhIHF1aXMgZW5pbS4gRG9uZWMgcGVkZSBqdXN0bywgZnJpbmdpbGxhIHZlbCwgYWxpcXVldCBu"
      "ZWMsIHZ1bHB1dGF0ZSBlZ2V0LCBhcmN1LiBJbiBlbmltIGp1c3RvLCByaG9uY3VzIHV0LCBpbXBlcmRpZXQgYSwgdmVuZW5hdGlzIHZpdGFlLCBq"
      "dXN0by4gTnVsbGFtIGRpY3R1bSBmZWxpcyBldSBwZWRlIG1vbGxpcyBwcmV0aXVtLiBJbnRlZ2VyIHRpbmNpZHVudC4gQ3JhcyBkYXBpYnVzLiBW"
      "aXZhbXVzIGVsZW1lbnR1bSBzZW1wZXIgbmlzaS4gQWVuZWFuIHZ1bHB1dGF0ZSBlbGVpZmVuZCB0ZWxsdXMuIEFlbmVhbiBsZW8gbGlndWxhLCBw"
      "b3J0dGl0b3IgZXUsIGNvbnNlcXVhdCB2aXRhZSwgZWxlaWZlbmQgYWMsIGVuaW0uIEFsaXF1YW0gbG9yZW0gYW50ZSwgZGFwaWJ1cyBpbiwgdml2"
      "ZXJyYSBxdWlzLCBmZXVnaWF0IGEsIHRlbGx1cy4gUGhhc2VsbHVzIHZpdmVycmEgbnVsbGEgdXQgbWV0dXMgdmFyaXVzIGxhb3JlZXQu");
  whenEncoderIsEncoding();
  thenActualDataShouldBeEqualExpected();
}

#endif