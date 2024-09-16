#pragma once

#include <concepts>
template<typename D>
struct WordNode
{
    D data;
    size_t score;
    WordNode(D d, size_t score){
        data = d;
        score = score;
    }
    bool operator<(const WordNode& other) const {
        return this->score < other.score;
    }
    bool operator>(const WordNode& other) const {
        return this->score > other.score;
    }
    bool operator==(const WordNode& other) const {
        return this->score == other.score;
    }

    bool operator<=(const WordNode& other) const {
        return this->score <= other.score;
    }
    bool operator>=(const WordNode& other) const {
        return this->score >= other.score;
    }
};
