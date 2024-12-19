#ifndef PROJECT_ESPRIT_MODEL_C_HASHTABLE_H
#define PROJECT_ESPRIT_MODEL_C_HASHTABLE_H

#include <vector>
#include <optional>
#include "DoubleList.h"

// Hash Node
template <typename K, typename V>
struct HashNode {
    K key;
    V value;

    HashNode(K key, V value) : key(key), value(value) {}

    // Comparison operator for equality
    bool operator==(const HashNode<K, V>& other) const {
        return key == other.key && value == other.value;
    }
};


// HashTable Class
template <typename K, typename V>
class HashTable {
private:
    int BUCKET_COUNT = 100;  // Default bucket count
    std::vector<DoubleList<HashNode<K, V>>> table;

    int hash_function(const K& key) const {
        return std::hash<K>()(key) % BUCKET_COUNT;
    }

public:
    HashTable() : table(BUCKET_COUNT) {}

    void insert(const K& key, const V& value) {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                node.value = value;  // Update if key exists
                return;
            }
        }

        bucket.push_back(HashNode<K, V>(key, value));
    }

    V get(const K& key) const {
        int index = hash_function(key);
        const auto& bucket = table[index];
        for (const auto& node : bucket) {
            if (node.key == key) {
                return node.value;  // Return the found value
            }
        }
        throw std::out_of_range("Key not found");  // Throw an exception if the key is not found
    }

    bool remove(const K& key) {
        int index = hash_function(key);
        auto& bucket = table[index];
        for (auto& node : bucket) {
            if (node.key == key) {
                bucket.remove(node);  // Remove the node
                return true;          // Indicate success
            }
        }
        return false;  // Indicate failure
    }


    bool contains(const K& key) const {
        int index = hash_function(key);
        const auto& bucket = table[index];

        for (const auto& node : bucket) {
            if (node.key == key) {
                return true;
            }
        }

        return false;
    }

    std::vector<HashNode<K, V>> getAllNodes() const {
        std::vector<HashNode<K, V>> allNodes;

        for (const auto& bucket : table) {
            for (const auto& node : bucket) {
                allNodes.push_back(node);  // Collect all nodes in the vector
            }
        }

        return allNodes;
    }

    void resizeTable(int newBucketCount) {
        std::vector<DoubleList<HashNode<K, V>>> newTable(newBucketCount);

        for (const auto& bucket : table) {
            for (const auto& node : bucket) {
                int newIndex = std::hash<K>()(node.key) % newBucketCount;
                newTable[newIndex].push_back(node);
            }
        }

        table = std::move(newTable);  // Replace the old table with the resized one
        BUCKET_COUNT = newBucketCount;
    }

};

#endif // PROJECT_ESPRIT_MODEL_C_HASHTABLE_H



