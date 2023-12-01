#ifndef HOME_SERIALIZER_IMPL_HPP
#define HOME_SERIALIZER_IMPL_HPP

#include "adapters_api.hpp"
#include "serializer.hpp"
#include "binary_manipulation/binary_creator.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace home::adapters {

class AdaptersAPI SerializerImpl
  : public Serializer {
private:
  using JSON = boost::property_tree::ptree;
  using File = interactor::File;
  using Files = interactor::Files;

public:
  std::vector<char> serialize(const interactor::Files &files) override;

private:

};

}

#endif
