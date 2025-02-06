#include "dict_parser.hpp"

// Function to parse the input text
std::vector<WordEntry>* parseInput(const std::string& filePath) {
    auto entries = new std::vector<WordEntry>();
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return entries; // Return empty vector on error
    }

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
        entries->emplace_back(entry);
    }

    return entries;
}

unordered_map<string, string>* parseFreqDict(const string& src){
    std::ifstream file(src);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << src << std::endl;
        return nullptr; // Return empty vector on error
    }

    auto ret = new unordered_map<string, string>();
    auto &ref = *ret;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        string id;
        std::string word;
        std::string freqPart;

        lineStream >> id;
        // Read the word
        lineStream >> word;
        lineStream >> freqPart;
        ref[word] = freqPart;
    }
    return ret;
}

void mergeDict(const string& src, const string& ref, const string& dst) {
    auto ptr = parseFreqDict(ref);
    if (ptr == nullptr) {
        std::cerr << "Error opening ref file: " << ref << std::endl;
        return;
    }
    auto& refMap = *ptr
    

    std::ofstream file(dst);
    if (!file.is_open()) {
        std::cerr << "Error opening ouptput file: " << dst << std::endl;
        return;
    }

    std::ifstream srcFile(src);
    
    if (!srcFile.is_open()) {
        std::cerr << "Error opening src file: " << src << std::endl;
        return;
    }

    std::string line;
    while (std::getline(srcFile, line)) {
        std::istringstream lineStream(line);
        WordEntry entry;
        std::string pinyinPart;
        // std::string freqPart;

        // Read the word
        lineStream >> entry.word;
        if (entry.word[0] == '#') {
            //spdlog::trace("meet comment: {}", entry.word);
            continue;
        }
        if (!refMap.count(entry.word)) {
            continue;
        }
        file << entry.word << "\t";

        // Read the pinyin (until the last part which is the frequency)
        bool firstPinyin = true;
        while (lineStream >> pinyinPart) {
            if (std::isdigit(pinyinPart[0])) {
                // freqPart = pinyinPart; // Last part is frequency
                // string c;
                // file >> c; // tail " "
                break;
            }
            //entry.pinyin.emplace_back(pinyinPart);
            if (!firstPinyin) {
                file << " ";
            }
            file << pinyinPart;
        }
        file << "\t" << refMap[entry.word] << endl;
    }
    delete
}

int testDictParser() {

    auto parsedEntries = parseInput("./resources/dict.yml");

    // Output the parsed entries
    for (const auto& entry : *parsedEntries) {
        std::cout << "Word: " << entry.word << ", Pinyin: ";
        for (const auto& p : entry.pinyin) {
            std::cout << p << " ";
        }
        std::cout << ", Frequency: " << entry.freq << std::endl;
    }
    delete parsedEntries;
    return 0;
}
