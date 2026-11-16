#include "project/map.h"

#include <algorithm>
#include <stdexcept>

Map::Map() = default;

bool Map::empty() const noexcept {
    return entries_.empty();
}

std::size_t Map::size() const noexcept {
    return entries_.size();
}

std::size_t Map::lowerBoundIndex(const std::string& key) const {
    // Sorted entries let us find a key or its insertion position in O(log n).
    const auto position = std::lower_bound(entries_.begin(), entries_.end(), key,
        [](const KeyValuePair& entry, const std::string& target) {
            return entry.key < target;
        });
    return static_cast<std::size_t>(position - entries_.begin());
}

std::size_t Map::findIndex(const std::string& key) const {
    const std::size_t index = lowerBoundIndex(key);
    return index < size() && entries_[index].key == key ? index : size();
}

bool Map::contains(const std::string& key) const {
    return findIndex(key) != size();
}

bool Map::insert(const std::string& key, int value) {
    const std::size_t index = lowerBoundIndex(key);
    if (index < size() && entries_[index].key == key) {
        return false;
    }
    entries_.insert(entries_.begin() + index, KeyValuePair{key, value});
    return true;
}

bool Map::update(const std::string& key, int newValue) {
    const std::size_t index = findIndex(key);
    if (index == size()) {
        return false;
    }
    entries_[index].value = newValue;
    return true;
}

bool Map::erase(const std::string& key) {
    const std::size_t index = findIndex(key);
    if (index == size()) {
        return false;
    }
    entries_.erase(entries_.begin() + index);
    return true;
}

int Map::at(const std::string& key) const {
    const std::size_t index = findIndex(key);
    if (index == size()) {
        throw std::out_of_range("Key not found");
    }
    return entries_[index].value;
}

int& Map::at(const std::string& key) {
    const std::size_t index = findIndex(key);
    if (index == size()) {
        throw std::out_of_range("Key not found");
    }
    return entries_[index].value;
}

std::vector<std::string> Map::keys() const {
    std::vector<std::string> result;
    for (const auto& entry : entries_) {
        result.push_back(entry.key);
    }
    return result;
}

std::vector<int> Map::values() const {
    std::vector<int> result;
    for (const auto& entry : entries_) {
        result.push_back(entry.value);
    }
    return result;
}

bool Map::isSorted() const noexcept {
    for (std::size_t i = 1; i < entries_.size(); ++i) {
        if (entries_[i - 1].key > entries_[i].key) {
            return false;
        }
    }
    return true;
}
