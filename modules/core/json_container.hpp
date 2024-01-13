#ifndef JSON_CONTAINER_HPP
#define JSON_CONTAINER_HPP

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "container.hpp"

namespace json {

using namespace boost::property_tree;

}

namespace home::interactor {

class JSONContainer : public Container {
 private:
  std::string_view path;
  json::ptree json;

 protected:
  JSONContainer() = default;

 public:
  JSONContainer(const std::string_view &path);
  ~JSONContainer();

  void write(const std::string &filename, const std::string &filedata) override;

  std::string read(const std::string &filename) override;
};

}  // namespace home::interactor

#endif