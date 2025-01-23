#include "hashMapDict.hpp"

template<std::totally_ordered K, std::totally_ordered V>
class MixDict {
private:
    HashMapDict<K, V> full_dict;
    HashMapDict<K, V> initial_dict; //only match initials
public:
    MixDict();
    // MixDict(K& k,V& v);
    // MixDict(K& k);
    // ~MixDict();
    // MixDict* find(const std::vector<K>& key, int&);
    bool Insert(std::vector<K>& key, const V&& data);
    void BuildDict(const string&);
    vector<string_view> MatchWords(const string& s);


};