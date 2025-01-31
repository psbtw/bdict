#include "parser.hpp"
#include <cstring>

namespace Pinyin {

// void PinyinParser::init_base_map()
// {
//     _base_map = move(unordered_map<string_view, vector<Alphabet>>{
//         {"a", {Alphabet::A}},
//         {"o", {Alphabet::O}},
//         {"e", {Alphabet::E}},
//         {"i", {Alphabet::I}},
//         {"u", {Alphabet::U}},
//         {"v", {Alphabet::V}},
//         {"uang", {Alphabet::UANG}}
//     });
// }

// PinyinParser::PinyinParser() {
//     _all_map = move(PinyinMap{
//         {"zuo", {Initial::Z, Final::UO, FuzzyFlag::None}},
//         {"zun", {Initial::Z, Final::UN, FuzzyFlag::None}},
//         {"zui", {Initial::Z, Final::UI, FuzzyFlag::None}},
//         // {"zuagn", {Initial::Z, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         // {"zuang", {Initial::Z, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"zuagn", {Initial::ZH, Final::UANG, FuzzyFlag::Z_ZH | FuzzyFlag::CommonTypo}},
//         {"zuang", {Initial::ZH, Final::UANG, FuzzyFlag::Z_ZH}},
//         {"zuan", {Initial::Z, Final::UAN, FuzzyFlag::None}},
//         {"zuai", {Initial::ZH, Final::UAI, FuzzyFlag::Z_ZH}},
//         {"zua", {Initial::ZH, Final::UA, FuzzyFlag::Z_ZH}},
//         {"zu", {Initial::Z, Final::U, FuzzyFlag::None}},
//         {"zou", {Initial::Z, Final::OU, FuzzyFlag::None}},
//         {"zogn", {Initial::Z, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"zon", {Initial::Z, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"zong", {Initial::Z, Final::ONG, FuzzyFlag::None}},
//         {"zi", {Initial::Z, Final::I, FuzzyFlag::None}},
//         {"zhuo", {Initial::ZH, Final::UO, FuzzyFlag::None}},
//         {"zhun", {Initial::ZH, Final::UN, FuzzyFlag::None}},
//         {"zhui", {Initial::ZH, Final::UI, FuzzyFlag::None}},
//         {"zhuagn", {Initial::ZH, Final::UANG, FuzzyFlag::CommonTypo}},
//         {"zhuang", {Initial::ZH, Final::UANG, FuzzyFlag::None}},
//         {"zhuan", {Initial::ZH, Final::UAN, FuzzyFlag::None}},
//         {"zhuai", {Initial::ZH, Final::UAI, FuzzyFlag::None}},
//         {"zhua", {Initial::ZH, Final::UA, FuzzyFlag::None}},
//         {"zhu", {Initial::ZH, Final::U, FuzzyFlag::None}},
//         {"zhou", {Initial::ZH, Final::OU, FuzzyFlag::None}},
//         {"zhogn", {Initial::ZH, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"zhon", {Initial::ZH, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"zhong", {Initial::ZH, Final::ONG, FuzzyFlag::None}},
//         {"zhi", {Initial::ZH, Final::I, FuzzyFlag::None}},
//         {"zhegn", {Initial::ZH, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"zheng", {Initial::ZH, Final::ENG, FuzzyFlag::None}},
//         {"zhen", {Initial::ZH, Final::EN, FuzzyFlag::None}},
//         {"zhei", {Initial::ZH, Final::EI, FuzzyFlag::None}},
//         {"zhe", {Initial::ZH, Final::E, FuzzyFlag::None}},
//         {"zhao", {Initial::ZH, Final::AO, FuzzyFlag::None}},
//         {"zhagn", {Initial::ZH, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"zhang", {Initial::ZH, Final::ANG, FuzzyFlag::None}},
//         {"zhan", {Initial::ZH, Final::AN, FuzzyFlag::None}},
//         {"zhai", {Initial::ZH, Final::AI, FuzzyFlag::None}},
//         {"zha", {Initial::ZH, Final::A, FuzzyFlag::None}},
//         {"zegn", {Initial::Z, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"zeng", {Initial::Z, Final::ENG, FuzzyFlag::None}},
//         {"zen", {Initial::Z, Final::EN, FuzzyFlag::None}},
//         {"zei", {Initial::Z, Final::EI, FuzzyFlag::None}},
//         {"ze", {Initial::Z, Final::E, FuzzyFlag::None}},
//         {"zao", {Initial::Z, Final::AO, FuzzyFlag::None}},
//         {"zagn", {Initial::Z, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"zang", {Initial::Z, Final::ANG, FuzzyFlag::None}},
//         {"zan", {Initial::Z, Final::AN, FuzzyFlag::None}},
//         {"zai", {Initial::Z, Final::AI, FuzzyFlag::None}},
//         {"za", {Initial::Z, Final::A, FuzzyFlag::None}},
//         {"yun", {Initial::Y, Final::UN, FuzzyFlag::None}},
//         {"yue", {Initial::Y, Final::UE, FuzzyFlag::None}},
//         {"yve", {Initial::Y, Final::UE, FuzzyFlag::CommonTypo}},
//         {"yuagn", {Initial::Y, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"yuang", {Initial::Y, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"yvagn", {Initial::Y, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"yvang", {Initial::Y, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"yuan", {Initial::Y, Final::UAN, FuzzyFlag::None}},
//         {"yvan", {Initial::Y, Final::UAN, FuzzyFlag::CommonTypo}},
//         {"yu", {Initial::Y, Final::U, FuzzyFlag::None}},
//         {"yv", {Initial::Y, Final::U, FuzzyFlag::CommonTypo}},
//         {"you", {Initial::Y, Final::OU, FuzzyFlag::None}},
//         {"yogn", {Initial::Y, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"yon", {Initial::Y, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"yong", {Initial::Y, Final::ONG, FuzzyFlag::None}},
//         {"yo", {Initial::Y, Final::O, FuzzyFlag::None}},
//         {"yign", {Initial::Y, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ying", {Initial::Y, Final::ING, FuzzyFlag::None}},
//         {"yin", {Initial::Y, Final::IN, FuzzyFlag::None}},
//         {"yi", {Initial::Y, Final::I, FuzzyFlag::None}},
//         {"ye", {Initial::Y, Final::E, FuzzyFlag::None}},
//         {"yao", {Initial::Y, Final::AO, FuzzyFlag::None}},
//         {"yagn", {Initial::Y, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"yang", {Initial::Y, Final::ANG, FuzzyFlag::None}},
//         {"yan", {Initial::Y, Final::AN, FuzzyFlag::None}},
//         {"ya", {Initial::Y, Final::A, FuzzyFlag::None}},
//         {"xun", {Initial::X, Final::UN, FuzzyFlag::None}},
//         {"xue", {Initial::X, Final::UE, FuzzyFlag::None}},
//         {"xve", {Initial::X, Final::UE, FuzzyFlag::CommonTypo}},
//         {"xuagn", {Initial::X, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"xuang", {Initial::X, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"xvagn", {Initial::X, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"xvang", {Initial::X, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"xuan", {Initial::X, Final::UAN, FuzzyFlag::None}},
//         {"xvan", {Initial::X, Final::UAN, FuzzyFlag::CommonTypo}},
//         {"xu", {Initial::X, Final::U, FuzzyFlag::None}},
//         {"xv", {Initial::X, Final::U, FuzzyFlag::CommonTypo}},
//         {"xou", {Initial::X, Final::U, FuzzyFlag::U_OU}},
//         {"xiu", {Initial::X, Final::IU, FuzzyFlag::None}},
//         {"xiogn", {Initial::X, Final::IONG, FuzzyFlag::CommonTypo}},
//         {"xion", {Initial::X, Final::IONG, FuzzyFlag::CommonTypo}},
//         {"xiong", {Initial::X, Final::IONG, FuzzyFlag::None}},
//         {"xign", {Initial::X, Final::ING, FuzzyFlag::CommonTypo}},
//         {"xing", {Initial::X, Final::ING, FuzzyFlag::None}},
//         {"xin", {Initial::X, Final::IN, FuzzyFlag::None}},
//         {"xie", {Initial::X, Final::IE, FuzzyFlag::None}},
//         {"xiao", {Initial::X, Final::IAO, FuzzyFlag::None}},
//         {"xiagn", {Initial::X, Final::IANG, FuzzyFlag::CommonTypo}},
//         {"xiang", {Initial::X, Final::IANG, FuzzyFlag::None}},
//         {"xian", {Initial::X, Final::IAN, FuzzyFlag::None}},
//         {"xia", {Initial::X, Final::IA, FuzzyFlag::None}},
//         {"xi", {Initial::X, Final::I, FuzzyFlag::None}},
//         {"wu", {Initial::W, Final::U, FuzzyFlag::None}},
//         {"wo", {Initial::W, Final::O, FuzzyFlag::None}},
//         {"wegn", {Initial::W, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"weng", {Initial::W, Final::ENG, FuzzyFlag::None}},
//         {"wen", {Initial::W, Final::EN, FuzzyFlag::None}},
//         {"wei", {Initial::W, Final::EI, FuzzyFlag::None}},
//         {"wagn", {Initial::W, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"wang", {Initial::W, Final::ANG, FuzzyFlag::None}},
//         {"wan", {Initial::W, Final::AN, FuzzyFlag::None}},
//         {"wai", {Initial::W, Final::AI, FuzzyFlag::None}},
//         {"wa", {Initial::W, Final::A, FuzzyFlag::None}},
//         {"tuo", {Initial::T, Final::UO, FuzzyFlag::None}},
//         {"tun", {Initial::T, Final::UN, FuzzyFlag::None}},
//         {"tui", {Initial::T, Final::UI, FuzzyFlag::None}},
//         {"tuagn", {Initial::T, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"tuang", {Initial::T, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"tuan", {Initial::T, Final::UAN, FuzzyFlag::None}},
//         {"tu", {Initial::T, Final::U, FuzzyFlag::None}},
//         {"tou", {Initial::T, Final::OU, FuzzyFlag::None}},
//         {"togn", {Initial::T, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"ton", {Initial::T, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"tong", {Initial::T, Final::ONG, FuzzyFlag::None}},
//         {"tign", {Initial::T, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ting", {Initial::T, Final::ING, FuzzyFlag::None}},
//         {"tin", {Initial::T, Final::ING, FuzzyFlag::IN_ING}},
//         {"tie", {Initial::T, Final::IE, FuzzyFlag::None}},
//         {"tiao", {Initial::T, Final::IAO, FuzzyFlag::None}},
//         {"tiagn", {Initial::T, Final::IAN, FuzzyFlag::IAN_IANG | FuzzyFlag::CommonTypo}},
//         {"tiang", {Initial::T, Final::IAN, FuzzyFlag::IAN_IANG}},
//         {"tian", {Initial::T, Final::IAN, FuzzyFlag::None}},
//         {"ti", {Initial::T, Final::I, FuzzyFlag::None}},
//         {"tegn", {Initial::T, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"teng", {Initial::T, Final::ENG, FuzzyFlag::None}},
//         {"ten", {Initial::T, Final::ENG, FuzzyFlag::EN_ENG}},
//         {"tei", {Initial::T, Final::EI, FuzzyFlag::None}},
//         {"te", {Initial::T, Final::E, FuzzyFlag::None}},
//         {"tao", {Initial::T, Final::AO, FuzzyFlag::None}},
//         {"tagn", {Initial::T, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"tang", {Initial::T, Final::ANG, FuzzyFlag::None}},
//         {"tan", {Initial::T, Final::AN, FuzzyFlag::None}},
//         {"tai", {Initial::T, Final::AI, FuzzyFlag::None}},
//         {"ta", {Initial::T, Final::A, FuzzyFlag::None}},
//         {"suo", {Initial::S, Final::UO, FuzzyFlag::None}},
//         {"sun", {Initial::S, Final::UN, FuzzyFlag::None}},
//         {"sui", {Initial::S, Final::UI, FuzzyFlag::None}},
//         {"suagn", {Initial::SH, Final::UANG, FuzzyFlag::S_SH | FuzzyFlag::CommonTypo}},
//         {"suang", {Initial::SH, Final::UANG, FuzzyFlag::S_SH}},
//         //{"suagn", {Initial::S, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         //{"suang", {Initial::S, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"suan", {Initial::S, Final::UAN, FuzzyFlag::None}},
//         {"suai", {Initial::SH, Final::UAI, FuzzyFlag::S_SH}},
//         {"sua", {Initial::SH, Final::UA, FuzzyFlag::S_SH}},
//         {"su", {Initial::S, Final::U, FuzzyFlag::None}},
//         {"sou", {Initial::S, Final::OU, FuzzyFlag::None}},
//         {"sogn", {Initial::S, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"son", {Initial::S, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"song", {Initial::S, Final::ONG, FuzzyFlag::None}},
//         {"si", {Initial::S, Final::I, FuzzyFlag::None}},
//         {"shuo", {Initial::SH, Final::UO, FuzzyFlag::None}},
//         {"shun", {Initial::SH, Final::UN, FuzzyFlag::None}},
//         {"shui", {Initial::SH, Final::UI, FuzzyFlag::None}},
//         {"shuagn", {Initial::SH, Final::UANG, FuzzyFlag::CommonTypo}},
//         {"shuang", {Initial::SH, Final::UANG, FuzzyFlag::None}},
//         {"shuan", {Initial::SH, Final::UAN, FuzzyFlag::None}},
//         {"shuai", {Initial::SH, Final::UAI, FuzzyFlag::None}},
//         {"shua", {Initial::SH, Final::UA, FuzzyFlag::None}},
//         {"shu", {Initial::SH, Final::U, FuzzyFlag::None}},
//         {"shou", {Initial::SH, Final::OU, FuzzyFlag::None}},
//         {"shi", {Initial::SH, Final::I, FuzzyFlag::None}},
//         {"shegn", {Initial::SH, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"sheng", {Initial::SH, Final::ENG, FuzzyFlag::None}},
//         {"shen", {Initial::SH, Final::EN, FuzzyFlag::None}},
//         {"shei", {Initial::SH, Final::EI, FuzzyFlag::None}},
//         {"she", {Initial::SH, Final::E, FuzzyFlag::None}},
//         {"shao", {Initial::SH, Final::AO, FuzzyFlag::None}},
//         {"shagn", {Initial::SH, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"shang", {Initial::SH, Final::ANG, FuzzyFlag::None}},
//         {"shan", {Initial::SH, Final::AN, FuzzyFlag::None}},
//         {"shai", {Initial::SH, Final::AI, FuzzyFlag::None}},
//         {"sha", {Initial::SH, Final::A, FuzzyFlag::None}},
//         {"segn", {Initial::S, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"seng", {Initial::S, Final::ENG, FuzzyFlag::None}},
//         {"sen", {Initial::S, Final::EN, FuzzyFlag::None}},
//         {"se", {Initial::S, Final::E, FuzzyFlag::None}},
//         {"sao", {Initial::S, Final::AO, FuzzyFlag::None}},
//         {"sagn", {Initial::S, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"sang", {Initial::S, Final::ANG, FuzzyFlag::None}},
//         {"san", {Initial::S, Final::AN, FuzzyFlag::None}},
//         {"sai", {Initial::S, Final::AI, FuzzyFlag::None}},
//         {"sa", {Initial::S, Final::A, FuzzyFlag::None}},
//         {"rua", {Initial::R, Final::UA, FuzzyFlag::None}},
//         {"r", {Initial::R, Final::End, FuzzyFlag::None}},
//         {"ruo", {Initial::R, Final::UO, FuzzyFlag::None}},
//         {"run", {Initial::R, Final::UN, FuzzyFlag::None}},
//         {"rui", {Initial::R, Final::UI, FuzzyFlag::None}},
//         {"ruagn", {Initial::R, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"ruang", {Initial::R, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"ruan", {Initial::R, Final::UAN, FuzzyFlag::None}},
//         {"ru", {Initial::R, Final::U, FuzzyFlag::None}},
//         {"rou", {Initial::R, Final::OU, FuzzyFlag::None}},
//         {"rogn", {Initial::R, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"ron", {Initial::R, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"rong", {Initial::R, Final::ONG, FuzzyFlag::None}},
//         {"ri", {Initial::R, Final::I, FuzzyFlag::None}},
//         {"regn", {Initial::R, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"reng", {Initial::R, Final::ENG, FuzzyFlag::None}},
//         {"ren", {Initial::R, Final::EN, FuzzyFlag::None}},
//         {"re", {Initial::R, Final::E, FuzzyFlag::None}},
//         {"rao", {Initial::R, Final::AO, FuzzyFlag::None}},
//         {"ragn", {Initial::R, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"rang", {Initial::R, Final::ANG, FuzzyFlag::None}},
//         {"ran", {Initial::R, Final::AN, FuzzyFlag::None}},
//         {"qun", {Initial::Q, Final::UN, FuzzyFlag::None}},
//         {"que", {Initial::Q, Final::UE, FuzzyFlag::None}},
//         {"qve", {Initial::Q, Final::UE, FuzzyFlag::CommonTypo}},
//         {"quagn", {Initial::Q, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"quang", {Initial::Q, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"qvagn", {Initial::Q, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"qvang", {Initial::Q, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"quan", {Initial::Q, Final::UAN, FuzzyFlag::None}},
//         {"qvan", {Initial::Q, Final::UAN, FuzzyFlag::CommonTypo}},
//         {"qu", {Initial::Q, Final::U, FuzzyFlag::None}},
//         {"qv", {Initial::Q, Final::U, FuzzyFlag::CommonTypo}},
//         {"qiu", {Initial::Q, Final::IU, FuzzyFlag::None}},
//         {"qiogn", {Initial::Q, Final::IONG, FuzzyFlag::CommonTypo}},
//         {"qion", {Initial::Q, Final::IONG, FuzzyFlag::CommonTypo}},
//         {"qiong", {Initial::Q, Final::IONG, FuzzyFlag::None}},
//         {"qign", {Initial::Q, Final::ING, FuzzyFlag::CommonTypo}},
//         {"qing", {Initial::Q, Final::ING, FuzzyFlag::None}},
//         {"qin", {Initial::Q, Final::IN, FuzzyFlag::None}},
//         {"qie", {Initial::Q, Final::IE, FuzzyFlag::None}},
//         {"qiao", {Initial::Q, Final::IAO, FuzzyFlag::None}},
//         {"qiagn", {Initial::Q, Final::IANG, FuzzyFlag::CommonTypo}},
//         {"qiang", {Initial::Q, Final::IANG, FuzzyFlag::None}},
//         {"qian", {Initial::Q, Final::IAN, FuzzyFlag::None}},
//         {"qia", {Initial::Q, Final::IA, FuzzyFlag::None}},
//         {"qi", {Initial::Q, Final::I, FuzzyFlag::None}},
//         {"pu", {Initial::P, Final::U, FuzzyFlag::None}},
//         {"pou", {Initial::P, Final::OU, FuzzyFlag::None}},
//         {"po", {Initial::P, Final::O, FuzzyFlag::None}},
//         {"pign", {Initial::P, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ping", {Initial::P, Final::ING, FuzzyFlag::None}},
//         {"pin", {Initial::P, Final::IN, FuzzyFlag::None}},
//         {"pie", {Initial::P, Final::IE, FuzzyFlag::None}},
//         {"piao", {Initial::P, Final::IAO, FuzzyFlag::None}},
//         {"piagn", {Initial::P, Final::IAN, FuzzyFlag::IAN_IANG | FuzzyFlag::CommonTypo}},
//         {"piang", {Initial::P, Final::IAN, FuzzyFlag::IAN_IANG}},
//         {"pian", {Initial::P, Final::IAN, FuzzyFlag::None}},
//         {"pi", {Initial::P, Final::I, FuzzyFlag::None}},
//         {"pegn", {Initial::P, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"peng", {Initial::P, Final::ENG, FuzzyFlag::None}},
//         {"pen", {Initial::P, Final::EN, FuzzyFlag::None}},
//         {"pei", {Initial::P, Final::EI, FuzzyFlag::None}},
//         {"pao", {Initial::P, Final::AO, FuzzyFlag::None}},
//         {"pagn", {Initial::P, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"pang", {Initial::P, Final::ANG, FuzzyFlag::None}},
//         {"pan", {Initial::P, Final::AN, FuzzyFlag::None}},
//         {"pai", {Initial::P, Final::AI, FuzzyFlag::None}},
//         {"pa", {Initial::P, Final::A, FuzzyFlag::None}},
//         {"ou", {Initial::End, Final::OU, FuzzyFlag::None}},
//         {"o", {Initial::End, Final::O, FuzzyFlag::None}},
//         {"nve", {Initial::N, Final::VE, FuzzyFlag::None}},
//         {"nv", {Initial::N, Final::V, FuzzyFlag::None}},
//         {"nuo", {Initial::N, Final::UO, FuzzyFlag::None}},
//         {"nun", {Initial::N, Final::UN, FuzzyFlag::None}},
//         {"nue", {Initial::N, Final::VE, FuzzyFlag::VE_UE}},
//         {"nuagn", {Initial::N, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"nuang", {Initial::N, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"nuan", {Initial::N, Final::UAN, FuzzyFlag::None}},
//         {"nu", {Initial::N, Final::U, FuzzyFlag::None}},
//         {"nou", {Initial::N, Final::OU, FuzzyFlag::None}},
//         {"nogn", {Initial::N, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"non", {Initial::N, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"nong", {Initial::N, Final::ONG, FuzzyFlag::None}},
//         {"niu", {Initial::N, Final::IU, FuzzyFlag::None}},
//         {"nign", {Initial::N, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ning", {Initial::N, Final::ING, FuzzyFlag::None}},
//         {"nia", {Initial::N, Final::IA, FuzzyFlag::None}},
//         {"nin", {Initial::N, Final::IN, FuzzyFlag::None}},
//         {"nie", {Initial::N, Final::IE, FuzzyFlag::None}},
//         {"niao", {Initial::N, Final::IAO, FuzzyFlag::None}},
//         {"niagn", {Initial::N, Final::IANG, FuzzyFlag::CommonTypo}},
//         {"niang", {Initial::N, Final::IANG, FuzzyFlag::None}},
//         {"nian", {Initial::N, Final::IAN, FuzzyFlag::None}},
//         {"ni", {Initial::N, Final::I, FuzzyFlag::None}},
//         {"ng", {Initial::End, Final::NG, FuzzyFlag::None}},
//         {"negn", {Initial::N, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"neng", {Initial::N, Final::ENG, FuzzyFlag::None}},
//         {"nen", {Initial::N, Final::EN, FuzzyFlag::None}},
//         {"nei", {Initial::N, Final::EI, FuzzyFlag::None}},
//         {"ne", {Initial::N, Final::E, FuzzyFlag::None}},
//         {"nao", {Initial::N, Final::AO, FuzzyFlag::None}},
//         {"nagn", {Initial::N, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"nang", {Initial::N, Final::ANG, FuzzyFlag::None}},
//         {"nan", {Initial::N, Final::AN, FuzzyFlag::None}},
//         {"nai", {Initial::N, Final::AI, FuzzyFlag::None}},
//         {"na", {Initial::N, Final::A, FuzzyFlag::None}},
//         {"n", {Initial::N, Final::End, FuzzyFlag::None}},
//         {"mu", {Initial::M, Final::U, FuzzyFlag::None}},
//         {"mou", {Initial::M, Final::OU, FuzzyFlag::None}},
//         {"mo", {Initial::M, Final::O, FuzzyFlag::None}},
//         {"miu", {Initial::M, Final::IU, FuzzyFlag::None}},
//         {"mign", {Initial::M, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ming", {Initial::M, Final::ING, FuzzyFlag::None}},
//         {"min", {Initial::M, Final::IN, FuzzyFlag::None}},
//         {"mie", {Initial::M, Final::IE, FuzzyFlag::None}},
//         {"miao", {Initial::M, Final::IAO, FuzzyFlag::None}},
//         {"miagn", {Initial::M, Final::IAN, FuzzyFlag::IAN_IANG | FuzzyFlag::CommonTypo}},
//         {"miang", {Initial::M, Final::IAN, FuzzyFlag::IAN_IANG}},
//         {"mian", {Initial::M, Final::IAN, FuzzyFlag::None}},
//         {"mi", {Initial::M, Final::I, FuzzyFlag::None}},
//         {"megn", {Initial::M, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"meng", {Initial::M, Final::ENG, FuzzyFlag::None}},
//         {"men", {Initial::M, Final::EN, FuzzyFlag::None}},
//         {"mei", {Initial::M, Final::EI, FuzzyFlag::None}},
//         {"me", {Initial::M, Final::E, FuzzyFlag::None}},
//         {"mao", {Initial::M, Final::AO, FuzzyFlag::None}},
//         {"magn", {Initial::M, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"mang", {Initial::M, Final::ANG, FuzzyFlag::None}},
//         {"man", {Initial::M, Final::AN, FuzzyFlag::None}},
//         {"mai", {Initial::M, Final::AI, FuzzyFlag::None}},
//         {"ma", {Initial::M, Final::A, FuzzyFlag::None}},
//         {"m", {Initial::M, Final::End, FuzzyFlag::None}},
//         {"lve", {Initial::L, Final::VE, FuzzyFlag::None}},
//         {"lv", {Initial::L, Final::V, FuzzyFlag::None}},
//         {"luo", {Initial::L, Final::UO, FuzzyFlag::None}},
//         {"lun", {Initial::L, Final::UN, FuzzyFlag::None}},
//         {"lue", {Initial::L, Final::VE, FuzzyFlag::VE_UE}},
//         {"luagn", {Initial::L, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"luang", {Initial::L, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"luan", {Initial::L, Final::UAN, FuzzyFlag::None}},
//         {"lu", {Initial::L, Final::U, FuzzyFlag::None}},
//         {"lou", {Initial::L, Final::OU, FuzzyFlag::None}},
//         {"logn", {Initial::L, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"lon", {Initial::L, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"long", {Initial::L, Final::ONG, FuzzyFlag::None}},
//         {"lo", {Initial::L, Final::O, FuzzyFlag::None}},
//         {"liu", {Initial::L, Final::IU, FuzzyFlag::None}},
//         {"lign", {Initial::L, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ling", {Initial::L, Final::ING, FuzzyFlag::None}},
//         {"lin", {Initial::L, Final::IN, FuzzyFlag::None}},
//         {"lie", {Initial::L, Final::IE, FuzzyFlag::None}},
//         {"liao", {Initial::L, Final::IAO, FuzzyFlag::None}},
//         {"liagn", {Initial::L, Final::IANG, FuzzyFlag::CommonTypo}},
//         {"liang", {Initial::L, Final::IANG, FuzzyFlag::None}},
//         {"lian", {Initial::L, Final::IAN, FuzzyFlag::None}},
//         {"lia", {Initial::L, Final::IA, FuzzyFlag::None}},
//         {"li", {Initial::L, Final::I, FuzzyFlag::None}},
//         {"legn", {Initial::L, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"leng", {Initial::L, Final::ENG, FuzzyFlag::None}},
//         {"end_pos", {Initial::L, Final::ENG, FuzzyFlag::EN_ENG}},
//         {"lei", {Initial::L, Final::EI, FuzzyFlag::None}},
//         {"le", {Initial::L, Final::E, FuzzyFlag::None}},
//         {"lao", {Initial::L, Final::AO, FuzzyFlag::None}},
//         {"lagn", {Initial::L, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"lang", {Initial::L, Final::ANG, FuzzyFlag::None}},
//         {"lan", {Initial::L, Final::AN, FuzzyFlag::None}},
//         {"lai", {Initial::L, Final::AI, FuzzyFlag::None}},
//         {"la", {Initial::L, Final::A, FuzzyFlag::None}},
//         {"kuo", {Initial::K, Final::UO, FuzzyFlag::None}},
//         {"kun", {Initial::K, Final::UN, FuzzyFlag::None}},
//         {"kui", {Initial::K, Final::UI, FuzzyFlag::None}},
//         {"kuagn", {Initial::K, Final::UANG, FuzzyFlag::CommonTypo}},
//         {"kuang", {Initial::K, Final::UANG, FuzzyFlag::None}},
//         {"kuan", {Initial::K, Final::UAN, FuzzyFlag::None}},
//         {"kuai", {Initial::K, Final::UAI, FuzzyFlag::None}},
//         {"kua", {Initial::K, Final::UA, FuzzyFlag::None}},
//         {"ku", {Initial::K, Final::U, FuzzyFlag::None}},
//         {"kou", {Initial::K, Final::OU, FuzzyFlag::None}},
//         {"kogn", {Initial::K, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"kon", {Initial::K, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"kong", {Initial::K, Final::ONG, FuzzyFlag::None}},
//         {"kegn", {Initial::K, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"keng", {Initial::K, Final::ENG, FuzzyFlag::None}},
//         {"ken", {Initial::K, Final::EN, FuzzyFlag::None}},
//         {"kei", {Initial::K, Final::EI, FuzzyFlag::None}},
//         {"ke", {Initial::K, Final::E, FuzzyFlag::None}},
//         {"kao", {Initial::K, Final::AO, FuzzyFlag::None}},
//         {"kagn", {Initial::K, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"kang", {Initial::K, Final::ANG, FuzzyFlag::None}},
//         {"kan", {Initial::K, Final::AN, FuzzyFlag::None}},
//         {"kai", {Initial::K, Final::AI, FuzzyFlag::None}},
//         {"ka", {Initial::K, Final::A, FuzzyFlag::None}},
//         {"jun", {Initial::J, Final::UN, FuzzyFlag::None}},
//         {"jue", {Initial::J, Final::UE, FuzzyFlag::None}},
//         {"jve", {Initial::J, Final::UE, FuzzyFlag::CommonTypo}},
//         {"juagn", {Initial::J, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"juang", {Initial::J, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"jvagn", {Initial::J, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"jvang", {Initial::J, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"juan", {Initial::J, Final::UAN, FuzzyFlag::None}},
//         {"jvan", {Initial::J, Final::UAN, FuzzyFlag::CommonTypo}},
//         {"ju", {Initial::J, Final::U, FuzzyFlag::None}},
//         {"jv", {Initial::J, Final::U, FuzzyFlag::CommonTypo}},
//         {"jiu", {Initial::J, Final::IU, FuzzyFlag::None}},
//         {"jiogn", {Initial::J, Final::IONG, FuzzyFlag::CommonTypo}},
//         {"jion", {Initial::J, Final::IONG, FuzzyFlag::CommonTypo}},
//         {"jiong", {Initial::J, Final::IONG, FuzzyFlag::None}},
//         {"jign", {Initial::J, Final::ING, FuzzyFlag::CommonTypo}},
//         {"jing", {Initial::J, Final::ING, FuzzyFlag::None}},
//         {"jin", {Initial::J, Final::IN, FuzzyFlag::None}},
//         {"jie", {Initial::J, Final::IE, FuzzyFlag::None}},
//         {"jiao", {Initial::J, Final::IAO, FuzzyFlag::None}},
//         {"jiagn", {Initial::J, Final::IANG, FuzzyFlag::CommonTypo}},
//         {"jiang", {Initial::J, Final::IANG, FuzzyFlag::None}},
//         {"jian", {Initial::J, Final::IAN, FuzzyFlag::None}},
//         {"jia", {Initial::J, Final::IA, FuzzyFlag::None}},
//         {"ji", {Initial::J, Final::I, FuzzyFlag::None}},
//         {"huo", {Initial::H, Final::UO, FuzzyFlag::None}},
//         {"hun", {Initial::H, Final::UN, FuzzyFlag::None}},
//         {"hui", {Initial::H, Final::UI, FuzzyFlag::None}},
//         {"huagn", {Initial::H, Final::UANG, FuzzyFlag::CommonTypo}},
//         {"huang", {Initial::H, Final::UANG, FuzzyFlag::None}},
//         {"huan", {Initial::H, Final::UAN, FuzzyFlag::None}},
//         {"huai", {Initial::H, Final::UAI, FuzzyFlag::None}},
//         {"hua", {Initial::H, Final::UA, FuzzyFlag::None}},
//         {"hu", {Initial::H, Final::U, FuzzyFlag::None}},
//         {"hou", {Initial::H, Final::OU, FuzzyFlag::None}},
//         {"hogn", {Initial::H, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"hon", {Initial::H, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"hong", {Initial::H, Final::ONG, FuzzyFlag::None}},
//         {"hegn", {Initial::H, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"heng", {Initial::H, Final::ENG, FuzzyFlag::None}},
//         {"hen", {Initial::H, Final::EN, FuzzyFlag::None}},
//         {"hei", {Initial::H, Final::EI, FuzzyFlag::None}},
//         {"he", {Initial::H, Final::E, FuzzyFlag::None}},
//         {"hao", {Initial::H, Final::AO, FuzzyFlag::None}},
//         {"hagn", {Initial::H, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"hang", {Initial::H, Final::ANG, FuzzyFlag::None}},
//         {"han", {Initial::H, Final::AN, FuzzyFlag::None}},
//         {"hai", {Initial::H, Final::AI, FuzzyFlag::None}},
//         {"ha", {Initial::H, Final::A, FuzzyFlag::None}},
//         {"guo", {Initial::G, Final::UO, FuzzyFlag::None}},
//         {"gun", {Initial::G, Final::UN, FuzzyFlag::None}},
//         {"gui", {Initial::G, Final::UI, FuzzyFlag::None}},
//         {"guagn", {Initial::G, Final::UANG, FuzzyFlag::CommonTypo}},
//         {"guang", {Initial::G, Final::UANG, FuzzyFlag::None}},
//         {"guan", {Initial::G, Final::UAN, FuzzyFlag::None}},
//         {"guai", {Initial::G, Final::UAI, FuzzyFlag::None}},
//         {"gua", {Initial::G, Final::UA, FuzzyFlag::None}},
//         {"gu", {Initial::G, Final::U, FuzzyFlag::None}},
//         {"gou", {Initial::G, Final::OU, FuzzyFlag::None}},
//         {"gogn", {Initial::G, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"gon", {Initial::G, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"gong", {Initial::G, Final::ONG, FuzzyFlag::None}},
//         {"gegn", {Initial::G, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"geng", {Initial::G, Final::ENG, FuzzyFlag::None}},
//         {"gen", {Initial::G, Final::EN, FuzzyFlag::None}},
//         {"gei", {Initial::G, Final::EI, FuzzyFlag::None}},
//         {"ge", {Initial::G, Final::E, FuzzyFlag::None}},
//         {"gao", {Initial::G, Final::AO, FuzzyFlag::None}},
//         {"gagn", {Initial::G, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"gang", {Initial::G, Final::ANG, FuzzyFlag::None}},
//         {"gan", {Initial::G, Final::AN, FuzzyFlag::None}},
//         {"gai", {Initial::G, Final::AI, FuzzyFlag::None}},
//         {"ga", {Initial::G, Final::A, FuzzyFlag::None}},
//         {"fuai", {Initial::H, Final::UAI, FuzzyFlag::F_H}},
//         {"fu", {Initial::F, Final::U, FuzzyFlag::None}},
//         {"fou", {Initial::F, Final::OU, FuzzyFlag::None}},
//         {"fo", {Initial::F, Final::O, FuzzyFlag::None}},
//         {"fiao", {Initial::F, Final::IAO, FuzzyFlag::None}},
//         {"fegn", {Initial::F, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"feng", {Initial::F, Final::ENG, FuzzyFlag::None}},
//         {"fen", {Initial::F, Final::EN, FuzzyFlag::None}},
//         {"fei", {Initial::F, Final::EI, FuzzyFlag::None}},
//         {"fagn", {Initial::F, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"fang", {Initial::F, Final::ANG, FuzzyFlag::None}},
//         {"fan", {Initial::F, Final::AN, FuzzyFlag::None}},
//         {"fa", {Initial::F, Final::A, FuzzyFlag::None}},
//         {"er", {Initial::End, Final::ER, FuzzyFlag::None}},
//         {"egn", {Initial::End, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"eng", {Initial::End, Final::ENG, FuzzyFlag::None}},
//         {"en", {Initial::End, Final::EN, FuzzyFlag::None}},
//         {"ei", {Initial::End, Final::EI, FuzzyFlag::None}},
//         {"e", {Initial::End, Final::E, FuzzyFlag::None}},
//         {"duo", {Initial::D, Final::UO, FuzzyFlag::None}},
//         {"dun", {Initial::D, Final::UN, FuzzyFlag::None}},
//         {"dui", {Initial::D, Final::UI, FuzzyFlag::None}},
//         {"duagn", {Initial::D, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         {"duang", {Initial::D, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"duan", {Initial::D, Final::UAN, FuzzyFlag::None}},
//         {"du", {Initial::D, Final::U, FuzzyFlag::None}},
//         {"dou", {Initial::D, Final::OU, FuzzyFlag::None}},
//         {"dogn", {Initial::D, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"don", {Initial::D, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"dong", {Initial::D, Final::ONG, FuzzyFlag::None}},
//         {"diu", {Initial::D, Final::IU, FuzzyFlag::None}},
//         {"dign", {Initial::D, Final::ING, FuzzyFlag::CommonTypo}},
//         {"ding", {Initial::D, Final::ING, FuzzyFlag::None}},
//         {"din", {Initial::D, Final::ING, FuzzyFlag::IN_ING}},
//         {"die", {Initial::D, Final::IE, FuzzyFlag::None}},
//         {"diao", {Initial::D, Final::IAO, FuzzyFlag::None}},
//         {"diagn", {Initial::D, Final::IAN, FuzzyFlag::IAN_IANG | FuzzyFlag::CommonTypo}},
//         {"diang", {Initial::D, Final::IAN, FuzzyFlag::IAN_IANG}},
//         {"dian", {Initial::D, Final::IAN, FuzzyFlag::None}},
//         {"dia", {Initial::D, Final::IA, FuzzyFlag::None}},
//         {"di", {Initial::D, Final::I, FuzzyFlag::None}},
//         {"degn", {Initial::D, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"deng", {Initial::D, Final::ENG, FuzzyFlag::None}},
//         {"den", {Initial::D, Final::EN, FuzzyFlag::None}},
//         {"dei", {Initial::D, Final::EI, FuzzyFlag::None}},
//         {"de", {Initial::D, Final::E, FuzzyFlag::None}},
//         {"dao", {Initial::D, Final::AO, FuzzyFlag::None}},
//         {"dagn", {Initial::D, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"dang", {Initial::D, Final::ANG, FuzzyFlag::None}},
//         {"dan", {Initial::D, Final::AN, FuzzyFlag::None}},
//         {"dai", {Initial::D, Final::AI, FuzzyFlag::None}},
//         {"da", {Initial::D, Final::A, FuzzyFlag::None}},
//         {"cuo", {Initial::C, Final::UO, FuzzyFlag::None}},
//         {"cun", {Initial::C, Final::UN, FuzzyFlag::None}},
//         {"cui", {Initial::C, Final::UI, FuzzyFlag::None}},
//         // {"cuagn", {Initial::C, Final::UAN, FuzzyFlag::UAN_UANG | FuzzyFlag::CommonTypo}},
//         // {"cuang", {Initial::C, Final::UAN, FuzzyFlag::UAN_UANG}},
//         {"cuagn", {Initial::CH, Final::UANG, FuzzyFlag::C_CH | FuzzyFlag::CommonTypo}},
//         {"cuang", {Initial::CH, Final::UANG, FuzzyFlag::C_CH}},
//         {"cuan", {Initial::C, Final::UAN, FuzzyFlag::None}},
//         {"cuai", {Initial::CH, Final::UAI, FuzzyFlag::C_CH}},
//         {"cu", {Initial::C, Final::U, FuzzyFlag::None}},
//         {"cou", {Initial::C, Final::OU, FuzzyFlag::None}},
//         {"cogn", {Initial::C, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"con", {Initial::C, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"cong", {Initial::C, Final::ONG, FuzzyFlag::None}},
//         {"ci", {Initial::C, Final::I, FuzzyFlag::None}},
//         {"chuo", {Initial::CH, Final::UO, FuzzyFlag::None}},
//         {"chun", {Initial::CH, Final::UN, FuzzyFlag::None}},
//         {"chui", {Initial::CH, Final::UI, FuzzyFlag::None}},
//         {"chuagn", {Initial::CH, Final::UANG, FuzzyFlag::CommonTypo}},
//         {"chuang", {Initial::CH, Final::UANG, FuzzyFlag::None}},
//         {"chuan", {Initial::CH, Final::UAN, FuzzyFlag::None}},
//         {"chuai", {Initial::CH, Final::UAI, FuzzyFlag::None}},
//         {"chua", {Initial::CH, Final::UA, FuzzyFlag::None}},
//         {"chu", {Initial::CH, Final::U, FuzzyFlag::None}},
//         {"chou", {Initial::CH, Final::OU, FuzzyFlag::None}},
//         {"chogn", {Initial::CH, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"chon", {Initial::CH, Final::ONG, FuzzyFlag::CommonTypo}},
//         {"chong", {Initial::CH, Final::ONG, FuzzyFlag::None}},
//         {"chi", {Initial::CH, Final::I, FuzzyFlag::None}},
//         {"chegn", {Initial::CH, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"cheng", {Initial::CH, Final::ENG, FuzzyFlag::None}},
//         {"chen", {Initial::CH, Final::EN, FuzzyFlag::None}},
//         {"che", {Initial::CH, Final::E, FuzzyFlag::None}},
//         {"chao", {Initial::CH, Final::AO, FuzzyFlag::None}},
//         {"chagn", {Initial::CH, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"chang", {Initial::CH, Final::ANG, FuzzyFlag::None}},
//         {"chan", {Initial::CH, Final::AN, FuzzyFlag::None}},
//         {"chai", {Initial::CH, Final::AI, FuzzyFlag::None}},
//         {"cha", {Initial::CH, Final::A, FuzzyFlag::None}},
//         {"cegn", {Initial::C, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"ceng", {Initial::C, Final::ENG, FuzzyFlag::None}},
//         {"cen", {Initial::C, Final::EN, FuzzyFlag::None}},
//         {"ce", {Initial::C, Final::E, FuzzyFlag::None}},
//         {"cao", {Initial::C, Final::AO, FuzzyFlag::None}},
//         {"cagn", {Initial::C, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"cang", {Initial::C, Final::ANG, FuzzyFlag::None}},
//         {"can", {Initial::C, Final::AN, FuzzyFlag::None}},
//         {"cai", {Initial::C, Final::AI, FuzzyFlag::None}},
//         {"ca", {Initial::C, Final::A, FuzzyFlag::None}},
//         {"bu", {Initial::B, Final::U, FuzzyFlag::None}},
//         {"bo", {Initial::B, Final::O, FuzzyFlag::None}},
//         {"bign", {Initial::B, Final::ING, FuzzyFlag::CommonTypo}},
//         {"bing", {Initial::B, Final::ING, FuzzyFlag::None}},
//         {"bin", {Initial::B, Final::IN, FuzzyFlag::None}},
//         {"bie", {Initial::B, Final::IE, FuzzyFlag::None}},
//         {"biao", {Initial::B, Final::IAO, FuzzyFlag::None}},
//         {"biagn", {Initial::B, Final::IANG, FuzzyFlag::CommonTypo}},
//         {"biang", {Initial::B, Final::IANG, FuzzyFlag::None}},
//         {"bian", {Initial::B, Final::IAN, FuzzyFlag::None}},
//         {"bi", {Initial::B, Final::I, FuzzyFlag::None}},
//         {"begn", {Initial::B, Final::ENG, FuzzyFlag::CommonTypo}},
//         {"beng", {Initial::B, Final::ENG, FuzzyFlag::None}},
//         {"ben", {Initial::B, Final::EN, FuzzyFlag::None}},
//         {"bei", {Initial::B, Final::EI, FuzzyFlag::None}},
//         {"bao", {Initial::B, Final::AO, FuzzyFlag::None}},
//         {"bagn", {Initial::B, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"bang", {Initial::B, Final::ANG, FuzzyFlag::None}},
//         {"ban", {Initial::B, Final::AN, FuzzyFlag::None}},
//         {"bai", {Initial::B, Final::AI, FuzzyFlag::None}},
//         {"ba", {Initial::B, Final::A, FuzzyFlag::None}},
//         {"ao", {Initial::End, Final::AO, FuzzyFlag::None}},
//         {"agn", {Initial::End, Final::ANG, FuzzyFlag::CommonTypo}},
//         {"ang", {Initial::End, Final::ANG, FuzzyFlag::None}},
//         {"an", {Initial::End, Final::AN, FuzzyFlag::None}},
//         {"ai", {Initial::End, Final::AI, FuzzyFlag::None}},
//         {"a", {Initial::End, Final::A, FuzzyFlag::None}},
//     });
//     splitBaseMap();
//     init_parse_map();
// }

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
            auto s = string_view(&src[start], i);
            if (_parse_ref.contains(s)) { // valid alpha
                dst.emplace_back(_parse_ref[s][0].a);
                start += i; //commit
                break;
                //direct match only take the full match, because src is supposed to be single syllable
            } 
        }
        if (i == 0) {
            log_trace("invalid s: {}", src[start]);
            break;
        }
    }
    
}

void logGraph(Graph<AlphaMark, MarkKey>& g) {
    log_info("logging graph:");
    for (auto& e : g.GetTable()) {
        log_info("key {} data at {}", e.first.toString(), fmt::ptr(&e.second));
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
        auto s = string_view(&src[start], i);
        if (_parse_ref.contains(s)) { // valid alpha
            for (auto& v : _parse_ref[s]) {
                const MarkKey key{start,start+v.s.size(), v.a}; // 【start， end）
                if (table.contains(key)) { //already exist
                    cur_node->AddToNode((table[key])); //different address from ori node, but the value is the same
                    log_info("get key {} data at {}", key.toString(), fmt::ptr((table[key])));
                    continue; //same start, same iteration, certainly same end, so just return, actually this means a joined node.
                } else { //new node
                    auto ptr = g.AddNode(key, AlphaMark{key, v});
                    log_info("added new node {} at {}", key.toString(), fmt::ptr(ptr));
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
    log_info("try parse: {}", s);
    Graph<Pinyin::AlphaMark, Pinyin::MarkKey> g;
    ParseToGraph(g, s);
    auto res = g.DFS_ALL();
    log_info("got res: ");
    for (auto&v : *res) {
        log_info("dfs res: {}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* const &k){return string(k->data.s); }, ","));
    }
    ApplyFuzzyForGraph(g);
    auto res2 = g.DFS_ALL();
    vector<PinyinVec> keys(res2->size());
    auto key = keys.begin();
    log_info("res after fuzzy: ");
    for (int i = 0; i<keys.size(); ++i) {
        const auto& v = (*res2)[i];
        log_info("route: {}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](Pinyin::AlphaMark* const &k){return string(k->data.s); }, ","));
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
    spdlog::set_level(spdlog::level::trace);
    Pinyin::PinyinParser p;
    string s(argv[1]);
    log_info("try parse: {}", s);
    spdlog::flush_on(spdlog::level::trace);
    Graph<Pinyin::AlphaMark, Pinyin::MarkKey> g;
    p.ParseToGraph(g, s);
    auto res = g.DFS_ALL();
    log_info("got res: ");
    for (auto&v : *res) {
        log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](AlphaMark* const &k){return string(k->data.s); }, ","));
    }
    p.ApplyFuzzyForGraph(g);
    auto res2 = g.DFS_ALL();
    log_info("res after fuzzy: ");
    for (auto&v : *res2) {
        log_info("{}", VecToString<Pinyin::AlphaMark*>(&v[0],  v.size(), [](AlphaMark* const &k){return string(k->data.s); }, ","));
    }
    delete res;
    delete res2;
    std::cout<<"done.\n";
    return 0;
}
