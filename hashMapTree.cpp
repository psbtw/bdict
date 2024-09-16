#include "hashMapTree.hpp"
#include <string>
#include <vector>

template<typename K, typename V>
requires ArrayType<K>
HashMapTree<K,V>::HashMapTree(K k, V v)
{
    key = k;
    value = v;
    //sub = std::unordered_map<K,HashMapTree<K,V>*>();
}

// template<typename K, typename V>
// requires ArrayType<K>
// HashMapTree<K,V>::~HashMapTree()
// {

// }

template <typename K, typename V>
requires ArrayType<K>
HashMapTree<K,V> *HashMapTree<K, V>::find(K& key, int& idx)
{
    HashMapTree<K,V>* tmp = this, sub = this->sub;
    idx = 0;
    for (; idx<key.size(); ++idx) {
        if (!sub ||!sub->count(key[idx]) ) {
            return tmp;
        }
        tmp = sub;
        sub = tmp->sub[key[idx]];
    }
    return tmp;
}

template <typename K, typename V>
requires ArrayType<K>
bool HashMapTree<K, V>::insert(K key, V value)
{
    int idx;
    auto ptr = this->find(key, idx);
    if (idx == key.size()) {
        ptr->value = value;
        return true;
    }
    //not found, add from the latest match
    for (; idx<key.size(); ++idx) {
        if (ptr->sub == nullptr) {
            ptr->sub = std::unordered_map<K, HashMapTree<K,V>*>();
        }
        ptr->sub[key[idx]] = HashMapTree<K,V>(key[idx], value);
    }
    return true;
}

int main(){
    auto tree = HashMapTree<std::string, std::vector<std::string>>("wo", {"我","窝"});
    tree.insert("wa", {"哇","蛙"});
    tree.insert("ni", {"你","泥"});
}