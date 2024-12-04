#pragma once

#include "../../bcommon/common/log.hpp"
#include <vector>
#include <string>

namespace Pinyin {

enum class Initial : char {
    Invalid = 0,
    B = 1,
    P,
    M,
    F,
    D,
    T,
    N,
    L,
    G,
    K,
    H,
    J,
    Q,
    X,
    ZH,
    CH,
    SH,
    R,
    Z,
    C,
    S,
    Y,
    W,
    End
};

enum class Final : char {
    Invalid = (char)Initial::End,
    A,
    AI,
    AN,
    ANG,
    AO,
    E,
    EI,
    EN,
    ENG,
    ER,
    O,
    ONG,
    OU,
    I,
    IA,
    IE,
    IAO,
    IU,
    IAN,
    IN,
    IANG,
    ING,
    IONG,
    U,
    UA,
    UO,
    UAI,
    UI,
    UAN,
    UN,
    UANG,
    V,
    VE,
    UE,
    NG,
    End
};

enum class Alphabet : char {
    Invalid = 0,
    B,
    P,
    M,
    F,
    D,
    T,
    N,
    L,
    G,
    K,
    H,
    J,
    Q,
    X,
    ZH,
    CH,
    SH,
    R,
    Z,
    C,
    S,
    Y,
    W,
    InitialEnd,
    A,
    AI,
    AN,
    ANG,
    AO,
    E,
    EI,
    EN,
    ENG,
    ER,
    O,
    ONG,
    OU,
    I,
    IA,
    IE,
    IAO,
    IU,
    IAN,
    IN,
    IANG,
    ING,
    IONG,
    U,
    UA,
    UO,
    UAI,
    UI,
    UAN,
    UN,
    UANG,
    V,
    VE,
    UE,
    NG,
    FinalEnd
};

enum FuzzyFlag : int {
    None = 0,
    CommonTypo = 1 << 0,
    NG_GN [[deprecated]] = CommonTypo,
    V_U = 1 << 1,
    AN_ANG = 1 << 2,   // 0
    EN_ENG = 1 << 3,   // 1
    IAN_IANG = 1 << 4, // 2
    IN_ING = 1 << 5,   // 3
    U_OU = 1 << 6,     // 4
    UAN_UANG = 1 << 7, // 5
    C_CH = 1 << 8,     // 0
    F_H = 1 << 9,      // 1
    L_N = 1 << 10,     // 2
    S_SH = 1 << 11,    // 3
    Z_ZH = 1 << 12,    // 4
    VE_UE = 1 << 13,
    Inner = 1 << 14,
    InnerShort = 1 << 15,
    PartialFinal = 1 << 16,
    /**
     * Enable matching partial shuangpin
     *
     * @since 1.0.11
     */
    PartialSp = 1 << 17,
    /**
     * Enable typo that may cause ambiguity.
     *
     * @since 1.1.3
     */
    AdvancedTypo = 1 << 18,
    /**
     * Enable correction based on layout profile.
     *
     * @since 1.1.7
     */
    Correction = 1 << 19,
};


struct Syllable {
    Initial i;
    Final f;
};

struct PinyinMapEntry {
    Initial i;
    Final f;
    int fz;

    // PinyinMapEntry(Initial i, Final f, FuzzyFlag fz) {
    //     i = i;
    //     f = f;
    //     fz = fz;
    // }
};

using PinyinVec = std::vector<Alphabet>;
using PinyinMap = unordered_map<string_view, PinyinMapEntry>;
using AlphabetMap = unordered_map<string_view, Alphabet>;

struct AlphaData {
    string_view s;
    Alphabet a; 
    bool fz = true;
};

using ParseRef = unordered_map<string_view, vector<AlphaData>>;

struct MarkKey {
    size_t start_pos;
    size_t end_pos; 
    Alphabet a;
    bool operator==(const MarkKey& b) const {
        return start_pos == b.start_pos &&
            end_pos == b.end_pos && 
            a == b.a;
    } 
    string toString() const {
        return to_string(start_pos*1000+end_pos);
    }
};

struct AlphaMark
{
    MarkKey key;
    AlphaData data;  
    //const string_view& src;
    string toString() {
        return string(data.s);
    }
};

}

namespace std {
template<>
struct hash<Pinyin::MarkKey>{
    size_t operator()(const Pinyin::MarkKey& k) const
    {
        // using size_t;
        // using hash;
        // using string;

        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        // return ((hash<string>()(k.first)
        //         ^ (hash<string>()(k.second) << 1)) >> 1)
        //         ^ (hash<int>()(k.third) << 1);
        return (size_t)(k.a) << 32 | (k.start_pos << 16) | (k.end_pos << 0 );
    }
};
}

namespace Pinyin {

}
