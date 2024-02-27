#ifndef POST_DELIMS_HPP
#define POST_DELIMS_HPP

#include <string>
#include <string_view>

namespace home::webserver {

struct Boundary {
  static constexpr std::string_view chrome { "------WebKitForm" };
  static constexpr std::string_view firefox { "-----------------------------" };
};

struct Delims {
  static constexpr std::string_view name_matcher_beg { "filename=\"" };
  static constexpr std::string_view name_matcher_end { "\"" };
  static constexpr std::string_view file_matcher_beg { "\r\n\r\n" };
};

struct ErrorMessages {
  static constexpr std::string_view bad_target { "Unknown target" };
  static constexpr std::string_view bad_request { "Unknown method" };
  static constexpr std::string_view empty_post { "The post request is empty" };
};

inline bool isPostHTMLBroken(const std::string &html) noexcept {
  if ((html.find(Boundary::chrome) == std::string::npos) && (html.find(Boundary::firefox) == std::string::npos)) {
    return true;
  } else if ((html.find(Delims::name_matcher_beg) == std::string::npos) &&
             (html.find(Delims::name_matcher_end) == std::string::npos)) {
    return true;
  }

  return false;
}

inline bool isHTMLEmpty(const std::string &body) noexcept { return body.empty() == true; }
// TODO - clear this mess somehow
}  // namespace  home::webserver

#endif