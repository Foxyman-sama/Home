#ifndef TESTS_CORE_HPP
#define TESTS_CORE_HPP

#include "tests/integration_tests/encoding_decoding_test.hpp"
#include "tests/integration_tests/sending_test.hpp"
#include "tests/unit_tests/controller_test.hpp"
#include "tests/unit_tests/parser_test.hpp"

int startTests(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
