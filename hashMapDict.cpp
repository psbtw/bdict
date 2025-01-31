#include "hashMapDict.hpp"
#include <string>
#include <vector>
#include <concepts>
#include "pinyinEncoder/types.hpp"
#include "wordNode.hpp"
#include "hashMapDict.hpp"
#include <iostream>
#include <fstream>
#include "pinyinEncoder/parser.hpp"

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
HashMapDict<K, V>::HashMapDict()
{
    parser = Pinyin::PinyinParser();
}

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
HashMapDict<K,V>::HashMapDict(K& k, V& v)
{
    key = k;
    data.emplace_back(v);
    parser = Pinyin::PinyinParser();
    //sub = std::unordered_map<K,HashMapDict<K,V>*>();
}

//template<std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
HashMapDict<K,V>::HashMapDict(const K& k)
{
    key = k;
    parser = Pinyin::PinyinParser();
}

// template<std::totally_ordered K, std::totally_ordered V>
// 
// HashMapDict<K,V>::~HashMapDict()
// {

// }

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
HashMapDict<K,V>* HashMapDict<K, V>::Find(const std::vector<K>& key, int& idx) //Find nearest match
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

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
bool HashMapDict<K, V>::Insert(const std::vector<K>& key, const V&& data)
{
    int idx;
    auto ptr = this->Find(key, idx);
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

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
bool HashMapDict<K, V>::InsertFirstN(const std::vector<K>& key, const V&& data, int n)
{
    int idx;
    auto ptr = this->Find(key, idx);
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
        ptr->data.insertFisrtN(data, n);
        return true;
    }
    return true;
}

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
void HashMapDict<K, V>::BuildDict(const string& filePath)
{
    //auto entries = new std::vector<WordEntry>();
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    START(BUILD_DICT)
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        WordEntry entry;
        std::string pinyinPart;
        std::string freqPart;

        // Read the word
        lineStream >> entry.word;
        if (entry.word[0] == '#') {
            //spdlog::trace("meet comment: {}", entry.word);
            continue;
        }

        // Read the pinyin (until the last part which is the frequency)
        while (lineStream >> pinyinPart) {
            if (std::isdigit(pinyinPart[0])) {
                freqPart = pinyinPart; // Last part is frequency
                break;
            }
            entry.pinyin.emplace_back(pinyinPart);
        }

        // Convert frequency to size_t
        entry.freq = std::stoul(freqPart);
        std::cout << "Word: " << entry.word << ", Pinyin: ";
        std::cout << ", Frequency: " << entry.freq << std::endl;
        vector<Pinyin::Alphabet> va;
        parser.StringVecToAlphaVec(entry.pinyin, va);
        Insert(va, {entry.word, entry.freq});
        auto iv = parser.PickInitialVec(va);
        if (iv.size()>0) {
            InsertFirstN(iv, {entry.word, entry.freq}, 20);
        }
    }
    END(BUILD_DICT)
    TIMECOST(BUILD_DICT)
    //log_info("words count: %d", parsedEntries->size());
    std::cout << "dict inited\n";

    // log_trace("start parse file");
    // START(parse_file);
    // auto parsedEntries = parseInput(filePath);
    // log_trace("end parse file");
    // END(parse_file);
    // TIMECOST(parse_file);
    // Pinyin::PinyinParser parser;

    // // Output the parsed entries
    // START(BUILD_DICT)
    // for (const auto& entry : *parsedEntries) {
    //     //std::cout << "Word: " << entry.word << ", Pinyin: ";
    //     vector<Pinyin::Alphabet> va;
    //     parser.StringVecToAlphaVec(entry.pinyin, va);
    //     //std::cout << ", Frequency: " << entry.freq << std::endl;
    //     Insert(va, {entry.word, entry.freq});
    //     // auto iv = parser.PickInitialVec(va);
    //     // if (iv.size()>0) {
    //     //     InsertFirstN(iv, {entry.word, entry.freq}, 20);
    //     // }
    // }
    // END(BUILD_DICT)
    // TIMECOST(BUILD_DICT)
    // log_info("words count: %d", parsedEntries->size());
    // std::cout << "dict inited\n";
    // delete parsedEntries;
}

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
bool HashMapDict<K, V>::LookUpByAlphabet(const Pinyin::PinyinVec& k, SortedVector<V>& res){
    START(match_1)
    int idx = 0;
    auto ptr = Find(k, idx);
    bool found = false;
    if (idx == k.size())[[__likely__]] {
        found = true;
        for (auto& v : ptr->get_data().Vec()) {
            res.insert(v);
        }
        log_trace("found exact match for key: [%s], val: %s", parser.AlphabetVecToString(k).c_str(), ptr->get_data().ToString().c_str());
    } else {
        log_trace("didn't find exact match for key: [%s]", parser.AlphabetVecToString(k).c_str());
    }
    END(match_1)
    TIMECOST(match_1)
    vector<string> ret(res.Vec().size());
    stringstream s;
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = res.Vec()[i].data;
        s << ret[i] << ", ";
    }
    log_trace("convert done, ret: %s", s.str().c_str());
    return found;
}

//template <std::totally_ordered K, std::totally_ordered V>
template <typename K, typename V>
vector<string> HashMapDict<K, V>::MatchWords(const string& src) {
    auto keys = parser.Parse(src);
    START(match_all)
    SortedVector<V> res;
    for (const auto& k : keys) {
        START(match_1)
        int idx = 0;
        auto ptr = Find(k, idx);
        if (idx == k.size())[[__likely__]] {
            for (auto& v : ptr->get_data().Vec()) {
                res.insert(v);
            }
            log_trace("found exact match for key: [%s], val: [%s]", parser.AlphabetVecToString(k).c_str(), ptr->get_data().ToString().c_str());
        } else {
            for (auto& v : ptr->get_data().Vec()) {
                res.insert(v);
            }
            log_trace("didn't find exact match for key: [%s], use longest match [%s]", parser.AlphabetVecToString(k).c_str(), ptr->get_data().ToString().c_str());
        }
        END(match_1)
        TIMECOST(match_1)
    }
    vector<string> ret(res.Vec().size());
    stringstream s;
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = res.Vec()[i].data;
        s << ret[i] << ", ";
    }
    END(match_all)
    TIMECOST(match_all)
    log_trace("convert done, ret: %s", s.str().c_str());
    cout<<s.str()<<endl;
    return ret;
}

int testHashMapDict(int argc, char* argv[]){
    //auto dict = HashMapDict<Alphabet, WordNode<std::string> >;
    

    init_logger("log.txt");
    // spdlog::set_level(spdlog::level::trace);
    // spdlog::flush_on(spdlog::level::trace);

    HashMapDict<K_t, D_t> dict;
    //dict.BuildDict("./resources/dict_2000.yml");
    dict.BuildDict("./resources/full_dict.yml");

    string s(argv[1]);

    //test match
    std::string input;
    while (1) {
        std::getline(std::cin, input);
        if (input == "quit") {
            break;
        }
        auto cadidates = dict.MatchWords(input);
        
    }
    

    std::cout<<"done.\n";
    return 0;
}