#pragma once

#include <stddef.h>
#include <unordered_map>
#include "../bcommon/container/sorted_vector.hpp"
#include "../bcommon/common/debug.hpp"
#include "wordNode.hpp"
#include "pinyinEncoder/types.hpp"
#include "pinyinEncoder/parser.hpp"

// template<typename T>
// concept ArrayType = requires(T t){
//     t[0] == t[1]; // operator[] and operator == of elements
//     t.size();
// };

// template<typename V>
// concept Insertable = requires(V v){
//     v.insert();
// };

//template<std::totally_ordered K, std::totally_ordered V>
template<typename K, typename V>
class HashMapDict
{
private:
    K key;
    SortedVector<V> data;
    std::unordered_map<K,HashMapDict<K,V>> sub;
    static Pinyin::PinyinParser parser;
public:
    HashMapDict();
    HashMapDict(K& k,V& v);
    HashMapDict(const K& k);
    //~HashMapDict();
    HashMapDict* Find(const std::vector<K>& key, int&);
    bool Insert(const std::vector<K>& key, const V&& data);
    bool InsertFirstN(const std::vector<K>& key, const V&& data, int n);
    void BuildDict(const string&);

    bool LookUpByAlphabet(const Pinyin::PinyinVec& p, SortedVector<V>& res);
    vector<string> MatchWords(const string& s);

    SortedVector<V>& get_data() {
        return data;
    }
    //SetParser(Pinyin::PinyinParser* parser) {parser = parser;}
};


struct WordEntry {
    std::string word;
    std::vector<std::string> pinyin;

    size_t freq;
};
std::vector<WordEntry>* parseInput(const std::string& filePath);

using K_t = Pinyin::Alphabet;
using D_t = WordNode<string>;


int testHashMapDict(int argc, char* argv[]);