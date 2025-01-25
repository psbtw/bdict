#include "hashMapDict.hpp"

template<std::totally_ordered K, std::totally_ordered V>
class MixDict {
private:
    HashMapDict<K, V> full_dict;
    HashMapDict<K, V> initial_dict; //only match initials
    int _initial_dict_len = 20;
    inline static Pinyin::PinyinParser parser;
public:
    MixDict();
    // MixDict(K& k,V& v);
    // MixDict(K& k);
    // ~MixDict();
    // MixDict* Find(const std::vector<K>& key, int&);
    bool Insert(const std::vector<K>& key, const V&& data);
    bool InsertFirstN(const std::vector<K>& key, const V&& data, int n){return false;}
    void BuildDict(const string&);
    vector<string_view> MatchWords(const string& s);


};