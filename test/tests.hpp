#ifndef TESTS_CORE_HPP
#define TESTS_CORE_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

int startTests(int _argc, char **_p_argv) {
  testing::InitGoogleTest(&_argc, _p_argv);
  testing::InitGoogleMock(&_argc, _p_argv);
  return RUN_ALL_TESTS();
}

#endif
