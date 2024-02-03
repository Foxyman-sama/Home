#ifndef JSON_CONTAINER_HPP
#define JSON_CONTAINER_HPP

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace json {

using namespace boost::property_tree;

}

namespace home::container {

class JSONContainer {
 private:
  std::string_view path;
  json::ptree json;

 protected:
  JSONContainer() = default;

 public:
  JSONContainer(const std::string_view &path);
  ~JSONContainer();

  virtual void write(const std::string &filename, const std::string &filedata);

  virtual std::string read(const std::string &filename);

  void extractToFile() noexcept;
};

}  // namespace home::container

#endif