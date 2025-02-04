#include "hashMapDict.hpp"
#include "dict_parser.hpp"

int main(int argc, char* argv[]) {
    mergeDict("../resources/dict.yml", "../resources/sgDict.txt", "../resources/new_dict.yml");
    //testHashMapDict(argc, argv);
    return 0;
}