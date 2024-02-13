#ifndef NET_LIB_HPP
#define NET_LIB_HPP

#include <boost/beast.hpp>

namespace net {

using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;
using Acceptor = tcp::acceptor;
using Socket = tcp::socket;

}  // namespace net

#endif