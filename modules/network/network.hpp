#include <boost/asio.hpp>

#ifdef Network_EXPORTS
#define NETAPI __declspec(dllexport)
#else
#define NETAPI __declspec(dllimport)
#endif

namespace home::network {
class NETAPI Network {
private: 
    class Impl;

    Impl *p_impl_;

public:
    Network() noexcept;
    ~Network() noexcept;
};
}