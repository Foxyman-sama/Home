#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>

#include "modules/core/controller_impl.hpp"
#include "modules/core/decoder_base64.hpp"
#include "modules/core/encoder_base64.hpp"
#include "modules/core/interactor_impl.hpp"
#include "modules/core/json_container.hpp"
#include "modules/webserver/html_parser.hpp"
#include "modules/webserver/webserver.hpp"

using namespace home::controller;
using namespace home::webserver;
using namespace home::interactor;
using namespace testing;
using std::begin, std::end;
using std::ranges::views::zip;

#endif