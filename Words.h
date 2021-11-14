#ifndef WORDS_H
#define WORDS_H
#include<string>
#include <vector>
#include <iostream>
#include <ostream>

    struct t { 
    std::string first; 
    bool second; 
    };

class Words {

private:

    //std::vector<std::string> output;

    //string str;
public:
    //string str;
    //

    

    t cat;

    std::vector<std::string> output;

    std::vector<bool> boo;

    Words() = delete;

    Words(std::string line);

    Words(const Words& line);                       //copy

    Words& operator=(const Words& word);             //assignment opperator

    ~Words() = default;                                       // destructor

    std::vector<std::string> analyze(std::string input);

    void helper(bool checker);

    long unsigned int size() const;

    bool empty() const;

    bool get(long unsigned int index, std::string& word, bool& checker)const;

     Words operator+(const Words& rhs)const;

     Words operator+=(const Words& rhs);

     bool operator==(const Words& rhs)const;

     bool operator!=(const Words& rhs)const;

     bool operator!()const;

     t& operator[](size_t);

     Words& operator--();//pre

     Words operator--(int);//post

     operator bool() const;
};
std::ostream& operator<<(std::ostream&, const Words&);


#endif



