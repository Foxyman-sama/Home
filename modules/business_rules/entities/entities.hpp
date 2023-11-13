#ifndef HOME_ENTITIES_HPP
#define HOME_ENTITIES_HPP

#include <fstream>
#include <string>
#include <vector>
#include "../business_rules_api.hpp"

namespace home::entities {
namespace read {
class BRAPI ReadStream {
public:
    virtual std::vector<char> read() = 0;
};
class BRAPI FileReadStream
  : public ReadStream {
private:
  std::ifstream in_stream;

  void tryOpen(const std::string &filename);

  void throwException(const std::string &filename);

public:
  explicit FileReadStream(const std::string &filename);
  std::vector<char> read() override;
};

class BRAPI ReadStreamFactory {
public:
  virtual std::shared_ptr<ReadStream> create(const std::string &) = 0;
};
class BRAPI FileReadStreamFactory 
  : public ReadStreamFactory {
public:
  std::shared_ptr<ReadStream> create(const std::string &filename) override;
};
}
namespace write {
class BRAPI WriteStream {
public:
    virtual void write(const std::vector<char> &) = 0;
};
class BRAPI FileWriteStream
  : public WriteStream {
private:
  std::ofstream out_stream;

  void tryOpen(const std::string &filename);

  void throwException(const std::string &filename);

public:
  explicit FileWriteStream(const std::string &filename);

  void write(const std::vector<char> &data) override;

  bool isOpen() const noexcept;
};

class BRAPI WriteStreamFactory {
public:
	virtual std::shared_ptr<WriteStream> create(const std::string &) = 0;
};
class BRAPI FileWriteStreamFactory
  : public WriteStreamFactory {
public:
  std::shared_ptr<WriteStream> create(const std::string &filename) override;
};
}
}

#endif
