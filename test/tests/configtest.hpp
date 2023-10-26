#ifndef TEST_CONFIG_HPP
#define TEST_CONFIG_HPP

#include <string_view>
#include <filesystem>

inline const std::string path_test_directory { "files/test/" };
inline const std::string test_filename { "test.txt" };
constexpr size_t test_file_size { 100'000 };

void createTestDirectory() noexcept {
    std::filesystem::create_directories(path_test_directory);
}
void deleteFilesFromTestDirectory() noexcept {
    std::filesystem::remove_all(path_test_directory);
}
void recreateTestDirectory() noexcept {
    deleteFilesFromTestDirectory();
    createTestDirectory();
}
std::string createFilename(size_t index) {
  return path_test_directory + std::to_string(index) + test_filename;
}

#endif
