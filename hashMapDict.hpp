#pragma once

#include <stddef.h>
#include <unordered_map>
#include "../bcommon/container/sorted_vector.hpp"

template<typename T>
concept ArrayType = requires(T t){
    t[0] == t[1]; // operator[] and operator == of elements
    t.size();
};

template<typename V>
concept Insertable = requires(V v){
    v.insert();
};

template<std::totally_ordered K, std::totally_ordered V>

// K type require operator ==
class HashMapDict
{
private:
    K key;
    SortedVector<V> data;
    std::unordered_map<K,HashMapDict<K,V>*> sub;
public:
    HashMapDict();
    HashMapDict(K k,V v);
    HashMapDict(K k);
    //~HashMapDict();
    HashMapDict* find(std::vector<K> key, int&);
    bool insert(std::vector<K> key, V data);
};


