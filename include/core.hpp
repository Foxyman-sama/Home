#ifndef LOCALHOST_CORE_INCLUDE_HPP
#define LOCALHOST_CORE_INCLUDE_HPP

#include <boost/asio.hpp>

namespace local::core {
namespace ip = boost::asio::ip;

using TCP = ip::tcp;
using Socket = TCP::socket;
using Endpoint = TCP::endpoint;
using Acceptor = TCP::acceptor;
using Error = boost::system::error_code;
using Size = unsigned long long;
using Data = std::vector<char>;

inline boost::asio::io_context g_io_context { };
}

#endif
