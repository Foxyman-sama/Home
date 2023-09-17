#ifndef LOCALHOST_CORE_INCLUDE_HPP
#define LOCALHOST_CORE_INCLUDE_HPP

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace local::core {
namespace net = boost::asio;
namespace ip = boost::asio::ip;

using TCP = ip::tcp;
using Socket = TCP::socket;
using Endpoint = TCP::endpoint;
using Acceptor = TCP::acceptor;
using Error = boost::system::error_code;
using Size = unsigned long long;
using Data = std::vector<char>;
}

#endif
