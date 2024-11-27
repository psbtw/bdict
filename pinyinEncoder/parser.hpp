#include "consts.hpp"
#include <unordered_map>
#include "../../bcommon/container/graph.hpp"

namespace Pinyin {

class PinyinParser {

private:
    PinyinMap _all_map, _base_map, _fuzzy_map;
    AlphabetMap _alphabet_map;
    AlphabetTree _alphabet_tree;
    void splitBaseMap();
    const PinyinMap& getAllMap();
    const PinyinMap& getBaseMap();
    void init_base_map();
    void initAlphabetMap();

public:
    vector<vector<Alphabet>> StringToAlphabet(std::string& str);
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
};

}
