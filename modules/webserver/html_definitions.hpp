#ifndef POST_DELIMS_HPP
#define POST_DELIMS_HPP

#include <string>
#include <string_view>

namespace home::webserver {

struct Delims {
  static constexpr std::string_view name_matcher_beg { "filename=\"" };
  static constexpr std::string_view name_matcher_end { "\"" };
  static constexpr std::string_view file_matcher_beg { "\r\n\r\n" };
  static constexpr std::string_view chrome_boundary { "------WebKitForm" };
  static constexpr std::string_view firefox_boundary { "-----------------------------" };
};
struct ErrorMessages {
  static constexpr std::string_view bad_target { "Unknown targetFile" };
  static constexpr std::string_view bad_request { "Unknown method" };
  static constexpr std::string_view empty_post { "The post request is empty" };
};

inline bool isHTMLBroken(const std::string &html) noexcept {
  if (html.empty() == true) {
    return true;
  } else if ((html.find(Delims::chrome_boundary) == std::string::npos) &&
             (html.find(Delims::firefox_boundary) == std::string::npos)) {
    return true;
  }

  return false;
}
// TODO - REFACTORING THIS MESS!
}  // namespace  home::webserver

#endif