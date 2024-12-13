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
vector<string_view> HashMapDict<K, V>::MatchWords(const vector<vector<Pinyin::Alphabet>>& keys) {
    vector<string_view> res
    int idx = 0;
    for (const auto& v : keys) {
        auto 
    }
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
    log_info("res after fuzzy: ");
    for (auto&v : *res2) {
        log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* k){return string(k->data.s); }, ","));
    }
    delete res, res2;

    std::cout<<"done.\n";
}
