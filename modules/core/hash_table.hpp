#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <unordered_map>

template <typename Key, typename Value>
using HashTable = std::unordered_map<Key, Value>;

#endif