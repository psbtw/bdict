#include "consts.hpp"
#include <unordered_map>


class PinyinParser {

private:
    unordered_map<string_view, vector<PinyinAlphabet>> _base_map; //always there
    unordered_map<string_view, vector<PinyinAlphabet>> _fuzzy_map; //added optionally
    unordered_map<PinyinFuzzyFlag, unordered_map<string, vector<PinyinAlphabet>>> _fuzzy_set; //predefined

    void init_base_map();

public:
    vector<vector<PinyinAlphabet>> StringToAlphabet(std::string& str);
    PinyinParser();
    void SetFuzzyFlags(vector<PinyinFuzzyFlag> &v);
    vector<PinyinVec>& Parse(const string& s);

    PinyinAlphabet ParseAlphabet(string_view& s){
        auto ret = PinyinAlphabet::FinalEnd;
        if (_base_map.count(s)) {
            ret = _base_map[s];
        }
    }
};