#include "mixDict.hpp"


template <std::totally_ordered K, std::totally_ordered V>
MixDict<K, V>::MixDict()
{
    _initial_dict_len = 20;
}

// template <std::totally_ordered K, std::totally_ordered V>
// MixDict<K,V>::MixDict(K& k, V& v)
// {
//     key = k;
//     data.emplace_back(v);
//     //sub = std::unordered_map<K,MixDict<K,V>*>();
// }

// template<std::totally_ordered K, std::totally_ordered V>
// MixDict<K,V>::MixDict(K& k)
// {
//     key = k;
// }

// template<std::totally_ordered K, std::totally_ordered V>
// 
// MixDict<K,V>::~MixDict()
// {

// }

// template <std::totally_ordered K, std::totally_ordered V>
// MixDict<K,V>* MixDict<K, V>::Find(const std::vector<K>& key, int& idx) //Find nearest match
// {
//     MixDict<K,V>* tmp = this;
//     auto sub = &this->sub;
//     idx = 0;
//     for (; idx<key.size(); ++idx) {
//         if (!sub->count(key[idx]) ) {
//             return tmp;
//         }
//         tmp = &sub->at(key[idx]);
//         sub = &tmp->sub;
//     }
//     return tmp;
// }

template <std::totally_ordered K, std::totally_ordered V>
bool MixDict<K, V>::Insert(const std::vector<K>& key, const V&& data)
{
    full_dict.Insert(key,data);
    auto ivec = parser.PickInitialVec(key);
    initial_dict.InsertFirstN(ivec, data, _initial_dict_len);
    return true;
}

template <std::totally_ordered K, std::totally_ordered V>
void MixDict<K, V>::BuildDict(const string& filePath)
{
    log_trace("start parse file");
    START(parse_file)
    auto parsedEntries = parseInput(filePath);
    log_trace("end parse file");
    END(parse_file)
    TIMECOST(parse_file)
    Pinyin::PinyinParser parser;

    // Output the parsed entries
    START(BUILD_DICT)
    for (const auto& entry : *parsedEntries) {
        //std::cout << "Word: " << entry.word << ", Pinyin: ";
        Pinyin::PinyinVec va;
        parser.StringVecToAlphaVec(entry.pinyin, va);
        //std::cout << ", Frequency: " << entry.freq << std::endl;
        full_dict.Insert(va, {entry.word, entry.freq});
        auto initials = parser.PickInitialVec(va);
        initial_dict.InsertFirstN(initials, {entry.word, entry.freq}, _initial_dict_len);
        
    }
    END(BUILD_DICT)
    TIMECOST(BUILD_DICT)
    log_info("words count: {}", parsedEntries->size());
    std::cout << "dict inited\n";
    delete parsedEntries;
}


template <std::totally_ordered K, std::totally_ordered V>
vector<string_view> MixDict<K, V>::MatchWords(const string& src) {
    auto keys = parser.Parse(src);
    START(match_all)
    SortedVector<V> res;
    for (const auto& k : keys) {
        if (full_dict.LookUpByAlphabet(k, res)) {

        } else {
            log_trace("didn't find exact match for key: [{}], try use initials...", parser.AlphabetVecToString(k));
            auto ivec = parser.PickInitialVec(k);
            initial_dict.LookUpByAlphabet(ivec, res);
        }
    }
    vector<string_view> ret(res.Vec().size());
    stringstream s;
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = res.Vec()[i].data;
        s << ret[i] << ", ";
    }
    END(match_all)
    TIMECOST(match_all)
    log_trace("convert done, ret: {}", s.str());
    return ret;
}



// int testMixDict(int argc, char* argv[]){
//     //auto dict = HashMapDict<Alphabet, WordNode<std::string> >;
    

//     init_logger("./log.txt");
//     spdlog::set_level(spdlog::level::trace);
//     spdlog::flush_on(spdlog::level::trace);

//     MixDict<K_t, D_t> dict;
//     dict.BuildDict("./resources/dict_2000.yml");
//     //dict.BuildDict("./resources/full_dict.yml");

//     string s(argv[1]);

//     //test match
//     auto cadidates = dict.MatchWords(s);

//     std::cout<<"done.\n";
//     return 0;
// }
