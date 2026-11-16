#include "project/map.h"

#include <iostream>

int main() {
    Map map;
    map.insert("banana", 2);
    map.insert("apple", 1);
    map.update("apple", 3);

    for (const auto& key : map.keys()) {
        std::cout << key << ": " << map.at(key) << '\n';
    }
}
