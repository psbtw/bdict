#pragma once

#include "types.hpp"
#include <unordered_map>
#include "../../bcommon/container/graph.hpp"
#include <string>
#include <string_view>

namespace Pinyin {


using PinyinGraph = Graph<AlphaMark, MarkKey>;
using PinyinGraphNode = GraphNode<AlphaMark>;

class PinyinParser {

private:
    PinyinMap _all_map, _base_map, _fuzzy_map;
    AlphabetMap _alphabet_map;
    ParseRef _parse_ref;
    unordered_map<Alphabet, Alphabet> _fz_map;
    

public:
    vector<vector<Alphabet>> StringToAlphabet(string& str);
    PinyinParser();
    void SetFuzzyFlags(vector<FuzzyFlag> &v);
    vector<PinyinVec> Parse(const string& s);

    Alphabet ParseAlphabet(string_view& s){
        auto ret = Alphabet::FinalEnd;
        // if (_base_map.count(s)) {
        //     ret = _base_map[s];
        // }
        return ret;
    }
    void ParseToGraph(PinyinGraph& g, const string& src,  size_t start_pos = 0, PinyinGraphNode* cur = nullptr);
    void ApplyFuzzyForGraph(PinyinGraph& g) {
        log_trace("applying fuzzy...");
        g.BFS(bind(&PinyinParser::addFuzzyNode, this, g, placeholders::_1));
    }

private:
    void splitBaseMap();
    const PinyinMap& getAllMap();
    const PinyinMap& getBaseMap();
    void init_base_map();
    void initAlphabetMap();
    void init_parse_map(){
        _parse_ref = move(ParseRef{
            {"b", {{"b", Alphabet::B}}},
            {"p", {{"p", Alphabet::P}}},
            {"m", {{"m", Alphabet::M}}},
            {"f", {{"f", Alphabet::F}}},
            {"d", {{"d", Alphabet::D}}},
            {"t", {{"t", Alphabet::T}}},
            {"n", {{"n", Alphabet::N}}},
            {"l", {{"l", Alphabet::L}}},
            {"g", {{"g", Alphabet::G}}},
            {"k", {{"k", Alphabet::K}}},
            {"h", {{"h", Alphabet::H}}},
            {"j", {{"j", Alphabet::J}}},
            {"q", {{"q", Alphabet::Q}}},
            {"x", {{"x", Alphabet::X}}},
            {"zh", {{"zh", Alphabet::ZH}}},
            {"ch", {{"ch", Alphabet::CH}}},
            {"sh", {{"sh", Alphabet::SH}}},
            {"r", {{"r", Alphabet::R}}},
            {"z", {{"z", Alphabet::Z}}},
            {"c", {{"c", Alphabet::C}}},
            {"s", {{"s", Alphabet::S}}},
            {"y", {{"y", Alphabet::Y}}},
            {"w", {{"w", Alphabet::W}}},
            {"a", {{"a", Alphabet::A}}},
            {"o", {{"o", Alphabet::O}}},
            {"e", {{"e", Alphabet::E}}},
            {"i", {{"i", Alphabet::I}}},
            {"u", {{"u", Alphabet::U}}},
            {"v", {{"v", Alphabet::V}}},
            {"ai", {{"ai", Alphabet::AI}}},
            {"ei", {{"ei", Alphabet::EI}}},
            {"ui", {{"ui", Alphabet::UI}}},
            {"ao", {{"ao", Alphabet::AO}}},
            {"ou", {{"ou", Alphabet::OU}}},
            {"iu", {{"iu", Alphabet::IU}}},
            {"ie", {{"ie", Alphabet::IE}}},
            {"ve", {{"ve", Alphabet::VE}}},
            {"er", {{"er", Alphabet::ER}, {"e", Alphabet::E}}},
            {"un", {{"un", Alphabet::UN}, {"u", Alphabet::U}}},
            //{"vn", {{"vn", Alphabet::VN}, {"v", Alphabet::V}}},
            {"ong", {{"ong", Alphabet::ONG}}},
            {"ang", {{"ang", Alphabet::ANG}, {"an", Alphabet::AN}}}, 
            {"an", {{"an", Alphabet::AN}, {"a", Alphabet::A}}}, 
            {"eng", {{"eng", Alphabet::ENG}, {"en", Alphabet::EN, false}}}, 
            {"en", {{"en", Alphabet::EN}, {"e", Alphabet::E}}}, 
            {"ing", {{"ing", Alphabet::ING}, {"in", Alphabet::IN, false}}}, 
            {"in", {{"in", Alphabet::IN}, {"i", Alphabet::I}}}, 
        });
    }

    void SetFuzzy() { //consider dynamic configurations in later verison
        _fz_map = move(unordered_map<Alphabet, Alphabet>{
            // {Alphabet::Z, Alphabet::ZH},
            // {Alphabet::ZH, Alphabet::Z},
            // {Alphabet::C, Alphabet::CH},
            // {Alphabet::CH, Alphabet::C},
            // {Alphabet::S, Alphabet::SH},
            // {Alphabet::SH, Alphabet::S},
            {Alphabet::IN, Alphabet::ING},
            {Alphabet::ING, Alphabet::IN},
            {Alphabet::EN, Alphabet::ENG},
            {Alphabet::ENG, Alphabet::EN}
        });
    }

    void addFuzzyNode(PinyinGraph& g, PinyinGraphNode* node) {
        if (node->data.data.fz && _fz_map.contains(node->data.key.a)) {
            MarkKey newKey(node->data.key);
            newKey.a = _fz_map[node->data.key.a];
            auto ptr = g.AddNode(newKey, node->data);
            ptr->CopyRelation(node);
        }
    }

};

}
