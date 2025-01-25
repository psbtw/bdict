#pragma once

#include <concepts>
#include <ostream>
using namespace std;

template<typename D>
struct WordNode
{
    D data;
    size_t score;
    WordNode(const D& d, size_t sc){
        data = d;
        score = sc;
    }

    WordNode& operator=(WordNode&& other) {
        
        // Guard self assignment
        if (this == &other)
            return *this;
        data = other.data;
        score = other.score;
        //log_trace("operator=, {}:{}", data, score);
        return *this;
    }    

    WordNode& operator=(const WordNode& other) {
        
        // Guard self assignment
        if (this == &other)
            return *this;
        data = other.data;
        score = other.score;
        //log_trace("operator=, {}:{}", data, score);
        return *this;
    }  

    WordNode(const WordNode& other) {
        data = other.data;
        score = other.score;
        //log_trace("copy constructor of &, {}:{}", data, score);
    }
    WordNode(const WordNode&& other) {
        data = other.data;
        score = other.score;
        //log_trace("copy constructor of &&, {}:{}", data, score);
    }
    bool operator<(const WordNode& other) const {
        return this->score < other.score;
    }
    bool operator>(const WordNode& other) const {
        return this->score > other.score;
    }
    bool operator==(const WordNode& other) const {
        return this->data == other.data;
    }

    bool operator<=(const WordNode& other) const {
        return this->score <= other.score;
    }
    bool operator>=(const WordNode& other) const {
        return this->score >= other.score;
    }

    inline string ToString() const{
        return format("{}:{},  ", data, score);
    }

    ostream& operator<<(ostream& s) const {
        return s << this->ToString();
    }
}; 
