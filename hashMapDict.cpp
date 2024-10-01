#include "HashMapDict.hpp"
#include <string>
#include <vector>
#include <concepts>
#include "pinyinEncoder/consts.hpp"
#include "wordNode.hpp"
#include "hashMapDict.hpp"
#include <iostream>

template <std::totally_ordered K, std::totally_ordered V>
HashMapDict<K, V>::HashMapDict()
{
}

template <std::totally_ordered K, std::totally_ordered V>
HashMapDict<K,V>::HashMapDict(K k, V v)
{
    key = k;
    data.emplace_back(v);
    //sub = std::unordered_map<K,HashMapDict<K,V>*>();
}

template<std::totally_ordered K, std::totally_ordered V>
HashMapDict<K,V>::HashMapDict(K k)
{
    key = k;
}

// template<std::totally_ordered K, std::totally_ordered V>
// 
// HashMapDict<K,V>::~HashMapDict()
// {

// }

template <std::totally_ordered K, std::totally_ordered V>
HashMapDict<K,V> *HashMapDict<K, V>::find(std::vector<K> key, int& idx)
{
    HashMapDict<K,V>* tmp = this, sub = this->sub;
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

template <std::totally_ordered K, std::totally_ordered V>

bool HashMapDict<K, V>::insert(std::vector<K>, V data)
{
    int idx;
    auto ptr = this->find(key, idx);
    //not found, add from the latest match
    for (; idx<key.size(); ++idx) {
        // if (ptr->sub.size() == 0) {
        //     ptr->sub = std::unordered_map<K, HashMapDict<K,V>*>();
        // }
        ptr->sub[key[idx]] = HashMapDict<K,V>(key[idx]);
        ptr = ptr->sub[key[idx]];
    }
    // found
    if (idx == key.size()) {
        ptr->data.insert(data);
        return true;
    }
    return true;
}

int main(){
    //auto dict = HashMapDict<PinyinAlphabet, WordNode<std::string> >;
    HashMapDict<PinyinAlphabet, WordNode<std::string> > dict;
    std::cout << "dict inited\n";
}
