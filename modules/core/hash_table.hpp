#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <ranges>
#include <unordered_map>

template <typename Key, typename Value>
class HashTable {
 private:
  std::unordered_map<Key, Value> hash_table;

 public:
  HashTable() = default;
  HashTable(std::initializer_list<std::pair<const Key, Value>> &&list) : hash_table { std::move(list) } {}

  void emplace(std::pair<Key, Value> &&pair) noexcept { hash_table.emplace(std::move(pair)); }
  void emplace(const Key &key, const Value &value) noexcept { hash_table.emplace(key, value); }

  Value &at(const Key &key) { return hash_table.at(key); }

  size_t getSize() const noexcept { return hash_table.size(); }

  auto begin() const noexcept { return hash_table.begin(); }
  auto end() const noexcept { return hash_table.end(); }

  constexpr bool operator==(const HashTable<Key, Value> &other) const noexcept {
    return this->hash_table == other.hash_table;
  };
};

#endif