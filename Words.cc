#include "Words.h"
#include <vector>
#include <string>

using namespace std;

ostream& operator<<(ostream& stream, const Words& line) {
    string placeholder = "";

    for (string s : line.output) {
        placeholder = placeholder + s;
        placeholder = placeholder + ",";
    }
    placeholder.pop_back();
    return  stream << placeholder;
}

Words::Words(std::string line) {
    analyze(line);
}

Words::Words(const Words& line) : output(line.output) {}
//Words::Words(const Words& line) : boo() {}


Words& Words::operator=(const Words& word) {
    output = word.output;

    return *this;
}


std::vector<std::string> Words::analyze(std::string input) {
    output.clear();
    boo.clear();

    string word;
    string line;
    bool backcheck = false;
    bool escaped = false;


    for (char c : input) {

        if (backcheck == true) {
            word = word + c;
            backcheck = false;
            escaped = true;
            c = '\0';
        }
        else if (isspace(c)) {
            if (word != "") {
                if (isspace(word[0])) {
                    word = word.erase(0, 1);
                }

                if ((word == "" || word == " ") == false) {
                    output.push_back(word);
                    helper(escaped);
                    escaped = false;
                }
                word = "";
            }
        }
        else if (c == '\\') {
            backcheck = true;
        }

        else if (c == '(' || c == ')') {
            if (word != "") {
                if (isspace(word[0])) {
                    word = word.erase(0, 1);
                }

                if ((word == "" || word == " ") == false) {
                    output.push_back(word);
                    helper(escaped);
                    escaped = false;
                }

                word = "";
            }
            word = word + c;
            output.push_back(word);
            helper(escaped);
            escaped = false;
            word = "";
        }
        else if (c == '\0') {
            continue;
        }
        else {

            word = word + c;
        }

    }
    if (word != "") {
        if (isspace(word[0])) {
            word = word.erase(0, 1);
        }

        if ((word == "" || word == " ") == false) {
            output.push_back(word);
            helper(escaped);
            escaped = false;
        }

        word = "";
    }
    return output;
}

void Words::helper(bool checker) {
    boo.push_back(checker);
}



[[nodiscard]] long unsigned int Words::size() const {
    vector<string> v = output;
    return output.size();
}

[[nodiscard]] bool Words::empty() const {
    int temp = size();
    if (temp == 0) {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool Words::get(long unsigned int index, std::string& word, bool& checker) const {
    if (index > output.size()) {
        return false;
    }
    else {
        if (boo.size() == 0) {
            checker = false;
            word = output[index];
            return true;
        }
        else {
            checker = true;
            word = output[index];
            if (boo[index] == 0) {
                checker = false;
            }
            return true;
        }
    }
}


Words Words::operator+(const Words& rhs)const {
    Words temp = *this;
    for (string s : rhs.output) {
        temp.output.push_back(s);
    }
    return temp;
}





Words Words::operator+=(const Words& rhs) {
    *this = *this + rhs;
    return *this;
}

bool Words::operator==(const Words& rhs) const {
    if (rhs.output.size() != output.size()) {
        return false;
    }
    for (long unsigned int i = 0; i < output.size(); i++) {
        string r = rhs.output[i];
        string l = output[i];
        if (l != r) {
            return false;
        }
    }
    return true;
}

bool Words::operator!=(const Words& rhs) const {
    if (*this == rhs) {
        return false;
    }
    else {
        return true;

    }
}

bool Words::operator!() const {
    if (output.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}


t& Words::operator[](size_t t) {
    string w;
    bool b = true;
    get(t, w, b);
    cat.first = w;
    cat.second = b;
    return cat;
}

Words& Words::operator--() {//pre{
    for (long unsigned int i = 0; i < output.size(); i++) {
        string s = output[i];
        if (s == "") {
            output.erase(output.begin() + i);
                i--;
        }
        else {
            int t = s.size();
            s.resize(t - 1);
            output[i] = s;
 
        }
    }
    return *this;
}

Words Words::operator--(int) {//post{//one from example //return previous value before mod
    auto te = *this;
    *this = --*this;
    return te;
}

Words::operator bool() const {
    bool b = !*this;
    if (b) {
        return false;
    }
    else {
        return true;
    }
}












