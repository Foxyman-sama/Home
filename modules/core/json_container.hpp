#ifndef JSON_CONTAINER_HPP
#define JSON_CONTAINER_HPP

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "container.hpp"

namespace json {

using namespace boost::property_tree;

}

namespace home::container {

class JSONContainer : public Container {
 private:
  std::string_view path;
  json::ptree json;

 public:
  JSONContainer(const std::string_view &path = "");

  virtual void write(const std::string &filename, const std::string &filedata) override;

  virtual std::string read(const std::string &filename) override;

  virtual std::vector<std::string> getSavedFilenames() override;

  void extractToFile() noexcept;
};

}  // namespace home::container

#endif