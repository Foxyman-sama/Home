#ifndef TEST_ENCODER_HPP
#define TEST_ENCODER_HPP

#include "test_base.hpp"

class EncoderTest : public Test {
 private:
  Base64Encoder encoder;
  std::vector<std::string> inputs;
  std::vector<std::string> expected;
  std::vector<std::string> actual;

 public:
  void appendInputs(std::vector<std::string> range) { inputs.insert(end(inputs), begin(range), end(range)); }
  void appendExpected(std::vector<std::string> range) { expected.insert(end(expected), begin(range), end(range)); }

  void encode() {
    for_each(inputs, [this](const auto &str) { actual.emplace_back(encoder.encode(str)); });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(EncoderTest, Encoding_empty_input_data) {
  appendInputs({});
  appendExpected({});

  encode();

  assertActualIsEqualExpected();
}
TEST_F(EncoderTest, Encoding_one_char) {
  appendInputs({ "Q" });
  appendExpected({ "UQ==" });

  encode();

  assertActualIsEqualExpected();
}
TEST_F(EncoderTest, Encoding_one_word) {
  appendInputs({ "Amazing" });
  appendExpected({ "QW1hemluZw==" });

  encode();

  assertActualIsEqualExpected();
}
TEST_F(EncoderTest, Encoding_lorem_ipsum) {
  appendInputs(
      { "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum "
        "sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies "
        "nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, "
        "aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam "
        "dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean "
        "vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem "
        "ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet." });
  appendExpected(
      { "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVlciBhZGlwaXNjaW5nIGVsaXQuIEFlbmVhbiBjb21tb2RvIGxpZ3VsYSBlZ2"
        "V0"
        "IGRvbG9yLiBBZW5lYW4gbWFzc2EuIEN1bSBzb2NpaXMgbmF0b3F1ZSBwZW5hdGlidXMgZXQgbWFnbmlzIGRpcyBwYXJ0dXJpZW50IG1vbnRlcy"
        "wg"
        "bmFzY2V0dXIgcmlkaWN1bHVzIG11cy4gRG9uZWMgcXVhbSBmZWxpcywgdWx0cmljaWVzIG5lYywgcGVsbGVudGVzcXVlIGV1LCBwcmV0aXVtIH"
        "F1"
        "aXMsIHNlbS4gTnVsbGEgY29uc2VxdWF0IG1hc3NhIHF1aXMgZW5pbS4gRG9uZWMgcGVkZSBqdXN0bywgZnJpbmdpbGxhIHZlbCwgYWxpcXVldC"
        "Bu"
        "ZWMsIHZ1bHB1dGF0ZSBlZ2V0LCBhcmN1LiBJbiBlbmltIGp1c3RvLCByaG9uY3VzIHV0LCBpbXBlcmRpZXQgYSwgdmVuZW5hdGlzIHZpdGFlLC"
        "Bq"
        "dXN0by4gTnVsbGFtIGRpY3R1bSBmZWxpcyBldSBwZWRlIG1vbGxpcyBwcmV0aXVtLiBJbnRlZ2VyIHRpbmNpZHVudC4gQ3JhcyBkYXBpYnVzLi"
        "BW"
        "aXZhbXVzIGVsZW1lbnR1bSBzZW1wZXIgbmlzaS4gQWVuZWFuIHZ1bHB1dGF0ZSBlbGVpZmVuZCB0ZWxsdXMuIEFlbmVhbiBsZW8gbGlndWxhLC"
        "Bw"
        "b3J0dGl0b3IgZXUsIGNvbnNlcXVhdCB2aXRhZSwgZWxlaWZlbmQgYWMsIGVuaW0uIEFsaXF1YW0gbG9yZW0gYW50ZSwgZGFwaWJ1cyBpbiwgdm"
        "l2"
        "ZXJyYSBxdWlzLCBmZXVnaWF0IGEsIHRlbGx1cy4gUGhhc2VsbHVzIHZpdmVycmEgbnVsbGEgdXQgbWV0dXMgdmFyaXVzIGxhb3JlZXQu" });

  encode();

  assertActualIsEqualExpected();
}

#endif