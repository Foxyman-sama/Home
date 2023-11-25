#ifndef HOME_SERIALIZER_IMPL_HPP
#define HOME_SERIALIZER_IMPL_HPP

#include "adapters_api.hpp"
#include "serializer.hpp"

namespace home::adapters {
class AdaptersAPI SerializerImpl 
  : public Serializer {
public:
  std::vector<char> serialize(const interactor::Files &files) override;
};
}

#endif
