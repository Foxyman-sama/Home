#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>

#include "controller_impl.hpp"
#include "decoder_base64.hpp"
#include "encoder_base64.hpp"
#include "html_parser.hpp"
#include "interactor_impl.hpp"
#include "json_container.hpp"
#include "webserver.hpp"

using namespace home::controller;
using namespace home::webserver;
using namespace home::interactor;
using namespace home::container;
using namespace home::crypto;
using namespace testing;
using std::begin, std::end;
using std::ranges::for_each;
using std::ranges::views::zip;

#endif