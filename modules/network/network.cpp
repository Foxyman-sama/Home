#include "network.hpp"

namespace home::network {
class Network::Impl { 
private:
    boost::asio::io_context io_;

public:
    
};

Network::Network() noexcept 
    : p_impl_ { new Impl { } } {
   
}
Network::~Network() noexcept {
    delete p_impl_;
}
}