#include "parser.hpp"
#include <cstring>

namespace Pinyin {

PinyinParser::PinyinParser() {
    init_parse_map();
    SetFuzzy();
}

void PinyinParser::splitBaseMap() {
    for (auto& e : _all_map) {
        if (e.second.fz == FuzzyFlag::None || e.second.fz | (FuzzyFlag::CommonTypo))[[likely]] {
            _base_map.insert(e);
        } else {
            _fuzzy_map.insert(e);
        }
    }
}

void PinyinParser::initAlphabetMap() {
    _alphabet_map = move(AlphabetMap{
        {"b", Alphabet::B},
        {"p", Alphabet::P},
        {"m", Alphabet::M},
        {"f", Alphabet::F},
        {"d", Alphabet::D},
        {"t", Alphabet::T},
        {"n", Alphabet::N},
        {"l", Alphabet::L},
        {"g", Alphabet::G},
        {"k", Alphabet::K},
        {"h", Alphabet::H},
        {"j", Alphabet::J},
        {"q", Alphabet::Q},
        {"x", Alphabet::X},
        {"zh", Alphabet::ZH},
        {"ch", Alphabet::CH},
        {"sh", Alphabet::SH},
        {"r", Alphabet::R},
        {"z", Alphabet::Z},
        {"c", Alphabet::C},
        {"s", Alphabet::S},
        {"y", Alphabet::Y},
        {"w", Alphabet::W},
        {"a", Alphabet::A},
        {"o", Alphabet::O},
        {"e", Alphabet::E},
        {"i", Alphabet::I},
        {"u", Alphabet::U},
        {"v", Alphabet::V},
        {"ai", Alphabet::AI},
        {"ei", Alphabet::EI},
        {"ui", Alphabet::UI},
        {"ao", Alphabet::AO},
        {"ou", Alphabet::OU},
        {"iu", Alphabet::IU},
        {"ie", Alphabet::IE},
        {"ve", Alphabet::VE},
        {"er", Alphabet::ER},
        {"an", Alphabet::AN},
        {"en", Alphabet::EN},
        {"in", Alphabet::IN},
        {"un", Alphabet::UN},
        //{"vn", Alphabet::VN},
        {"ang", Alphabet::ANG},
        {"eng", Alphabet::ENG},
        {"ing", Alphabet::ING},
        {"ong", Alphabet::ONG}
    });
}

const int MaxAlphabetLen = 3;
// bool PinyinParser::hasValidAlphabet(const string& src, int start,  vector<AlphaMark>& m) {
//     for (int i=1; i<=MaxAlphabetLen && start+i-1 < src.size(); ++i) {
//         auto s = string_view(src, i);
//         if (_alphabet_map.contains(s)) {
//             m.emplace_back(AlphaMark{s, _alphabet_map[s], start, i, });
//         }
//     }
// }
void PinyinParser::DirectParseToVec(const string& src, vector<Alphabet>& dst) {
    if (!src.size()) {
        return;
    }
    size_t start = 0;
    while(start < src.length()) {
        size_t i = MaxAlphabetLen < src.size() - start ? MaxAlphabetLen : src.size() - start; 
        for (; i>0; --i) {
            auto s = string(&src[start], i);
            if (_parse_ref.count(s)) { // valid alpha
                dst.emplace_back(_parse_ref[s][0].a);
                start += i; //commit
                break;
                //direct match only take the full match, because src is supposed to be single syllable
            } 
        }
        if (i == 0) {
            log_trace("invalid s: %c", src[start]);
            break;
        }
    }
    
}

void logGraph(Graph<AlphaMark, MarkKey>& g) {
    log_info("logging graph:");
    for (auto& e : g.GetTable()) {
        log_info("key %s data at %p", e.first.toString().c_str(), &e.second);
    }
}

void PinyinParser::ParseToGraph(PinyinGraph& g, const string& src, size_t start, PinyinGraphNode* cur_node) {
    if (start >= src.size()) {
        return;
    }
    auto table = g.GetTable();
    if (cur_node == nullptr) {
        cur_node = &g.GetRoot();
    }
    //while (start < src.size()) {
    size_t step_len = MaxAlphabetLen < src.size() - start ? MaxAlphabetLen : src.size() - start; 
    for (int i=step_len; i>0; --i) {
        auto s = string(&src[start], i);
        if (_parse_ref.count(s)) { // valid alpha
            for (auto& v : _parse_ref[s]) {
                const MarkKey key{start,start+v.s.size(), v.a}; // 【start， end）
                if (table.count(key)) { //already exist
                    cur_node->AddToNode((table[key])); //different address from ori node, but the value is the same
                    log_info("get key %s data at %p", key.toString().c_str(), (table[key]));
                    continue; //same start, same iteration, certainly same end, so just return, actually this means a joined node.
                } else { //new node
                    auto ptr = g.AddNode(key, AlphaMark{key, v});
                    log_info("added new node %s at %p", key.toString().c_str(), ptr);
                    cur_node->AddToNode(ptr);
                    //logGraph(g);
                    ParseToGraph(g, src, start+v.s.size(), cur_node->to_nodes.back()); // recrusive, cur_node move to newly added
                }  
            }  
            return;  // nest stituations are already defined in _parse_map, so if contains, all have already been processed above              
        } else { //not in pre-calculated map
            // do nothing
        }
    }

}



vector<vector<Alphabet>> PinyinParser::StringToAlphabet(std::string &str)
{
    vector<vector<Alphabet>> ret; //n*m fuzzy combinations

    
    


    return ret;
}


// void PinyinParser::SetFuzzyFlags(vector<FuzzyFlag> &v) {
//     for (auto flag : v) {
//         if (_fuzzy_set.count(flag)) {
//             for (auto s : _fuzzy_set[flag]) {
//                 _fuzzy_map[s.first] = s.second;
//             }
//         } else {
//             // not pre-defined
//         }

//     }
// }

const size_t SyllableMaxLen = 6;
vector<PinyinVec> PinyinParser::Parse(const string &s)
{
    log_info("try parse: %s", s.c_str());
    Graph<Pinyin::AlphaMark, Pinyin::MarkKey> g;
    ParseToGraph(g, s);
    auto res = g.DFS_ALL();
    log_info("got res: ");
    for (auto&v : *res) {
        log_info("dfs res: %s", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* const &k){return string(k->data.s); }, ",").c_str());
    }
    ApplyFuzzyForGraph(g);
    auto res2 = g.DFS_ALL();
    vector<PinyinVec> keys(res2->size());
    auto key = keys.begin();
    log_info("res after fuzzy: ");
    for (int i = 0; i<keys.size(); ++i) {
        const auto& v = (*res2)[i];
        log_info("route: %s", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* const &k){return string(k->data.s); }, ",").c_str());
        PinyinVec k(v.size());
        for (int j = 0; j<k.size(); ++j) {
            k[j] = v[j]->data.a;
        }
        keys[i] = k;
    }
    delete res, res2;
    return keys;
}


}

int test_parser(int argc, char* argv[]) {
    std::cout<<"start...\n";
    using Pinyin::AlphaMark;
    using Pinyin::MarkKey;

    init_logger("./log.txt");
    // spdlog::set_level(spdlog::level::trace);
    Pinyin::PinyinParser p;
    string s(argv[1]);
    // log_info("try parse: {}", s);
    // spdlog::flush_on(spdlog::level::trace);
    log_info("try parse: %s", s);
    Graph<Pinyin::AlphaMark, Pinyin::MarkKey> g;
    p.ParseToGraph(g, s);
    auto res = g.DFS_ALL();
    log_info("got res: ");
    for (auto&v : *res) {
        //log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](AlphaMark* const &k){return string(k->data.s); }, ","));
        log_info("%s", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](AlphaMark* const &k){return string(k->data.s); }, ",").c_str());
    }
    p.ApplyFuzzyForGraph(g);
    auto res2 = g.DFS_ALL();
    log_info("res after fuzzy: ");
    for (auto&v : *res2) {
        //log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](AlphaMark* const &k){return string(k->data.s); }, ","));
        log_info("%s", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](AlphaMark* const &k){return string(k->data.s); }, ",").c_str());
    }
    delete res;
    delete res2;
    std::cout<<"done.\n";
    return 0;
}
