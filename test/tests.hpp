#ifndef TESTS_CORE_HPP
#define TESTS_CORE_HPP

#include "tests/integration_tests/write_get_filenames_test.hpp"
#include "tests/integration_tests/write_read_test.hpp"
#include "tests/unit_tests/controller_test.hpp"
#include "tests/unit_tests/decoder_test.hpp"
#include "tests/unit_tests/encoder_decoder_test.hpp"
#include "tests/unit_tests/encoder_test.hpp"
#include "tests/unit_tests/interactor_test.hpp"
#include "tests/unit_tests/jsonoutput_test.hpp"
#include "tests/unit_tests/parser_test.hpp"
#include "tests/unit_tests/webserver_test.hpp"

int startTests(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
