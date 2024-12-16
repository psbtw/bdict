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
bool HashMapDict<K, V>::Insert(std::vector<K>& key, const V& data)
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
    START(match_all)
    SortedVector<V> res;
    for (const auto& k : keys) {
        START(match_1)
        int idx = 0;
        auto ptr = find(k, idx);
        if (idx == k.size())[[__likely__]] {
            for (auto& v : ptr->get_data().Vec()) {
                res.insert(v);
            }
            log_trace("found exact match for key: {}, val: {}", parser.AlphabetVecToString(k), ptr->get_data().ToString());
        } else {
            log_trace("didn't find exact match for key: {}", parser.AlphabetVecToString(k));
        }
        END(match_1)
        LOG(match_1)
    }
    vector<string_view> ret(res.Vec().size());
    stringstream s;
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = res.Vec()[i].data;
        s << ret[i] << ", ";
    }
    END(match_all)
    LOG(match_all)
    log_trace("convert done, ret: {}", s.str());
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
        D_t w(entry.word, entry.freq);
        dict.Insert(va, w);
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
        log_info("dfs res: {}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* const &k){return string(k->data.s); }, ","));
    }
    p.ApplyFuzzyForGraph(g);
    auto res2 = g.DFS_ALL();
    vector<vector<K_t>> keys(res2->size());
    auto key = keys.begin();
    log_info("res after fuzzy: ");
    for (int i = 0; i<keys.size(); ++i) {
        const auto& v = (*res2)[i];
        log_info("route: {}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* const &k){return string(k->data.s); }, ","));
        vector<K_t> k(v.size());
        for (int j = 0; j<k.size(); ++j) {
            k[j] = v[j]->data.a;
        }
        keys[i] = k;
    }

    //test match
    auto cadidates = dict.MatchWords(keys);
    delete res, res2;

    std::cout<<"done.\n";
}
