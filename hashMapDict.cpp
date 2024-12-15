#include "hashMapDict.hpp"
#include <string>
#include <vector>
#include <concepts>
#include "pinyinEncoder/types.hpp"
#include "wordNode.hpp"
#include "hashMapDict.hpp"
#include <iostream>
#include "pinyinEncoder/parser.hpp"

template <std::totally_ordered K, std::totally_ordered V>
HashMapDict<K, V>::HashMapDict()
{
}

template <std::totally_ordered K, std::totally_ordered V>
HashMapDict<K,V>::HashMapDict(K& k, V& v)
{
    key = k;
    data.emplace_back(v);
    //sub = std::unordered_map<K,HashMapDict<K,V>*>();
}

template<std::totally_ordered K, std::totally_ordered V>
HashMapDict<K,V>::HashMapDict(K& k)
{
    key = k;
}

// template<std::totally_ordered K, std::totally_ordered V>
// 
// HashMapDict<K,V>::~HashMapDict()
// {

// }

template <std::totally_ordered K, std::totally_ordered V>
HashMapDict<K,V>* HashMapDict<K, V>::find(const std::vector<K>& key, int& idx) //find nearest match
{
    HashMapDict<K,V>* tmp = this;
    auto sub = &this->sub;
    idx = 0;
    for (; idx<key.size(); ++idx) {
        if (!sub->count(key[idx]) ) {
            return tmp;
        }
        tmp = &sub->at(key[idx]);
        sub = &tmp->sub;
    }
    return tmp;
}

template <std::totally_ordered K, std::totally_ordered V>
bool HashMapDict<K, V>::Insert(std::vector<K>& key, V&& data)
{
    int idx;
    auto ptr = this->find(key, idx);
    //not found, add from the latest match
    for (; idx<key.size(); ++idx) {
        // if (ptr->sub.size() == 0) {
        //     ptr->sub = std::unordered_map<K, HashMapDict<K,V>*>();
        // }
        ptr->sub[key[idx]] = HashMapDict(key[idx]);
        ptr = &ptr->sub[key[idx]];
    }
    // found
    if (idx == key.size()) {
        ptr->data.insert(data);
        return true;
    }
    return true;
}

template <std::totally_ordered K, std::totally_ordered V>
vector<string_view> HashMapDict<K, V>::MatchWords(const vector<vector<K>>& keys) {
    SortedVector<V> res;
    for (const auto& k : keys) {
        int idx = 0;
        auto ptr = find(k, idx);
        if (idx == k.size())[[__glibc_likely]] {
            for (auto& v : ptr->get_data().get_data()) {
                res.insert(v);
            }
            log_trace("found exact match for key: {}, val: {}", k, ptr->get_data().get_data());
        } else {
            log_trace("didn't find exact match for key: {}", k);
        }
    }
    vector<string_view> ret(res.get_data().size());
    auto iter = ret.begin();
    for (const auto &node : res.get_data()) {
        ret.emplace(iter++, node.data);
    }
    log_trace("convert done.");
    return ret;
}

int main(int argc, char* argv[]){
    //auto dict = HashMapDict<Alphabet, WordNode<std::string> >;
    HashMapDict<K_t, D_t> dict;

    init_logger("./log.txt");
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    log_trace("start parse file");
    START(parse_file);
    auto parsedEntries = parseInput("./resources/dict.yml");
    log_trace("end parse file");
    END(parse_file);
    LOG(parse_file);
    Pinyin::PinyinParser parser;

    // Output the parsed entries
    START(BUILD_DICT)
    for (const auto& entry : *parsedEntries) {
        //std::cout << "Word: " << entry.word << ", Pinyin: ";
        vector<Pinyin::Alphabet> va;
        parser.StringVecToAlphaVec(entry.pinyin, va);
        //std::cout << ", Frequency: " << entry.freq << std::endl;
        dict.Insert(va, {entry.word, entry.freq});
    }
    END(BUILD_DICT)
    LOG(BUILD_DICT)
    log_info("words count: {}", parsedEntries->size());
    std::cout << "dict inited\n";
    delete parsedEntries;


    //test parse
    string s(argv[1]);
    log_info("try parse: {}", s);
    spdlog::flush_on(spdlog::level::trace);
    Graph<Pinyin::AlphaMark, Pinyin::MarkKey> g;
    Pinyin::PinyinParser p;
    p.ParseToGraph(g, s);
    auto res = g.DFS_ALL();
    log_info("got res: ");
    for (auto&v : *res) {
        log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* k){return string(k->data.s); }, ","));
    }
    p.ApplyFuzzyForGraph(g);
    auto res2 = g.DFS_ALL();
    vector<vector<K_t>> keys(res2->size());
    auto key = keys.begin();
    log_info("res after fuzzy: ");
    for (auto&v : *res2) {
        log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* k){return string(k->data.s); }, ","));
        vector<K_t> k(v.size());
        auto it = k.begin();
        for (const auto& m : v) {
            k.emplace(it++, m->data.a);
        }
        keys.emplace(key++, k);
    }

    //test match
    auto cadidates = dict.MatchWords(keys);
    delete res, res2;

    std::cout<<"done.\n";
}
